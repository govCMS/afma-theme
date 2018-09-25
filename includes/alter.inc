<?php

/**
 * @file
 * alter.inc
 */

/**
 * Implements hook_css_alter().
 */
function govstrap_css_alter(&$css) {
  // Exclude css
  if (!empty($excludes)) {
    $css = array_diff_key($css, drupal_map_assoc($excludes));
  }
}

/**
 * Implements hook_js_alter().
 */
function govstrap_js_alter(&$js) {
  $theme_path = drupal_get_path('theme', 'govstrap');

  // Ensure jQuery Once is always loaded.
  // @see https://drupal.org/node/2149561
  if (empty($js['misc/jquery.once.js'])) {
    $jquery_once = drupal_get_library('system', 'jquery.once');
    $js['misc/jquery.once.js'] = $jquery_once['js']['misc/jquery.once.js'];
    $js['misc/jquery.once.js'] += drupal_js_defaults('misc/jquery.once.js');
  }

  // Replace jQuery with higher version.
  if (theme_get_setting('jquery_replace_enabled')) {
    // jQuery update.
    $node_admin_paths = array(
      'node/*/edit',
      'node/add',
      'node/add/*',
      'panels/*',
      'ctools/*'
    );
    $replace_jquery = TRUE;
    if (path_is_admin(current_path())) {
      $replace_jquery = FALSE;
    }
    else {
      foreach ($node_admin_paths as $node_admin_path) {
        if (drupal_match_path(current_path(), $node_admin_path)) {
          $replace_jquery = FALSE;
        }
      }
    }
    // Swap out jQuery to use an updated version of the library.
    if ($replace_jquery) {
      $js['misc/jquery.js']['data'] = $theme_path . '/js/jquery.min.js';
      // Relace version.
      $js['misc/jquery.js']['version'] = '3.3.1';
    }
  }

  // Exclude js
  if (!empty($excludes)) {
    $js = array_diff_key($js, drupal_map_assoc($excludes));
  }
}

/**
 * Implements hook_js_callback_filter_xss_alter().
 */
function govstrap_js_callback_filter_xss_alter(array &$allowed_tags = array()) {
  $allowed_tags[] = 'button';
}

/**
 * Search block form alter.
 */
function govstrap_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_api_page_search_form_default_search') {
    // Update search keys filed attributes.
    $form['keys_1']['#title'] = 'Search';
    $form['keys_1']['#attributes']['placeholder'] = t('Search');
    $form['keys_1']['#attributes']['autocomplete'] = 'off';
    // Update submit button style.
    $form['submit_1']['#value'] = decode_entities('') . ' Search';
  }

  if ($form_id == 'search_block_form') {
    // Update search keys filed attributes.
    $form['search_block_form']['#attributes']['title'] = 'Search';
    $form['search_block_form']['#attributes']['class'][] = 'form-control';
    $form['search_block_form']['#attributes']['placeholder'] = t('Find what you\'re looking for...');
    $form['search_block_form']['#attributes']['autocomplete'] = 'off';
    // Update submit button style.
    $form['actions']['submit']['#value'] = decode_entities('');
    $form['actions']['submit']['#attributes']['aria-label'] = 'Search';
    $form['#submit'][0] = 'govstrap_search_block_form_submit';
  }

  if ($form_id == 'search_api_page_search_form') {
    $form['form']['keys_1']['#title_display'] = 'none';
    $form['form']['keys_1']['#attributes']['class'][] = 'form-control';
    $form['form']['keys_1']['#attributes']['placeholder'] = t('Find what you\'re looking for...');
    $form['form']['submit_1']['#value'] = decode_entities('') . ' Search';
  }
}

function govstrap_search_block_form_submit ($form, &$form_state) {
  $keys = $form_state['values']['search_block_form'];
  if (empty($keys)) {
    form_set_error('keys', t('Please enter some keywords.'));
  } else {
    $form_state['redirect'] = array('/search/'.$keys);
  }
}

/**
 * Alter the menu tree and its configuration before the tree is rendered.
 *
 * @param $tree
 *   An array containing the unrendered menu tree.
 * @param $config
 *   An array containing the configuration of the tree.
 */
function govstrap_menu_block_tree_alter(&$tree, &$config) {
  if ($config['admin_title'] == 'AFMA sidebar nav (main menu)'){
    foreach ($tree as $key => $value) {
      if ($tree[$key]['link']['in_active_trail']) {
        _govstrap_recursivly_activate_active_menu_item_s_all_sibling_menu_items($tree[$key]['below']);
      }
    }
  }
}

function _govstrap_recursivly_activate_active_menu_item_s_all_sibling_menu_items(&$tree){
  foreach ($tree as $key => $value) {
    $tree[$key]['link']['hidden'] = 0;
    if ($tree[$key]['link']['in_active_trail'] && !empty($tree[$key]['below'])) {
      _govstrap_recursivly_activate_active_menu_item_s_all_sibling_menu_items($tree[$key]['below']);
    }
  }
}