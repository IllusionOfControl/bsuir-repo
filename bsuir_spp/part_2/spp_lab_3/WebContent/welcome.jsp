<%@ taglib prefix="s" uri="/struts-tags" %>
<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<!DOCTYPE html>
<html>
<head>
    <title>spp_lab_3</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
</head>
<body>
<div class="container">
    <br/>
    <h1>The order list system</h1>
    <div class="btn-group" role="group">
        <button class="btn btn-outline-primary"><s:a action="table">Show table</s:a></button>
        <button class="btn btn-outline-primary"><s:a action="addPage">Add new order</s:a></button>
        <button class="btn btn-outline-primary"><s:a action="editPage">Edit order</s:a></button>
        <button class="btn btn-outline-primary"><s:a action="deletePage">Delete order</s:a></button>
    </div>
</div>
</body>
</html>