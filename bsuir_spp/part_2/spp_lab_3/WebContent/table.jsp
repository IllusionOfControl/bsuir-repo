<%@ page language="java" contentType="text/html; charset=US-ASCII"
    pageEncoding="US-ASCII"%>
<%@ taglib uri="/struts-tags" prefix="s"%>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=US-ASCII">
<title>LR3</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
</head>
<body>
<s:include value="welcome.jsp"></s:include>

<div class="container">
<table border="1pt" style="width: 100%; margin-top: 30px;" class="table">
    <tr>
        <th scope="col">ID</th>
        <th scope="col">Name</th>
        <th scope="col">Created at</th>
        <th scope="col">Vacation</th>
    </tr>

    <s:iterator value="items" var="item">
        <tr>
            <td scope="row"><s:property value="#item.id"/> </td>
            <td><s:property value="#item.name"/> </td>
            <td><s:property value="#item.created"/> </td>

            <s:if test="#item.checked==true">
                <td><input type="checkbox" readonly checked/></td>
            </s:if>
            <s:if test="#item.checked==false">
                <td> <input type="checkbox" readonly/></td>
            </s:if>
        </tr>
    </s:iterator>
</table>
</div>

</body>
</html>