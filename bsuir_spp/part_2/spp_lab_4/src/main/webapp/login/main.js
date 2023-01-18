// When the page is fully loaded...
$(document).ready(function() {

    $("#addBtn").click(function(event) {
        var buttonID = event.target.id;

        $.ajax({
            url: 'http://localhost:8080/web_war_exploded/main',         /* Куда отправить запрос */
            method: 'post',             /* Метод запроса (post или get) */
            dataType: 'json',          /* Тип данных в ответе (xml, json, script, html). */
            data: {
                description: $( "#description" ).val(),
                patientId: $( "select#patientId option:checked" ).val()
            },     /* Данные передаваемые в массиве */
            success: function(data){   /* функция которая будет выполнена после успешного запроса.  */
                var body = $('#visits tbody');
                var tr = $('<tr class="visitTd_' + data["id"] + '">');
                tr.addCeil(data["id"])
                    .addCeil(data["displayDate"])
                    .addCeil(data["description"])
                    .addCeil(data["patientName"])
                    .addRemoveBtn(data["id"]);
                body.append(tr);
            },
            error: function (jqXHR, exception) {
                alert('Error');
            }
        });
    });

    $(document).on ("click", ".removeVisit", function (event) {
        var id = event.target.dataset.visit
        $.ajax({
            url: 'http://localhost:8080/web_war_exploded/main',         /* Куда отправить запрос */
            method: 'delete',             /* Метод запроса (post или get) */
            dataType: 'json',          /* Тип данных в ответе (xml, json, script, html). */
            data: {
                id: id
            },
            success: function(data){   /* функция которая будет выполнена после успешного запроса.  */
                $(".visitTd_" + id).remove();
            },
            error: function (jqXHR, exception) {
                alert('Error');
            }
        });
    });
});