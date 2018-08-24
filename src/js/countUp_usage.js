/**
 * @file
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.govstrap_countup = {
    attach: function (context, settings) {

      var count_options = {
        useEasing: true,
        useGrouping: true,
        separator: ',',
        decimal: '.',
      };

      $('.field-name-field-afma-sclc-count-num', context).each(function () {
        var unit = ' ' + (typeof $(this).attr('afma-count-unit') === undefined ? 'tonnes' : $(this).attr('afma-count-unit'));
        $(this).find('.field-item').each(function () {
          count_options['suffix'] = unit;
          // @see http://inorganik.github.io/countUp.js/
          var numAnim = new CountUp(this, 0, $(this).text(), 0, 2, count_options);
          if (!numAnim.error) {
            numAnim.start();
          }
        });
      });
    }
  };

})(jQuery, Drupal);