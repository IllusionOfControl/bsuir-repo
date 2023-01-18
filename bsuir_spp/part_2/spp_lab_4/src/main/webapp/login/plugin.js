(function( $ ){

    $.fn.addCeil = function(text) {
        return this.each(function() {
            var $this = $(this);
            var td = $('<td>');
            td.text(text);
            $this.append(td);
        });
    };

    $.fn.addRemoveBtn = function(id) {
        var $this = $(this);
        $this.append('<td><button class="removeVisit" data-visit="' + id +'">Remove</button></td>')
    };
})( jQuery );