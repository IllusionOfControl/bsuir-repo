package org.example;

import java.sql.*;

public class Main {
    private static final String url = "jdbc:mysql://192.168.24.152:3306/spp";
    private static final String user = "remote";
    private static final String password = "Qw123456";

    public static void main(String[] args) {

        Connection connection = null;
        try
        {
            /*
             *
             *           STATEMENT, CONNECTION, RESULTSET
             *
             * */
            // create a database connection
            connection = DriverManager.getConnection(url, user, password);  // открываем соединение
            Statement statement = connection.createStatement();             // создаём объект обычных запросов
            statement.setQueryTimeout(30);  // set timeout to 30 sec.

            System.out.println("Creating table");
            statement.executeUpdate("drop table if exists coffee");
            statement.executeUpdate("create table coffee (id INTEGER PRIMARY KEY AUTO_INCREMENT, name TEXT, price INTEGER)");

            statement.executeUpdate("drop table if exists payment");
            statement.executeUpdate("create table payment (id INTEGER PRIMARY KEY AUTO_INCREMENT, coffee_id INTEGER, count INTEGER, total INTEGER)");

            System.out.println("Insert Values");
            statement.executeUpdate("insert into coffee (name, price) values('americano', 12)");
            statement.executeUpdate("insert into coffee (name, price) values('raf', 9)");
            statement.executeUpdate("insert into coffee (name, price) values('cappuchino', 8)");
            statement.executeUpdate("insert into coffee (name, price) values('russiano', 10)");
            statement.executeUpdate("insert into coffee (name, price) values('cacao', 6)");

            statement.executeUpdate("insert into payment (coffee_id, count, total) values(1, 1, 12)");
            statement.executeUpdate("insert into payment (coffee_id, count, total) values(2, 2, 18)");
            statement.executeUpdate("insert into payment (coffee_id, count, total) values(3, 1, 8)");
            statement.executeUpdate("insert into payment (coffee_id, count, total) values(1, 2, 24)");

            ResultSet rs;
            // вывод видов кофе
            System.out.println("Coffee:");
            rs = statement.executeQuery("select * from coffee");
            while(rs.next())
            {
                System.out.println("id=" + rs.getString("id") + "\tname=" + rs.getString("name") + "\tprice=" + rs.getString("price") );
            }

            // вывод оплаты
            System.out.println("Payment:");
            rs = statement.executeQuery("select * from payment");
            while(rs.next())
            {
                System.out.println("id=" + rs.getString("id") + "\tcoffee_id=" + rs.getString("coffee_id") + "\tcount=" + rs.getString("count") + "\total=" + rs.getString("total") );
            }

            /*
            *
            *           PREPARED STATEMENT
            *
            * */
            PreparedStatement ps;   // создаём объект подготовленых запросов

            // вывод кофе ценой < 9
            System.out.println("Prepared statement (coffee.price < 9)");
            ps = connection.prepareStatement("SELECT * from coffee WHERE price < 9"); // получаем подготовленый запрос
            rs = ps.executeQuery();
            while(rs.next())
            {
                System.out.println("id=" + rs.getString("id") + "\tname=" + rs.getString("name") + "\tprice=" + rs.getString("price") );
            }

            // добавление кофе
            System.out.println("Prepared statement (add coffee) and print");
            ps = connection.prepareStatement("insert into coffee (name, price) values(?, ?)"); // получаем подготовленый запрос
            ps.setString(1, "tea"); // задаём аргументы
            ps.setInt(2, 4);
            ps.executeUpdate();
            ps = connection.prepareStatement("SELECT * from coffee");
            rs = ps.executeQuery();
            while(rs.next())
            {
                // read the result set
                System.out.println("id=" + rs.getString("id") + "\tname=" + rs.getString("name") + "\tprice=" + rs.getString("price") );
            }

            /*
             *
             *           TRANSACTION
             *
             * */

            boolean failed;
            System.out.println("Transaction");
            connection.setAutoCommit(false);    // выключаем авто запись
            ps = connection.prepareStatement("insert into coffee (name, price) values(?, ?)", Statement.RETURN_GENERATED_KEYS);
            ps.setString(1, "red coffee");
            ps.setInt(2, 20);
            ps.executeUpdate();
            ps.setString(1, "chill coffee");
            ps.setInt(2, 21);
            ps.executeUpdate();
            ps.setString(1, "white tea");
            ps.setInt(2, 8);
            ps.executeUpdate();
            failed = false;             // Transaction
            if (failed) {
                System.out.println("Transaction:Rollback");
                connection.rollback();  // если что-то поломано, то отменяем изменения
            } else {
                System.out.println("Transaction:Commit");
                connection.commit();    // если нормально, изменения записываем
            }
            connection.setAutoCommit(true); // включаем авто запись

            ps = connection.prepareStatement("SELECT * from coffee");
            rs = ps.executeQuery();
            while(rs.next())
            {
                System.out.println("id=" + rs.getString("id") + "\tname=" + rs.getString("name") + "\tprice=" + rs.getString("price") );
            }

            /*
             *
             *           CALLABLE STATEMENT
             *
             * */
            System.out.println("CallableStatement");
            statement.executeUpdate("DROP PROCEDURE IF EXISTS GET_POOR_DRINKS;");   // удаляем процедуру если есть
            statement.executeUpdate("CREATE PROCEDURE GET_POOR_DRINKS() BEGIN SELECT * FROM coffee WHERE price < 8; END");  // создаём процедуру
            CallableStatement cs = connection.prepareCall("{CALL GET_POOR_DRINKS()}");  // создаём объект подготовленного вызова
            rs = cs.executeQuery(); // вызываем
            while(rs.next())
            {
                System.out.println("id=" + rs.getString("id") + "\tname=" + rs.getString("name") + "\tprice=" + rs.getString("price") );
            }
        }
        catch(SQLException e)
        {
            System.err.println(e.getMessage());
        }
        finally {
            try {
                if (connection != null)
                    connection.close();
            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
        }
    }
}