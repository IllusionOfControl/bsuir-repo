<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<h1>Movie list</h1>
<ul>
    <c:forEach items="${movieList}" var="movie">
        <li><c:out value="${movie}"/></li>
    </c:forEach>
</ul>