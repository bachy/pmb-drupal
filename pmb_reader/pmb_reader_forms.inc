<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_forms.inc,v 1.7 2011-10-21 20:32:23 gueluneau Exp $

function pmb_reader_suggestion_edit_form($form_state, $suggestion, $categ_and_sources) {
  $can_edit = ($suggestion->sugg_state == 1) || !$suggestion->sugg_id;
  $can_delete = $suggestion->sugg_id;
	
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_title) ? $suggestion->sugg_title : '',
    '#description' => t('The title of the document'),
  	'#required' => true,
  	'#disabled' => !$can_edit,
  );
  $form['author'] = array(
    '#type' => 'textfield',
    '#title' => t('Author'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_author) ? $suggestion->sugg_author : '',
  	'#description' => t('The author of the document'),
  	'#required' => true,  
  	'#disabled' => !$can_edit,
  );  
  $form['publisher'] = array(
    '#type' => 'textfield',
    '#title' => t('Publisher'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_editor) ? $suggestion->sugg_editor : '',
  	'#description' => t('The publisher of the document'),
  	'#required' => true,  
  	'#disabled' => !$can_edit,
  );  
  $form['barcode'] = array(
    '#type' => 'textfield',
    '#title' => t('ISBN / Bar code'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_barcode) ? $suggestion->sugg_barcode : '',
    '#description' => t('The bar code of the document'),
  	'#disabled' => !$can_edit,
  );
  $form['price'] = array(
    '#type' => 'textfield',
    '#title' => t('Price'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_price) ? $suggestion->sugg_price : '',
    '#description' => t('The price of the document'),
  	'#disabled' => !$can_edit,
  );  
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_url) ? $suggestion->sugg_url : '',
    '#description' => t('The website of the document'),
  	'#disabled' => !$can_edit,
  );  
  $form['date_pub'] = array(
    '#type' => 'textfield',
    '#title' => t('Publication date'),
    '#size' => 50,
    '#maxlength' => 255,
  	'#default_value' => isset($suggestion->sugg_date) ? $suggestion->sugg_date : '',
    '#description' => t('The date of the document'),
    '#disabled' => !$can_edit,
  );  
  $form['comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#default_value' => isset($suggestion->sugg_comment) ? $suggestion->sugg_comment : '',
    '#description' => t('The comment of the suggestion'),
    '#disabled' => !$can_edit,
  );
  $form['source'] = array(
    '#type' => 'select',
    '#title' => t('Source'),
    '#default_value' => isset($suggestion->sugg_source) ? $suggestion->sugg_source : 0,
    '#description' => t('The source of the suggestion'),
    '#disabled' => !$can_edit,
  );
  $form['source']['#options'] = array();
  $form['source']['#options'][0] = t('No source');
  foreach($categ_and_sources->sources as $asource) {
  	$form['source']['#options'][$asource->source_id] = $asource->source_caption;
  }
  
  $form['category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => isset($suggestion->sugg_category) ? $suggestion->sugg_category : 0,
    '#description' => t('The category of the suggestion'),
    '#disabled' => !$can_edit,
  );
  $form['category']['#options'] = array();
  $form['category']['#options'][0] = t('No Category');
  foreach($categ_and_sources->categories as $acateg) {
  	$form['category']['#options'][$acateg->category_id] = $acateg->category_caption;
  }

  $form['suggestion_id'] = array('#type' => 'hidden', '#value' => isset($suggestion->sugg_id) ? $suggestion->sugg_id : 0);
  
  $form['submit'] = array(
  	'#type' => 'submit', 
  	'#value' => t('Save'),
    '#disabled' => !$can_edit,  
  );
  if ($can_delete) {
	  $form['delete'] = array(
	  	'#type' => 'submit', 
	  	'#value' => t('Delete'),
	    '#disabled' => !$can_edit,
	  );
  }
  return $form;
}

function pmb_reader_suggestion_edit_form_validate($form, &$form_state) {
  if ($form_state['values']['title'] == '') {
    form_set_error('title', t('You must enter a title.'));
  }
  if ($form_state['values']['author'] == '') {
    form_set_error('title', t('You must enter an author.'));
  }
  if ($form_state['values']['publisher'] == '') {
    form_set_error('title', t('You must enter a publisher.'));
  }
}

function pmb_reader_suggestion_edit_form_submit($form, &$form_state) {
	//highlight_string(print_r($form_state, true));
	
	$suggestion = array();
	$suggestion['sugg_id'] = $form_state['values']['suggestion_id'];
	$suggestion['sugg_title'] = $form_state['values']['title'];
	$suggestion['sugg_author'] = $form_state['values']['author'];
	$suggestion['sugg_editor'] = $form_state['values']['publisher'];
	$suggestion['sugg_barcode'] = $form_state['values']['barcode'];
	$suggestion['sugg_price'] = $form_state['values']['price'];
	$suggestion['sugg_comment'] = $form_state['values']['comment'];
	$suggestion['sugg_url'] = $form_state['values']['url'];
	$suggestion['sugg_date'] = $form_state['values']['date_pub'];
	$suggestion['sugg_source'] = $form_state['values']['source'];
	$suggestion['sugg_category'] = $form_state['values']['category'];
		
	if ($form_state['clicked_button']['#id'] == 'edit-delete') {
		$result = FALSE;
		if ($suggestion['sugg_id']) {
	    	$pmb_data = new pmb_data();
			$pmb_data->set_user($GLOBALS["user"]);
			$result = $pmb_data->reader_delete_suggestion($suggestion['sugg_id']);
			if ($result) {
				drupal_set_message(t('Your suggestion has been deleted.'));
			}
			else {
				drupal_set_message(t('Your suggestion has not been deleted.', 'error'));
			}			
		}
		drupal_goto('pmb_reader/'.$GLOBALS["user"]->uid.'/suggestions');
	}
	else {
		if (!$suggestion['sugg_id'])  {
	    	$pmb_data = new pmb_data();
			$pmb_data->set_user($GLOBALS["user"]);
			$result = $pmb_data->reader_add_suggestion($suggestion);
		}
		else {
	    	$pmb_data = new pmb_data();
			$pmb_data->set_user($GLOBALS["user"]);
			$result = $pmb_data->reader_edit_suggestion($suggestion);
		}
		if ($result) {
			drupal_set_message(t('Your suggestion has been saved.'));
		}
		else {
			drupal_set_message(t('Your suggestion has not been saved.', 'error'));
		}
		drupal_goto('pmb_reader/'.$GLOBALS["user"]->uid.'/suggestions');
	}
}


function pmb_reader_cart_form($form_state, $notices) {
	$form = array();
	$options = array();
	$form['notices']['notice_ids'] = array();
	foreach($notices as $anotice_id => $notice_content) {
		$form['notices']['notice_ids'][$anotice_id] = '';
		$options[$anotice_id] = '';
	}
	
	$form['checked_notices'] = array(
		'#type' => 'checkboxes',
		'#options' => $options,
		'#default_value' => array(),
	);
 
	$form['delete_selected'] = array(
		'#type' => 'submit',
		'#value' => t('Remove selected elements from cart'),
		'#name' => 'delete_selected',
	);
	
	$form['empty_cart'] = array(
		'#type' => 'submit',
		'#value' => t('Empty cart'),
		'#name' => 'empty_cart',
	);

 
	return $form;
}

function pmb_reader_cart_form_validate($form, &$form_state) {
	if ($form_state["clicked_button"]['#name'] == 'delete_selected') {
		if (!array_sum($form_state['values']['checked_notices'])) {
			form_set_error('title', t('You must select records before removing.'));			
		}
		return;
	}
	else if ($form_state["clicked_button"]['#name'] == 'empty_cart') {
		return;
	}
	form_set_error('title', t('Unknown operation'));
}

function pmb_reader_cart_form_submit($form, &$form_state) {
	require_once(drupal_get_path('module', 'pmb_reader').'/pmb_reader_cart.inc');
	if ($form_state["clicked_button"]['#name'] == 'delete_selected') {

		$notice_ids = array();
		foreach ($form_state['values']['checked_notices'] as $anotice_id => $value) {
			if ($value) {
				$notice_ids[] = $anotice_id;
			}
		}
		pmb_reader_delete_notices_from_cart($GLOBALS["user"], $notice_ids);
		
		return;
	}
	else if ($form_state["clicked_button"]['#name'] == 'empty_cart') {
		pmb_reader_empty_cart($GLOBALS["user"]);		
		return;
	}
}


function pmb_reader_add_notice_to_cart_form($form, $notice_id) {
	$form = array();
	
	$form['add_notice_to_cart'] = array(
		'#type' => 'submit',
		'#value' => t('Add notice to cart'),
		'#name' => 'add_notice_to_cart',
	);

	return $form;
}

function pmb_reader_add_notice_to_cart_form_validate($form, &$form_state) {
	if ($form_state["clicked_button"]['#name'] == 'add_notice_to_cart') {
		if ($form['#parameters'][2]+0 == 0)
			form_set_error('title', t('Blank notice id.'));
		return;
	}
	form_set_error('title', t('Could not understand query.'));
}

function pmb_reader_add_notice_to_cart_form_submit($form, &$form_state) {
	require_once(drupal_get_path('module', 'pmb_reader').'/pmb_reader_cart.inc');
	$notice_ids = array($form['#parameters'][2]);
	pmb_reader_add_notices_to_cart($GLOBALS["user"], $notice_ids);
	drupal_goto('pmb_reader/'.$GLOBALS["user"]->uid.'/cart');
}


function pmb_reader_add_cart_to_reading_list_form($form, $list_id) {
	$form = array();
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($GLOBALS["user"]);
	if (!(isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)))
		return FALSE;
	$cart_content = $pmb_data->reader_get_cart();
	
	$form['add_cart_to_reading_list'] = array(
		'#type' => 'submit',
		'#value' => t('Add your cart to this reading list'),
		'#name' => 'add_cart_to_reading_list',
		'#disabled' => !($cart_content && count($cart_content)),
	);
	
	$form['#cart_content'] = $cart_content;
	$form['#list_id'] = $list_id;	
	
	return $form;
}

function pmb_reader_add_cart_to_reading_list_form_validate($form, &$form_state) {
	if ($form_state["clicked_button"]['#name'] == 'add_cart_to_reading_list') {
		if ($form['#list_id'] == 0)
			form_set_error('title', t('Blank reading list.'));
		return;
	}
	form_set_error('title', t('Could not understand query.'));
}

function pmb_reader_add_cart_to_reading_list_form_submit($form, &$form_state) {
	require_once(drupal_get_path('module', 'pmb_reader').'/pmb_reader_reading_lists.inc');
	$list_id = $form['#list_id'];
	pmb_reader_add_notices_to_reading_list($GLOBALS["user"], $list_id, $form['#cart_content']);
	drupal_goto('pmb_reader/'.$GLOBALS["user"]->uid.'/reading_lists/'.$list_id);
}


function pmb_reader_reading_list_form($form_state, $list, $notices) {
	$form = array();
	$options = array();
	$form['#notices']['notice_ids'] = array();
	foreach($notices as $anotice_id => $notice_content) {
		$form['#notices']['notice_ids'][$anotice_id] = '';
		$options[$anotice_id] = '';
	}
	$form['#notices']['notices'] = $notices;
	
	$form['#reading_list'] = $list;
	
	$form['checked_notices'] = array(
		'#type' => 'checkboxes',
		'#options' => $options,
		'#default_value' => array(),
	);
 
	$form['delete_selected'] = array(
		'#type' => 'submit',
		'#value' => t('Remove selected elements from list'),
		'#name' => 'delete_selected',
		'#disabled' => !($notices && count($notices)),
	);
	
	$form['empty_list'] = array(
		'#type' => 'submit',
		'#value' => t('Empty list'),
		'#name' => 'empty_list',
		'#disabled' => !($notices && count($notices)),
	);


	if ((isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))) {
	    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
	    $pmb_data = new pmb_data();
		$pmb_data->set_user($GLOBALS["user"]);
		$cart_content = $pmb_data->reader_get_cart();
		$form['add_cart_to_list'] = array(
			'#type' => 'submit',
			'#value' => t('Add the content of your cart to this list'),
			'#name' => 'add_cart_to_list',
			'#disabled' => !($cart_content && count($cart_content)),
		);
	
		$form['#cart_content'] = $cart_content;		
	}
		

	return $form;
}

function pmb_reader_reading_list_form_validate($form, &$form_state) {
	if ($form_state["clicked_button"]['#name'] == 'delete_selected') {
		if (!array_sum($form_state['values']['checked_notices'])) {
			form_set_error('title', t('You must select notices to remove.'));			
		}
		return;
	}
	else if ($form_state["clicked_button"]['#name'] == 'empty_list') {
		return;
	}
	else if ($form_state["clicked_button"]['#name'] == 'add_cart_to_list') {
		return;
	}
	form_set_error('title', t('Unknown operation'));
}

function pmb_reader_reading_list_form_submit($form, &$form_state) {
	require_once(drupal_get_path('module', 'pmb_reader').'/pmb_reader_reading_lists.inc');
	if ($form_state["clicked_button"]['#name'] == 'delete_selected') {

		$notice_ids = array();
		foreach ($form_state['values']['checked_notices'] as $anotice_id => $value) {
			if ($value) {
				$notice_ids[] = $anotice_id;
			}
		}
		pmb_reader_remove_notices_from_reading_list($GLOBALS["user"], $form['#reading_list']->reading_list_id, $notice_ids);
		
		return;
	}
	else if ($form_state["clicked_button"]['#name'] == 'add_cart_to_list') {
		$list_id = $form['#reading_list']->reading_list_id;
		pmb_reader_add_notices_to_reading_list($GLOBALS["user"], $list_id, $form['#cart_content']);
	}	
	else if ($form_state["clicked_button"]['#name'] == 'empty_list') {
		pmb_reader_empty_reading_list($GLOBALS["user"], $form['#reading_list']->reading_list_id);
		return;
	}
}
