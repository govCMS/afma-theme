!function(o,e){"use strict";Drupal.behaviors.govstrap={attach:function(e,t){o(document).ready(function(){o("#menu").mmenu({extensions:["pagedim-black","position-right"]});var e=o("#search-btn"),t=o("#close-btn"),n=o("#mob-search-popup");o(e).on("click",function(){o(n).fadeIn(),o("body").css("overflow","hidden")}),o(t).on("click",function(){o(n).fadeOut(),o("body").css("overflow","auto")}),o(".explore-the-site .explore-the-site-link").click(function(e){e.preventDefault(),o(".region-footer").slideToggle(220),o(this).toggleClass("explore-open")}),o('a[data-toggle="lightbox"]').click(function(e){e.preventDefault(),o(this).ekkoLightbox({alwaysShowClose:!0})}),o('[data-toggle="tooltip"]').tooltip()})}}}(jQuery);