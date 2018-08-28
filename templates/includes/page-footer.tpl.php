<?php if (!empty($page['footer'])): ?>
  <footer id="footer" class="footer">
    <div class="<?php print $container_class; ?>">
      <?php print render($page['footer']); ?>
      <div class="visible-xs">
          <div class="logo">
              <a id="footer-logo-afma" href="http://www.afma.gov.au/"
                 title="Australian Fisheries Management Authority" target="_blank">
                  <img src="/<?php print path_to_theme(); ?>/img/logo-afma.svg" alt="AFMA logo"/>
              </a>
          </div>
          <div class="logo">
              <a id="footer-logo-tsra" href="http://www.tsra.gov.au/" title="Torres Strait Regional Authority" target="_blank">
                  <img src="/<?php print path_to_theme(); ?>/img/logo-tsra.png" alt="Torres Strait Regional Authority logo"/>
              </a>
          </div>
          <div class="logo no-right-margin">
              <a id="footer-logo-qld-gov" href="https://www.qld.gov.au/" title="Queensland Government" target="_blank">
                  <img src="/<?php print path_to_theme(); ?>/img/logo-qld-gov.svg" alt="Queensland Government logo"/>
              </a>
          </div>
      </div>
    </div>
  </footer>
<?php endif; ?>

<?php if (!empty($page['footer_menu'])): ?>
  <footer id="footer-menu" class="footer-menu">
    <div class="<?php print $container_class; ?>">
      <?php print render($page['footer_menu']); ?>
    </div>
  </footer>
<?php endif; ?>