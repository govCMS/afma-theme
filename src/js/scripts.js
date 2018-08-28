/**
 * @file
 * A JavaScript file for the Site.
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.govstrap = {
    attach: function (context, settings) {
      $(document).ready(function () {
        $("#menu").mmenu({
          "extensions": [
            "pagedim-black",
            "position-right"
          ]
        });

        var searchBtn = $('#search-btn');
        var searchCloseBtn = $('#close-btn');
        var searchPopup = $('#mob-search-popup');

        $(searchBtn).on('click', function(){
          $(searchPopup).fadeIn();
          $('body').css('overflow', 'hidden');
        });

        $(searchCloseBtn).on('click', function(){
          $(searchPopup).fadeOut();
          $('body').css('overflow', 'auto');
        });
      });
      $('a[data-toggle="lightbox"]').click(function(event) {
        event.preventDefault();
        $(this).ekkoLightbox({
          alwaysShowClose: true,
        });
      });
      $('[data-toggle="tooltip"]').tooltip();
    }
  };

})(jQuery, Drupal);
