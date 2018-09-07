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

/**
 * Implements theme_pager_link().
 */
function govstrap_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];
  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }
  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array(
        '@number' => $text,
      ));
    }
  }

  $attributes['class'] = array('page-link');

  // @todo l() cannot be used here, since it adds an 'active' class based on the
  //   path only (which is always the current path for pager links). Apparently,
  //   none of the pager links is active at any time - but it should still be
  //   possible to use l() here.
  // @see http://drupal.org/node/1410574
  $attributes['href'] = url($_GET['q'], array(
    'query' => $query,
  ));
  return '<a' . drupal_attributes($attributes) . '>' . $text . '</a>';
}

/**
 * Implements theme_pager().
 */
function govstrap_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = 7;
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);

  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;

  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;

  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;

  // max is the maximum page number
  $pager_max = $pager_total[$element];

  // End of marker calculations.
  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {

    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {

    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  // End of generation loop preparation.
  $li_first = theme('pager_first', array(
    'text' => t('First'),
    'element' => $element,
    'parameters' => $parameters,
  ));
  $li_previous = theme('pager_previous', array(
    'text' => '<i class="fal fa-arrow-left theme-color"></i><span class="sr-only">'.t('previous').'</span>',
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_next = theme('pager_next', array(
    'text' => '<i class="fal fa-arrow-right theme-color"></i><span class="sr-only">'.t('next').'</span>',
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_last = theme('pager_last', array(
    'text' => t('Last'),
    'element' => $element,
    'parameters' => $parameters,
  ));
  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array(
          'page-item',
        ),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array(
          'page-item',
        ),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array(
            'page-item',
            'page-ellipsis',
          ),
          'data' => '<span class="page-link">…</span>',
        );
      }

      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array(
              'page-item',
            ),
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => $pager_current - $i,
              'parameters' => $parameters,
            )),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array(
              'page-item',
              'current',
            ),
            'data' => '<span href="#" class="page-link">'.$i.'</span>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array(
              'page-item',
            ),
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => $i - $pager_current,
              'parameters' => $parameters,
            )),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array(
            'page-item',
            'page-ellipsis',
          ),
          'data' => '<span class="page-link">…</span>',
        );
      }
    }

    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array(
          'page-item',
        ),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array(
          'page-item',
        ),
        'data' => $li_last,
      );
    }
    return '<h2 class="sr-only">' . t('Pages') . '</h2><div class="item-pager">' . theme('item_list', array(
        'items' => $items,
        'attributes' => array(
          'class' => array(
            'pagination',
          ),
        ),
      )).'</div>';
  }
}
