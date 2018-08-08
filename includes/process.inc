<?php

/**
 * @file process.inc
 */

/**
 * Implements hook_process_html().
 */
function govstrap_process_html(&$variables, $hook) {
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
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
 * Implements hook_process_page().
 */
function govstrap_process_page(&$variables) {
  $variables['active_page_parent'] = _get_active_page_parent();
}

/**
 * Implements hook_process_block().
 */
function govstrap_process_block(&$variables, $hook) {
  // Drupal 7 should use a $title variable instead of $block->subject.
  $variables['title'] = isset($variables['block']->subject) ? $variables['block']->subject : '';
}

function _get_active_page_parent() {
  // Determine current page's parent
  $active_page_parent = '';
  $active_trail = menu_get_active_trail();
  if (is_array($active_trail)) {
    if (count($active_trail) == 2) {
      $parent = prev($active_trail);
    }
    if (count($active_trail) > 2) {
      $parent = $active_trail[1];
    }
    if ($parent['link_title']) {
      $active_page_parent = '<ul class="menu">';
      $active_page_parent .= '<li class="leaf active-trail">';
      $active_page_parent .= l($parent['link_title'], $parent['link_path'], array('attributes' => array('class' => 'active-trail')));
      $active_page_parent .= '</li></ul>';
    }
    if ($parent['title'] == 'Home') {
      $active_page_parent = '<ul class="menu">';
      $active_page_parent .= '<li class="leaf active-trail">';
      $active_page_parent .= menu_get_active_title();
      $active_page_parent .= '</li></ul>';
    }
  }
  return $active_page_parent;
}
