<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_admin_pages.inc,v 1.6 2011-10-21 20:32:24 gueluneau Exp $

function pmb_admin_cache_form() {
  $form = array();

  $form['pmb_linking'] = array(
    '#type' => 'fieldset',
    '#title' => t('PMB Linking'),
   );
  $form['pmb_linking']['pmb_link_type'] = array(
    '#type' => 'select',
    '#title' => t('PMB link type'),
    '#default_value' => variable_get('pmb_link_type', 'json-rpc'),
    '#description' => t("The type of the link to PMB"),
  	'#options' => array(
  		'json-rpc' => t('JSON-RPC'),
  	),
    '#required' => TRUE,
  );  
  $form['pmb_linking']['pmb_link_serverurl'] = array(
    '#type' => 'textfield',
    '#title' => t('PMB service URL'),
    '#default_value' => variable_get('pmb_link_serverurl', ''),
    '#size' => 50,
    '#maxlength' => 256,
    '#description' => t("The url of the PMB service"),
    '#required' => TRUE,
  );  
  $form['pmb_linking']['pmb_link_serveruser'] = array(
    '#type' => 'textfield',
    '#title' => t('PMB service login'),
    '#default_value' => variable_get('pmb_link_serveruser', ''),
    '#size' => 50,
    '#maxlength' => 256,
    '#description' => t("The login of the PMB service"),
    '#required' => FALSE,
  );  
  $form['pmb_linking']['pmb_link_serverpassword'] = array(
    '#type' => 'textfield',
    '#title' => t('PMB service password'),
    '#default_value' => variable_get('pmb_link_serverpassword', ''),
    '#size' => 50,
    '#maxlength' => 256,
    '#description' => t("The password of the PMB service"),
    '#required' => FALSE,
  );  
  
  $form['cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache'),
  	'#collapsible' => TRUE,
  	'#collapsed' => TRUE,   
   );
  $form['cache']['pmb_user_cache_profile'] = array(
    '#type' => 'radios',
    '#title' => t('Cache profile'),
    '#default_value' => variable_get('pmb_user_cache_profile', 'cache_anonymous_all'),
    '#description' => t("The profile of the cache. Determine how to cache the notices. This will have an inpact on performances."),
    '#required' => TRUE,
  	'#options' => array(
		'cache_anonymous_all' => t('Anonymous and readers share the same cache'),
  		'cache_anonymous_empr_all' => t('Anonymous readers have their own cache. All readers share the same cache.'),  		
  		'cache_anonymous_empr_separate' => t("Anonymous readers have their own cache. Each reader has its own cache"),  		
  	),
  );
  $form['cache']['pmb_notice_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the notices in the cache'),
    '#default_value' => variable_get('pmb_notice_cache_duration', 3600),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the notices in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_author_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the authors in the cache'),
    '#default_value' => variable_get('pmb_author_cache_duration', 3600),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the authors in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_publisher_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the publishers in the cache'),
    '#default_value' => variable_get('pmb_publisher_cache_duration', 3600),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the publishers in the cache, in seconds"),
    '#required' => TRUE,
  );  
  $form['cache']['pmb_collection_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the collections in the cache'),
    '#default_value' => variable_get('pmb_collection_cache_duration', 3600),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the collections in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_subcollection_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the subcollection in the cache'),
    '#default_value' => variable_get('pmb_subcollection_cache_duration', 3600),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the subcollection in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_location_and_sections_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the locations and sections in the cache'),
    '#default_value' => variable_get('pmb_location_and_sections_cache_duration', 60*24*7),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the locations and sections in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_search_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the searches in the cache'),
    '#default_value' => variable_get('pmb_search_cache_duration', 60*15),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the searches in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_reader_session_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the reader sessions in the cache'),
    '#default_value' => variable_get('pmb_reader_session_duration', 60*20 - 5),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the reader sessions in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_reader_loans_cache_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the loans of readers in the cache'),
    '#default_value' => variable_get('pmb_reader_loans_cache_duration', 60*20 - 5),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the loans of readers in the cache, in seconds"),
    '#required' => TRUE,
  );
  $form['cache']['pmb_reader_reservations_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration of the reservations of readers in the cache'),
    '#default_value' => variable_get('pmb_reader_reservations_duration', 5),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t("The duration of the reservations readers in the cache, in seconds"),
    '#required' => TRUE,
  );

  
  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display'),
  	'#collapsible' => TRUE,
  	'#collapsed' => TRUE,  
   );  
  $form['display']['pmb_noticeperpage_author'] = array(
    '#type' => 'textfield',
    '#title' => t('Records per page / Authors'),
    '#default_value' => variable_get('pmb_noticeperpage_author', 3),
    '#size' => 5,
    '#maxlength' => 10,
    '#description' => t("Number of record per page in the author pages"),
    '#required' => TRUE,
  );
  $form['display']['pmb_noticeperpage_publisher'] = array(
    '#type' => 'textfield',
    '#title' => t('Records per page / Publishers'),
    '#default_value' => variable_get('pmb_noticeperpage_publisher', 3),
    '#size' => 5,
    '#maxlength' => 10,
    '#description' => t("Number of records per page in the publisher pages"),
    '#required' => TRUE,
  );
  $form['display']['pmb_noticeperpage_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Records per page / Collections'),
    '#default_value' => variable_get('pmb_noticeperpage_collection', 3),
    '#size' => 5,
    '#maxlength' => 10,
    '#description' => t("Number of records per page in the collection pages"),
    '#required' => TRUE,
  );
  $form['display']['pmb_noticeperpage_subcollection'] = array(
    '#type' => 'textfield',
    '#title' => t('Records per page / Sub Collections'),
    '#default_value' => variable_get('pmb_noticeperpage_subcollection', 3),
    '#size' => 5,
    '#maxlength' => 10,
    '#description' => t("Number of records per page in the sub collection pages"),
    '#required' => TRUE,
  );
  $form['display']['pmb_noticeperpage_search'] = array(
    '#type' => 'textfield',
    '#title' => t('Records per page / Search'),
    '#default_value' => variable_get('pmb_noticeperpage_search', 10),
    '#size' => 5,
    '#maxlength' => 10,
    '#description' => t("Number of records per page in the search results"),
    '#required' => TRUE,
  );
  
  return system_settings_form($form);
}