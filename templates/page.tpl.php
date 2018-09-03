<?php
/**
 * @file
 * page.tpl.php - Returns the HTML for a single Drupal page.
 */
?>
<div class="page">
    <!-- page mobile header -->
  <?php include 'includes/page-header--mobile.tpl.php'; ?>
    <!-- /page mobile header -->
    <div class="mm-content">
        <!-- page header -->
      <?php include 'includes/page-header.tpl.php'; ?>
        <!-- /page header -->

        <!-- page banner -->
        <div class="banner slim-line bg-dark-blue text-white theme-color-gradient-after">
            <div class="bg-img-others"
                 style="background-size: contain; background-position-x: 100%; background-image: url(/<?php print path_to_theme(); ?>/img/banners/afma-banner-01.png)">
                <div class="container">
                    <div class="row">
                        <div class="col-lg-12 py-5">
                          <?php if (!empty($breadcrumb)): ?>
                              <nav aria-label="breadcrumb"
                                   class="breadcrumbs">
                                <?php print $breadcrumb; ?>
                              </nav>
                          <?php endif ?>
                            <div class="text">
                                <div class="accent-others text-white">
                                  <?php print render($title_prefix); ?>
                                    <h1 class="mb3"><?php print $title; ?></h1>
                                  <?php print render($title_suffix); ?>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <!-- /page banner -->

        <div class="bg-white">
          <?php if (!empty($page['highlighted'])): ?>
              <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
          <?php endif; ?>
          <?php if ($messages): ?>
              <div class="system-alert">
                <?php print $messages; ?>
              </div>
          <?php endif; ?>
            <div class="container py-5">
                <div class="row">
                    <!-- main page content -->
                    <div class="<?php print $content_column_class; ?> pb-5">

                        <section id="main-content-section" role="main">
                            <a id="main-content"></a>
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
                    </div>
                    <!-- /main page content -->
                    <!-- sidebar right -->
                  <?php if (!empty($page['sidebar_right'])): ?>
                      <div class="col-lg-3 offset-lg-1">
                        <?php if ($active_page_parent): ?>
                            <h3 class="font-family2 mb-4 h4">
                                <a href="/<?php print $active_page_parent['link_path']; ?>"
                                   class="theme-color theme-color-hover">&nbsp;
                                    <i class="fal fa-arrow-left float-left line-height-inherit"></i>
                                  <?php print $active_page_parent['link_title']; ?>
                                </a>
                            </h3>
                        <?php endif; ?>
                        <?php print render($page['sidebar_right']); ?>
                      </div>
                  <?php endif; ?>
                    <!-- /sidebar right -->

                </div>
            </div>
        </div>
        <!-- page footer -->
      <?php include 'includes/page-footer.tpl.php'; ?>

    </div>
</div>

<!-- page mobile menu -->
<?php include 'includes/page-menu--mobile.tpl.php'; ?>

