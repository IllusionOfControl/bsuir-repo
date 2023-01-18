$(document).ready(function() {
    $(".login").click(function (event) {
        $.ajax({
            url: 'http://localhost:8080/web_war_exploded/register',         /* Куда отправить запрос */
            method: 'post',             /* Метод запроса (post или get) */
            dataType: 'json',          /* Тип данных в ответе (xml, json, script, html). */
            data: {
                name: $("#name").val(),
                password: $("#password").val()
            },     /* Данные передаваемые в массиве */
            success: function (data) {   /* функция которая будет выполнена после успешного запроса.  */
                window.location.replace("http://localhost:8080/web_war_exploded/login");
            },
            error: function (jqXHR, exception) {
                alert('User with this username exists');
            }
        });
    });
});