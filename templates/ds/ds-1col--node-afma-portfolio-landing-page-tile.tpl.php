<?php

/**
 * @file
 * Display Suite 1 column template.
 */
?>
<?php
$link = $content['node_link']['#object']->path;
?>



  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
<a href="/<?php print $link['alias'];?>" class="card">
      <?php print render($content['field_feature_image']); ?>
    <div class="card-body">
      <?php print render($content['title']); ?>
    </div>
</a>

