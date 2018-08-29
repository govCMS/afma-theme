<?php

/**
 * @file
 * Implementation for the two column bricked layout
 */

// Plugin definition
$plugin = array(
  'title' => t('AFMA homepage'),
  'category' => t('Custom'),
  'icon' => 'afma-homepage-2.5-small.png',
  'theme' => 'panels_homepage',
  'regions' => array(
    'row-1-col-1' => t('Row 1 Col 1 (Menu bean block left)'),
    'row-1-col-2' => t('Row 1 Col 2 (Menu bean block right)'),
    'row-2-col-1' => t('Row 2 Col 1 (Second Menu bean block left)'),
    'row-2-col-2' => t('Row 2 Col 2 (Second Menu bean block right)'),
    'row-3' => t('Row 3 (Second Menu bean block with full width bg)'),
    'row-4-col-1' => t('Row 4 Col 1 (2/3 width views)'),
    'row-4-col-2' => t('Row 4 Col 2 (1/3 width sidebar)'),
    'row-5' => t('Row 5 (optional video)'),
  ),
);
