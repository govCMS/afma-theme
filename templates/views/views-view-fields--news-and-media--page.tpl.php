<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT
 *   output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field.
 *   Do not use var_export to dump this object, as it can't handle the
 *   recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to
 *   use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
    <div class="afma-news-listing-post-date col-lg-1 py-3">
    <span class="afma-news-listing-date-day">
      <?php print $fields['field_news_date']->content; ?>
    </span>
        <span class="afma-news-listing-date-month">
      <?php print $fields['field_news_date_1']->content; ?>
    </span>
        <span class="afma-news-listing-date-year">
      <?php print $fields['field_news_date_2']->content; ?>
    </span>
    </div>

  <?php if ($fields['field_image']): ?>
      <div class="afma-news-listing-title-body col-lg-8 py-4">
          <div class="afma-news-listing-title"><?php print $fields['title']->content; ?></div>
          <div class="afma-news-listing-body"> <?php print $fields['body']->content; ?></div>
      </div>
      <div class="afma-news-listing-image col-lg-3 px-0"><?php print $fields['field_image']->content; ?></div>
  <?php else: ?>
      <div class="afma-news-listing-title-body col-lg-11 py-4">
          <div class="afma-news-listing-title"><?php print $fields['title']->content; ?></div>
          <div class="afma-news-listing-body"> <?php print $fields['body']->content; ?></div>
      </div>
  <?php endif; ?>
