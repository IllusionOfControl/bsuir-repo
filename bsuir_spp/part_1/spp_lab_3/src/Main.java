public class Main {

    public static void main(String[] args) {
        BillClass givemoney = new BillClass();
        for (int i = 1; i < 6; i++){
            int result = 100 *i;
            Thread t = new Thread(() -> {
                new Money(result, givemoney).run();
                new Money(result, givemoney).run();
            });
            //Thread t = new Thread(new Money(result, givemoney));
            t.setName("Thread "+ i);
            t.start();
        }
    }
}

class BillClass{
    int Bill = 100_000;
}

class Money implements Runnable{

    int count = 0;
    BillClass bill;
    Money(int count, BillClass bill){
        this.count=count;
        this.bill=bill;
    }

    public void run(){
        synchronized(bill){
            System.out.printf("%s \n", Thread.currentThread().getName());
            if(bill.Bill == 0)
                System.out.println("Money 404: Not Found :(");
            else if(count > bill.Bill)
                System.out.println("No money!");
            else{
                bill.Bill = bill.Bill - count;
                System.out.println("You take " + count + " money!");
            }
        }
    }
}

