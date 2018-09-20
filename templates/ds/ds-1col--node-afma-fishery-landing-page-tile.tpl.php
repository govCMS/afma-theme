<?php

/**
 * @file
 * Display Suite 1 column template.
 */
?>
<?php
$link = $content['read_more_link']['#object']->path;
?>
  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
<a href="/<?php print $link['alias'];?>" class="card">
    <?php
    $species_image = render($content['field_feature_image']);
    if (empty($species_image)) {
      $species_image = '<img style="height: auto; max-width: 100%; flex-shrink: 0;" src="/'.path_to_theme().'/img/fisheries-placeholder.png" alt="placeholder image for fisheries" />';
    }
    ?>
      <?php print $species_image; ?>
    <div class="card-body">
      <?php print render($content['title']); ?>
    </div>
</a>

