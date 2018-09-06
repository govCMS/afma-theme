<?php

/**
 * @file
 * theme.inc
 */

/**
 * Implements theme_breadrumb().
 */
function govstrap_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    $page_type = arg(0);
    if ($page_type == 'node') {
      $node_id = arg(1);
      if (!empty($node_id) && is_numeric($node_id)) {
        $node = node_load(arg(1));
        switch ($node->type) {
          case 'webform':
            $breadcrumb[] = 'Form';
            $breadcrumb[] = $node->field_title['und'][0]['value'];
            break;
        }
      }
    }
    elseif ($page_type == 'search') {
      $breadcrumb = array('<a href="/">Home</a>', 'Search');
    }
    else {
      $breadcrumb[] = drupal_get_title();
    }

    $breadcrumbs = '<ol class="breadcrumb">';
    foreach ($breadcrumb as $key => $value) {
      $breadcrumbs .= '<li>' . $value . '</li>';
    }
    $breadcrumbs .= '</ol>';

    return $breadcrumbs;
  }
}

/**
 * Theme a menu item link.
 *
 * @param $variables
 *   An array of variables containing:
 *    - menu_item: The menu item array.
 *    - link_options: An array of link options.
 *
 * @ingroup themeable
 */
function govstrap_superfish_menu_item_link($variables) {
  $menu_item = $variables['menu_item'];
  $link_options = $variables['link_options'];

  if ($menu_item['link']['link_path'] == '<front>' && drupal_strtolower($menu_item['link']['title']) == 'home' ){
    $link_options['html'] = TRUE;
    $menu_item['link']['title'] = '<i class="fal fa-home"></i><span class="sr-only">Home</span>';
  }

  return l($menu_item['link']['title'], $menu_item['link']['href'], $link_options);
}

/**
 * Implements theme_menu_tree().
 */
function govstrap_menu_tree__menu_block__1($variables) {
  return '<ul>' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_link().
 */
function govstrap_menu_link__menu_block__1(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_tree().
 */
function govstrap_menu_tree__menu_block__3($variables) {

  $out_put = '';

  $children = element_children($variables['#tree']);

  if (!empty($variables['#tree'])
      && $variables['#tree'][$children[0]]['#href'] == '<front>'
      && $variables['#tree'][$children[0]]['#original_link']['plid'] == '0') {

    $item_num_per_row = 3;
    $i                = 1;
    foreach ($children as $child_key) {
      switch ($i % $item_num_per_row) {
        case 1:
          $out_put .= '<div class="row">' . $variables['#tree'][$child_key]['#children'];
          break;
        case 0:
          $out_put .= $variables['#tree'][$child_key]['#children'] . '</div>';
          break;
        default:
          $out_put .= $variables['#tree'][$child_key]['#children'];
          break;
      }
      ++$i;
    }
  }
  else {
    $out_put = '<ul class="menu">' . $variables['tree'] . '</ul>';
  }

  return $out_put;
}

/**
 * Implements theme_menu_link().
 */
function govstrap_menu_link__menu_block__3(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#original_link']['plid'] == 0){
    $item_num_per_row = 3;
    $element['#attributes']['class'][] = 'col-ms-12';
    $element['#attributes']['class'][] = 'col-md-' . (12/$item_num_per_row);
  }

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Default theme implementation for theme('crumbs_breadcrumb_link').
 *
 * @param array $item
 *
 * @return string
 */
function govstrap_crumbs_breadcrumb_link(array $item) {

  $prefix = '';

  if ($item['href'] == '<front>'){
    $prefix = '<div class="afma-breadcrum-prefix pr-2">You are here:</div>';
    $item['localized_options']['html'] = TRUE;
    $item['title'] = '<i class="fal fa-home"></i><span class="sr-only">Home</span>';
  }

  if ('<nolink>' === $item['href']) {
    $out_put = $prefix . check_plain($item['title']);
  }
  else {
    $options = isset($item['localized_options']) ? $item['localized_options'] : array();
    $out_put = $prefix . l($item['title'], $item['href'], $options);
  }

  return $out_put;
}