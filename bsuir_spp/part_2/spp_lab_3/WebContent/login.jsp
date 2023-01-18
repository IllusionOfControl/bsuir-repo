<%@ page language="java" contentType="text/html; charset=US-ASCII"
    pageEncoding="US-ASCII"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%-- Using Struts2 Tags in JSP --%>
<%@ taglib uri="/struts-tags" prefix="s"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=US-ASCII">
<title>spp_lab_3</title>
	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
	<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
</head>
<body>
<div class="container">
<h3>Welcome User, please login below</h3>
<s:form action="login">
	<s:textfield name="name" label="User Name" cssClass="form-control"></s:textfield>
	<s:textfield name="password" label="Password" type="password" cssClass="form-control"></s:textfield>
	<s:submit value="Login" cssClass="form-control"></s:submit>
</s:form>

<h3>Or register</h3>
<s:form action="register">
	<s:textfield name="name" label="User Name" cssClass="form-control"></s:textfield>
	<s:textfield name="password" label="Password" type="password" cssClass="form-control"></s:textfield>
	<s:submit value="Register" cssClass="form-control"></s:submit>
</s:form>
</div>
</body>
</html>