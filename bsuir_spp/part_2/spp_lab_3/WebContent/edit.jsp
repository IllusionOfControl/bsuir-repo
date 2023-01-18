<%@ page language="java" contentType="text/html; charset=US-ASCII"
    pageEncoding="US-ASCII"%>
<%@ taglib uri="/struts-tags" prefix="s"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=US-ASCII">
<title>spp_lab_3</title>
</head>
<body>
<s:include value="welcome.jsp"></s:include>

<div class="container">
<s:form action="edit">
    <s:textfield name="id" label="Order Id to update" cssClass="form-control"></s:textfield>
    <s:textfield name="name" label="Order name" cssClass="form-control"></s:textfield>
    <s:checkbox name="done" label="Vacation" cssClass="form-check-input"></s:checkbox>
    <s:submit value="Update" cssClass="form-control"></s:submit>
</s:form>
</div>

</body>
</html>