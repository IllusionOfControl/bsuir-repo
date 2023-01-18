<%@ page language="java" contentType="text/html; charset=US-ASCII"
         pageEncoding="US-ASCII"%>
<%@ taglib uri="/struts-tags" prefix="s"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=US-ASCII">
    <title>LR4</title>
</head>
<body>
<s:include value="welcome.jsp"></s:include>

<div class="container">
<s:form action="delete">
    <s:textfield name="id" label="Order's id" cssClass="form-control"></s:textfield>
    <s:submit value="Delete" cssClass="form-control"></s:submit>
</s:form>
</div>

</body>
</html>