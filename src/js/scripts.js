/**
 * @file
 * A JavaScript file for the Site.
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.govstrap = {
    attach: function (context, settings) {

      // Smooth scropping to top
      $(window).scroll(function () {
        if ($(this).scrollTop() != 0) {
          $("#to-top").fadeIn();
        } else {
          $("#to-top").fadeOut();
        }
      });
      $("#to-top").click(function () {
        $("body,html").animate({scrollTop: 0}, 500);
      });

      $(document).ready(function () {
        var animationDuration = 220;

        // MMenu behaviour
        $("#menu").mmenu({
          "extensions": [
            "pagedim-black",
            "position-right"
          ]
        });

        // Slider
        $(".rev_slider ul").slick({
          dots: true,
          infinite: true,
          autoplay: true,
          autoplaySpeed: 5000,
          speed: 300,
          slidesToShow: 1,
          adaptiveHeight: true,
          arrows: true,
        });

        // Mobile search button behaviour
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

        // Explore the site (footer) behaviour
        $(".explore-the-site .explore-the-site-link").click(function(e) {
          e.preventDefault();
          $(".region-footer").slideToggle(animationDuration);
          $(this).toggleClass("explore-open");
        });

        // Lightbox behaviour
        $('a[data-toggle="lightbox"]').click(function(event) {
          event.preventDefault();
          $(this).ekkoLightbox({
            alwaysShowClose: true,
          });
        });

        // Tooltip behaviour
        $('[data-toggle="tooltip"]').tooltip();
      });
    }
  };

})(jQuery, Drupal);
