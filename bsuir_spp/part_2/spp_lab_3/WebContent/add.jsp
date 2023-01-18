<%@ page language="java" contentType="text/html; charset=US-ASCII"
    pageEncoding="US-ASCII"%>
<%@ taglib uri="/struts-tags" prefix="s"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
<meta http-equiv="Content-Type" content="text/html; charset=US-ASCII">
<title>spp_lab_3</title>
</head>
<body>
<s:include value="welcome.jsp"></s:include>
<div class="container">
<s:form action="add">
    <div class="mb-3">
        <s:textfield name="name" label="Order name" cssClass="form-control"></s:textfield>
    </div>
    <div class="mb-3">
        <s:submit value="Add" cssClass="form-control"></s:submit>
    </div>
</s:form>
</div>
</body>
</html>