<?php
/**
 * @file
 * page-header.tpl.php - Returns the HTML of the page header
 */
?>

<header class="header bg-white">
    <div class="container">
      <?php if (!empty($page['header'])): ?>
          <div class="row">
            <?php print render($page['header']); ?>
          </div>
      <?php endif; ?>
        <div class="row">
            <div class="col-lg-12">
                <div class="top">
                    <div class="row">
                        <div class="col-md-6">
                            <div class="afma-header-logo-container">
                                <a href="/" aria-label="homepage">
                                    <img src="/<?php print path_to_theme(); ?>/img/logo-afma.svg" class="afma-logo" alt="Australian Fisheries Management Authority"/>
                                </a>
                            </div>
                            <div class="afma-header-crimfish-hotline">
                                <p class="p-info">CRIMFISH hotline <span class="afma-header-hotline-link"><a href="tel:1800274634"><i class="fal fa-phone fa-flip-horizontal"></i>1800 274 634</a></span></p>
                            </div>
                        </div>
                        <div class="col-md-6 text-right search-cluster">
                            <div class="afma-header-upper-links-container">
                                <ul class="menu afma-header-upper-links">
                                    <li class="first leaf"><a href="/" title="">About Us</a></li>
                                    <li class="leaf"><a href="/" title="" class="active">News and Media</a></li>
                                    <li class="leaf"><a href="/" title="">Careers</a></li>
                                    <li class="last leaf"><a href="/" title="" class="active">Contact Us</a></li>
                                </ul>
                            </div>
                          <?php print $search_box; ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="nav-bg">
        <div class="container">
            <div class="row">
                <div class="col-lg-12">
                    <nav id="navigation" class="<?php print $container_class; ?> clearfix">
                      <?php print render($page['navigation']); ?>
                    </nav><!-- /#navigation -->
                </div>
            </div>
        </div>
    </div>
</header>