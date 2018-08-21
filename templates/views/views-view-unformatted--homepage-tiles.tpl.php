<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
    <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="row" id="homepage-tiles">
  <?php foreach ($rows as $id => $row): ?>
      <article class="col-sm-6">
          <div class="homepage-tile">
            <?php print $row; ?>
          </div>
      </article>
  <?php endforeach; ?>
</div>

