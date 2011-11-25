<?php
/*
 * Implementation of views_plugin_style
 */
class litemaps_views_plugin_style extends views_plugin_style {
  /**
   * Provide a form for setting options.
   *
   * @param array $form
   * @param array $form_state
   */  
  function options_form(&$form, &$form_state) {
    // @todo Implement descriptions and validation
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $this->options['width'],
    );
    
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $this->options['height'],
    );
    
    $form['zoom'] = array(
      '#type' => 'textfield',
      '#title' => t('Zoom'),
      '#default_value' => $this->options['zoom'],
    );
    
    $form['staticmap'] = array(
      '#type' => 'checkbox',
      '#title' => t('Static map'),
      '#default_value' => $this->options['staticmap'],
    );
  }
  
  
  function query() {
    $join = new views_join();
    $join->construct('litemaps_points', 'node', 'nid', 'eid');
    $alias_table = $this->view->query->add_relationship('litemaps_points', $join, 'litemaps_points');
    
    $this->view->query->add_where('litemaps', "$alias_table.entity = 'node'");
    $this->view->query->add_where('litemaps', "$alias_table.latitude IS NOT NULL");
    $this->view->query->add_where('litemaps', "$alias_table.longitude IS NOT NULL");
    
    $this->view->litemaps->alias_latitude = $this->view->query->add_field('litemaps_points', 'latitude');
    $this->view->litemaps->alias_longitude = $this->view->query->add_field('litemaps_points', 'longitude');
  }
}