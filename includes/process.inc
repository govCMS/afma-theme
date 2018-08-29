<?php

/**
 * @file process.inc
 */

/**
 * Implements hook_process_html().
 */
function govstrap_process_html(&$variables, $hook) {
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);

  // Replace public file path token with public file path
  //$path_to_public_files = variable_get('file_public_path', 'sites/default/files');
  $path_to_public_files = _govstrap_get_public_file_path_from_system();
  $path_to_theme = path_to_theme();
  $search = [
    '[afma-public-file-path]',
    '%5Bafma-public-file-path%5D',
    '[path_to_theme]',
    '%5Bpath_to_theme%5D',
  ];
  $replace = [
    $path_to_public_files,
    $path_to_public_files,
    $path_to_theme,
    $path_to_theme,
  ];
  $variables['page'] = str_replace($search, $replace, $variables['page']);
}

function _govstrap_get_public_file_path_from_system(){
  global $base_url;
  return rtrim(str_replace($base_url, '', file_create_url('public://')), '/');
}

/**
 * Override or insert variables in the html_tag theme function.
 */
function govstrap_process_html_tag(&$variables) {
  $tag = &$variables['element'];

  if ($tag['#tag'] == 'style' || $tag['#tag'] == 'script') {
    // Remove redundant CDATA comments.
    unset($tag['#value_prefix'], $tag['#value_suffix']);

    // Remove redundant type attribute.
    if (isset($tag['#attributes']['type']) && $tag['#attributes']['type'] !== 'text/ng-template' && $tag['#attributes']['type'] !== 'application/ld+json') {
      unset($tag['#attributes']['type']);
    }

    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

/**
 * Implements hook_process_block().
 */
function govstrap_process_block(&$variables, $hook) {
  // Drupal 7 should use a $title variable instead of $block->subject.
  $variables['title'] = isset($variables['block']->subject) ? $variables['block']->subject : '';
}

/**
 * Implements hook_process_page().
 */
function govstrap_process_page(&$variables) {

  // Make search form available to page.tpl.php
  $search_box = drupal_get_form('search_block_form');
  $variables['search_box'] = drupal_render($search_box);

  $search_box_mobile =  drupal_get_form('search_block_form');
  //$search_box_mobile["search_block_form"]["#id"] = $search_box_mobile["search_block_form"]["#id"].'--mobile';
  $variables['search_box_mobile'] = drupal_render($search_box_mobile);

  $header_links =  module_invoke('menu_block', 'block_view', '2');
  $variables['header_links_block'] = $header_links['content'];

  // Accessibility settings.
  $variables['skip_link_anchor'] = check_plain(theme_get_setting('govstrap_skip_link_anchor'));
  $variables['skip_link_text'] = check_plain(theme_get_setting('govstrap_skip_link_text'));
  $variables['home_page_h1'] = check_plain(theme_get_setting('home_page_h1'));
  //$variables['active_page_parent'] = _get_active_page_parent();
}