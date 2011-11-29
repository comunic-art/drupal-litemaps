<?php

/**
 * @file
 * Class of Views style plugin.
 */

/*
 * Implementation of views_plugin_style
 */
class litemaps_views_plugin_style extends views_plugin_style {
  
  function option_definition() {
    $options = parent::option_definition();
    $options['map'] = array(
      'height' => array('default' => variable_get('litemaps_default_height', LITEMAPS_DEFAULT_HEIGHT)),
      'width' => array('default' => variable_get('litemaps_default_width', LITEMAPS_DEFAULT_WIDTH)),
      'center' => array('default' => variable_get('litemaps_default_center', LITEMAPS_DEFAULT_CENTER)),
      'zoom' => array('default' => variable_get('litemaps_default_zoom', LITEMAPS_DEFAULT_ZOOM)),
      'type' => array('default' => variable_get('litemaps_default_type', LITEMAPS_DEFAULT_TYPE)),
      'staticmap' => array('default' => variable_get('litemaps_default_staticmap', LITEMAPS_DEFAULT_STATICMAP)),
    );
    return $options;
  }
  
  /**
   * Provide a form for setting options.
   *
   * @param array $form
   * @param array $form_state
   */
  function options_form(&$form, &$form_state) {
    $fields = field_info_fields();
    $options = array();
    
    $form['fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Fields'),
      '#description' => t('The fields to use as points in the map.'),
      '#tree' => TRUE,
    );
    
    foreach ($fields as $field) {
      if ($field['type'] == 'litemaps_point') {
        foreach (field_views_field_default_views_data($field) as $data) {
          if (isset($data[$field['field_name']])) {
            $form['fields'][$field['field_name']] = array(
              '#type' => 'checkbox',
              '#title' => $data[$field['field_name']]['title'],
              '#description' => $data[$field['field_name']]['help'],
              '#default_value' => $this->options['fields'][$field['field_name']],
            );
          }
        }
      }
    }
    
    $form['map'] = array(
      '#type' => 'fieldset',
      '#title' => t('Map'),
      '#description' => t('Settings of the map to display.'),
      '#tree' => TRUE,
    );
    
    $form['map']['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Map height'),
      '#description' => _litemaps_settings_description('height'),
      '#default_value' => $this->options['map']['height'],
    );
    
    $form['map']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Map width'),
      '#description' => _litemaps_settings_description('width'),
      '#default_value' => $this->options['map']['width'],
    );
    
    $form['map']['center'] = array(
      '#type' => 'textfield',
      '#title' => t('Map center'),
      '#description' => _litemaps_settings_description('center'),
      '#default_value' => $this->options['map']['center'],
    );
    
    $form['map']['zoom'] = array(
      '#type' => 'select',
      '#title' => t('Map zoom'),
      '#description' => _litemaps_settings_description('zoom'),
      '#options' => _litemaps_settings_options_zoom(),
      '#default_value' => $this->options['map']['zoom'],
    );
    
    $form['map']['type'] = array(
      '#type' => 'select',
      '#title' => t('Map type'),
      '#description' => _litemaps_settings_description('type'),
      '#options' => _litemaps_settings_options_type(),
      '#default_value' => $this->options['map']['type'],
    );
    
    $form['map']['staticmap'] = array(
      '#type' => 'checkbox',
      '#title' => t('Static map'),
      '#description' => _litemaps_settings_description('staticmap'),
      '#default_value' => $this->options['map']['staticmap'],
    );
  }

  function query() {
    parent::query();
    
    $fields = array_filter($this->options['fields']);
    foreach ($fields as $field => $status) {
      $field_info = field_info_field($field);
      foreach (field_views_field_default_views_data($field_info) as $data) {
        if (isset($data[$field]['field'])) {
          $table = $data[$field]['field']['table'];
          $latitude = $field . "_latitude";
          $longitude = $field . "_longitude";
          
          $table = $this->view->query->ensure_table($table);
          $latitude_alias = $this->view->query->add_field($table, $latitude);
          $longitude_alias = $this->view->query->add_field($table, $longitude);
          
          $this->view->litemaps->aliases[] = array(
            'latitude' => $latitude_alias,
            'longitude' => $longitude_alias,
          );
        }
      }
    }
    
    if (isset($this->row_plugin)) {
      $this->row_plugin->query();
    }
  }
}
