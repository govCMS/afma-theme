/**
 * @file
 * A JavaScript file for the Site.
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.govstrap = {
    attach: function (context, settings) {
      $(document).ready(function () {
        // Smooth scropping to top
        $(window).scroll(function() {
          if($(this).scrollTop() != 0) {
            $("#to-top").fadeIn();
          } else {
            $("#to-top").fadeOut();
          }
        });
        $("#to-top").click(function() {
          $("body,html").animate({scrollTop:0},800);
        });
        // Append the opener link for mobile navigation
        $('.sf-accordion-toggle a').prepend('<i class="icon-menu"></i>');
        $('.sf-accordion > li.menuparent > a').prepend('<i class="icon-plus"></i>');
        // Toggle burger menu active state
        $('.sf-accordion-toggle a').click(function() {
          $('.sf-accordion-toggle a i').toggleClass('icon-menu');
          $('.sf-accordion-toggle a i').toggleClass('icon-cross');
        });
        $('.sf-accordion > li.menuparent > a').click(function() {
          $('.sf-accordion > li.menuparent > a').not(this).find('i.icon-minus').toggleClass('icon-plus').toggleClass('icon-minus');
          $(this).find('i').toggleClass('icon-plus').toggleClass('icon-minus');
        });
      });
      $('a[data-toggle="lightbox"]').click(function(event) {
        event.preventDefault();
        $(this).ekkoLightbox({
          alwaysShowClose: true,
        });
      });
    }
  };

})(jQuery, Drupal);
