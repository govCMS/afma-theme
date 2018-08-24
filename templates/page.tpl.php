<?php
/**
 * @file
 * page.tpl.php - Returns the HTML for a single Drupal page.
 */
?>
<?php include 'includes/header.tpl.php'; ?>

<nav id="navigation" class="<?php print $container_class; ?> clearfix">
  <?php print render($page['navigation']); ?>
</nav><!-- /#navigation -->

<main>
  <div id="main" class="main-container <?php print $container_class; ?>">
    <?php if (!empty($page['highlighted'])): ?>
      <div class="highlighted"><?php print render($page['highlighted']); ?></div>
    <?php endif; ?>
    <?php print $messages; ?>
    <div id="content" class="row">
      <?php if (!empty($page['sidebar_first'])): ?>
        <aside class="col-sm-3" role="complementary">
          <?php print render($page['sidebar_first']); ?>
        </aside>  <!-- /#sidebar-first -->
      <?php endif; ?>
      <section id="main-content-section" class="<?php print $content_column_class; ?>" role="main">
        <div id="main-content"></div>
        <?php print render($title_prefix); ?>
        <?php if (!empty($title)): ?>
          <h1 class="page-header"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php if (!empty($tabs)): ?>
          <?php print render($tabs); ?>
        <?php endif; ?>
        <?php if (!empty($page['help'])): ?>
          <?php print render($page['help']); ?>
        <?php endif; ?>
        <?php if (!empty($action_links)): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>
        <div id="page-content">
          <?php print render($page['content']); ?>
        </div>
      </section>
      <?php if (!empty($page['sidebar_second'])): ?>
        <aside class="col-sm-3" role="complementary">
            <?php if($active_page_parent): ?>
                <div class="menu-block-wrapper menu-block-active-parent menu-name-main-menu">
                  <?php print $active_page_parent; ?>
                </div>
            <?php endif; ?>
          <?php print render($page['sidebar_second']); ?>
        </aside>  <!-- /#sidebar-second -->
      <?php endif; ?>
    </div>
  </div>
</main>

<?php include 'includes/footer.tpl.php'; ?>
