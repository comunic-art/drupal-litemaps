<?php

/**
 * @file
 * Define LiteMaps Views style plugin parameters.
 */

/**
 * Implements hook_views_plugins().
 */
function litemaps_views_plugins() {
  return array(
    'style' => array(
      'litemaps' => array(
        'title' => t('LiteMaps'),
        'theme' => 'views_view_litemaps',
        'help' => t('LiteMaps Views style using jQuery LiteMaps plugin.'),
        'handler' => 'litemaps_views_plugin_style',
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
