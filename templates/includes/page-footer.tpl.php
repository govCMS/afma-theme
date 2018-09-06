<?php if (!empty($page['footer'])): ?>
  <footer id="footer" class="footer">
    <div class="<?php print $container_class; ?>">
        <div class="row">
            <div class="col-md-12">
                <div class="explore-the-site">
                    <a href="#" title="explore the site" class="explore-the-site-link"><i class="fas fa-angle-down"></i>  Explore the site  <i class="fas fa-angle-down"></i></a>
                </div>
              <?php print render($page['footer']); ?>
            </div>
        </div>
    </div>
  </footer>
<?php endif; ?>

<?php if (!empty($page['footer_menu'])): ?>
  <footer id="footer-menu" class="footer-menu">
    <div class="<?php print $container_class; ?>">
        <div class="row">
            <div class="col-lg-6 footer-bottom-stay-connected">
                <div class="social-links">
                    Stay connected:
                    <a href="https://www.facebook.com/AustralianFisheriesManagementAuthority/" target="_blank" title="AFMA Facebook" class="mx-1 afma-facebook-redirect"><i class="fab fa-facebook-square"></i></a>
                    <a href="https://www.youtube.com/user/TheAFMAComms" title="AFMA Youtube" class="mx-1 afma-youtube-redirect"><i class="fab fa-youtube"></i></a>
                </div>
            </div>

            <div class="col-lg-6 footer-bottom-menu">
              <?php print render($page['footer_menu']); ?>
            </div>
        </div>
    </div>
  </footer>
<?php endif; ?>