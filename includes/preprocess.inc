<?php

/**
 * @file
 * preprocess.inc
 */

define('AFMA_PUBLIC_FILE_PATH_TOKEN', '[afma-public-file-path]');

/**
 * Implements hook_preprocess_html().
 * Override or insert variables into the html template.
 *
 * @param $variables
 * @param $hook
 */
function govstrap_preprocess_html(&$variables, $hook) {
  // Set common variables.
  $variables['base_path'] = base_path();
  $variables['path_to_govstrap'] = drupal_get_path('theme', 'govstrap');

  // Send X-UA-Compatible HTTP header to force IE to use the most recent
  // rendering engine or use Chrome's frame rendering engine if available.
  if (is_null(drupal_get_http_header('X-UA-Compatible'))) {
    drupal_add_http_header('X-UA-Compatible', 'IE=edge');
  }

  // IE8 support of HTML5 elements and media queries .
  $ie_script_s = array(
    '#browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE),
    '#tag' => 'script',
    '#attributes' => array(
      'type' => "text/javascript",
      'src' => './' . $variables['path_to_govstrap'] . '/js/modernizr.js',

    ),
  );
  drupal_add_html_head($ie_script_s, "govstrapmodernizr");

  // IE8 support of HTML5 elements and media queries.
  $ie_script_r = array(
    '#browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE),
    '#tag' => 'script',
    '#attributes' => array(
      'type' => "text/javascript",
      'src' => './' . $variables['path_to_govstrap'] . '/js/respond.js',
    ),
  );
  drupal_add_html_head($ie_script_r, "govstraprespond");

  if (theme_get_setting('fontawesome_enabled') && theme_get_setting('fontawesome_css_cdn')) {
    // Add fontawesome CDN file.
    $fontawesome = 'https://use.fontawesome.com/releases/' . theme_get_setting('fontawesome_css_cdn') . '/js/all.js';
    drupal_add_js($fontawesome, array('type' => 'external', 'defer' => TRUE));
  }

  // Accessibility settings.
  $variables['skip_link_anchor'] = check_plain(theme_get_setting('govstrap_skip_link_anchor'));
  $variables['skip_link_text'] = check_plain(theme_get_setting('govstrap_skip_link_text'));

  // Attributes for html element.
  $variables['html_attributes_array'] = array(
    'lang' => $variables['language']->language,
    'dir' => $variables['language']->dir,
  );

  // Return early, so the maintenance page does not call any of the code below.
  if ($hook != 'html') {
    return;
  }

  // Serialize RDF Namespaces into an RDFa 1.1 prefix attribute.
  if ($variables['rdf_namespaces']) {
    $prefixes = array();
    foreach (explode("\n  ", ltrim($variables['rdf_namespaces'])) as $namespace) {
      // Remove xlmns: and ending quote and fix prefix formatting.
      $prefixes[] = str_replace('="', ': ', substr($namespace, 6, -1));
    }
    $variables['rdf_namespaces'] = ' prefix="' . implode(' ', $prefixes) . '"';
  }

  // Replace public file path token with public file path
  //$path_to_public_files = variable_get('file_public_path', 'sites/default/files');
  $path_to_public_files = _govstrap_get_public_file_path_from_system();
  //  $path_to_theme = path_to_theme();
  //  $search = array('[path_to_public_files]', '%5Bpath_to_public_files%5D', '[path_to_theme]', '%5Bpath_to_theme%5D');
  //  $replace = array($path_to_public_files, $path_to_public_files, $path_to_theme, $path_to_theme);
  $variables['page'] = str_replace(AFMA_PUBLIC_FILE_PATH_TOKEN, $path_to_public_files, $variables['page']);
}

function _govstrap_get_public_file_path_from_system(){
  global $base_url;
  return rtrim(str_replace($base_url, '', file_create_url('public://')), '/');
}

/**
 * Implements hook_preprocess_page().
 *
 * @param $variables
 *
 * @see page.tpl.php
 */
function govstrap_preprocess_page(&$variables) {
  // Add pathToTheme to Drupal.settings in JS.
  drupal_add_js('jQuery.extend(Drupal.settings, { "pathToTheme": "' . path_to_theme() . '" });', 'inline');

  // Theme suggestions.
  $header = drupal_get_http_header("status");
  if ($header === "404 Not Found") {
    $variables['theme_hook_suggestions'][] = 'page__404';
  }
  if ($header === "403 Forbidden") {
    $variables['theme_hook_suggestions'][] = 'page__403';
  }

  // Set page container columns.
  $variables['container_class'] = 'container';

  // Calculate container columns with sidebar.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = 'col-sm-6';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = 'col-sm-9';
  }
  else {
    $variables['content_column_class'] = 'col-sm-12';
  }
}

/**
 * Implements hook_preprocess_node().
 */
function govstrap_preprocess_node(&$variables, $hook) {
  // Add a theme hook suggestion for type and view mode.
  $variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__' . $variables['view_mode'];

  // _template_preprocess_node__{content_type}__{view mode}
  $possible_hook_name = '_' . __FUNCTION__ . '__' . $variables['type'] . '__' . $variables['view_mode'];

  if (function_exists($possible_hook_name)) {
    $possible_hook_name($variables);
  }
}

/**
 * Implements hook_preprocess_block().
 */
function govstrap_preprocess_block(&$variables, $hook) {
  // Use a template with no wrapper for the page's main content.
  if ($variables['block_html_id'] == 'block-system-main') {
    $variables['theme_hook_suggestions'][] = 'block__no_wrapper';
  }

  $variables['title_attributes_array']['class'][] = 'block-title';

  // Block template per bean type.
  if ($variables['block']->module === 'bean') {
    $beans = $variables['elements']['bean'];
    $bean_keys = element_children($beans);
    $bean = $beans[reset($bean_keys)];
    // Add template suggestions for bean types.
    $variables['theme_hook_suggestions'][] = 'block__bean__' . $bean['#bundle'];
  }
}

/**
 * Implements hook_preprocess_entity().
 */
function govstrap_preprocess_entity(&$variables) {
  // _template_preprocess_entity__{entity_type}__{bundle_machine_name}
  $possible_hook_name = '_' . __FUNCTION__ . '__' . $variables['entity_type'] . '__' . $variables['elements']['#bundle'];

  if (function_exists($possible_hook_name)) {
    $possible_hook_name($variables);
  }
}

/**
 * Implements hook_preprocess_field().
 */
function govstrap_preprocess_field(&$variables) {
  // _template_preprocess_field__{field_name}
  $possible_hook_name = '_' . __FUNCTION__ . '__' . $variables['element']['#field_name'];

  if (function_exists($possible_hook_name)) {
    $possible_hook_name($variables);
  }
}

/**
 * Implements template_preprocess_taxonomy_term().
 */
function govstrap_preprocess_taxonomy_term(&$variables) {
  // _template_preprocess_taxonomy_term__{vocabulary_machine_name}
  $possible_hook_name = '_' . __FUNCTION__ . '__' . $variables['vocabulary_machine_name'];

  if (function_exists($possible_hook_name)) {
    $possible_hook_name($variables);
  }
}

/******************** Internal functions called by preprocess hooks *****************/

/**
 * Called by govstrap_preprocess_node()
 */
function _govstrap_preprocess_node__afma_portfolio__full(&$variables) {

  // If there is any body summary, we added into top section before body rendered.
  if (!empty($variables['body'][0][safe_summary])){
    $variables['content'] = [
      'body_summary' => [
        '#type' => 'container',
        '#attributes' => [
          'class' => 'afma-portfolio-body-summary',
        ],
        'markup' => [
          '#type' => 'markup',
          '#markup' => $variables['body'][0][safe_summary],
        ],
      ],
    ] + $variables['content'];
  }
}

/**
 * Called by govstrap_preprocess_entity()
 */
function _govstrap_preprocess_entity__paragraphs_item__afma_species_catch_limit_count(&$variables) {

  $theme_path =  drupal_get_path('theme', 'govstrap');

  drupal_add_js($theme_path . '/js/countUp.min.js', 'file');
  drupal_add_js($theme_path . '/js/countUp_usage.js', 'file');
}

/**
 * Called by govstrap_preprocess_entity()
 */
function _govstrap_preprocess_entity__paragraphs_item__afma_sustainability_status_bar(&$variables) {

  if (!empty($variables['paragraphs_item']->field_afma_sbar_pp_description[LANGUAGE_NONE][0]['safe_value'])){
    $variables['attributes_array']['data-toggle'] = 'tooltip';
    $variables['attributes_array']['data-placement'] = 'top';
    $variables['attributes_array']['title'] = $variables['paragraphs_item']->field_afma_sbar_pp_description[LANGUAGE_NONE][0]['safe_value'];

    //@TODO Shouldn't be hard-coded
    $variables['attributes_array']['style'] = 'cursor: pointer;';
  }
}

/**
 * Called by govstrap_preprocess_field()
 */
function _govstrap_preprocess_field__field_afma_sclc_count_num(&$variables) {

  if (isset($variables['element']['#object']->field_afma_sclc_cl_unit[LANGUAGE_NONE][0]['value'])) {
    $variables['attributes_array']['afma-count-unit'] =
      $variables['element']['#object']->field_afma_sclc_cl_unit[LANGUAGE_NONE][0]['value'];
  }
}

/**
 * Called by govstrap_preprocess_taxonomy_term()
 */
function _govstrap_preprocess_taxonomy_term__seasons(&$variables) {
  // Do not display as link
  $variables['page'] = TRUE;
}

/**
 * Called by govstrap_preprocess_taxonomy_term()
 */
function _govstrap_preprocess_taxonomy_term__sustainability_status(&$variables) {
  // Do not display as link
  $variables['page']    = TRUE;
  $variables['content'] = [
    '#type'   => 'markup',
    '#markup' => $variables['name'],
  ];

  // Insert term-specific classes
  $variables['classes_array'][] = 'afma-sustainability-status-' . drupal_html_class($variables['name']);
}