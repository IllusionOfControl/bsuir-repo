<%@ page import="com.example.entities.Data" %>
<%@ page import="com.example.entities.Customer" %>
<%@ page import="com.example.entities.Visit" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>spp_lab_4</title>
    <link rel="stylesheet" href="login/style.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.1/jquery.min.js"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
    <script src="login/plugin.js"></script>
    <script src="login/main.js"></script>
</head>
<body class="" style="background: #3f3f3f; color: #000">
    <div class="container" style="color: #000; border-radius: 50px;">
        <br/>

        <h1>Hello, <%
            if(Data.order != null)
                out.print(Data.order.getOrderName());
        %></h1>

        <a href="${pageContext.request.contextPath}/login" class="btn btn-outline-warning">Sign out</a>

        <br/>
        <br/>

        <select class="form-select mt-5" id="patientId" name="patientId" required>
            <%
                for (Customer p : Data.customerList) {
                    out.println(String.format("<option value=\"%1$s\">%2$s</option>", p.getId(), p.getName()));
                }
            %>
        </select>
        <div class="mt-8 mb-8 ">
            <input type="text" class="form-control" id="description" name="description" required>
        </div>
        <button class="login btn btn-outline-primary" id="addBtn">Add</button>

        <br>

        <h1>Orders</h1>

        <table class="table" id="visits" style="background: slategray">
            <thead>
            <tr>
                <th scope="col">ID</th>
                <th scope="col">Date</th>
                <th scope="col">Description</th>
                <th scope="col">Order</th>
                <th scope="col"></th>
            </tr>
            </thead>

            <tbody>
            <%
                for (Visit v : Data.getVisitList()) {
                    out.println(String.format("<tr class=\"visitTd_%1$s\">", v.getId()));
                    out.println(String.format("<th scope=\"row\">%1$s</td>", v.getId()));
                    out.println(String.format("<td>%1$s</td>", v.getDisplayDate()));
                    out.println(String.format("<td>%1$s</td>", v.getDescription()));
                    out.println(String.format("<td>%1$s</td>", v.getOrderName()));
                    out.println(String.format("<td><button class=\"removeVisit btn btn-danger\" data-visit=%1$s>Remove</button></td>", v.getId()));
                    out.println("</tr>");
                }
            %>
            </tbody>
        </table>
    </div>
</body>
</html>
