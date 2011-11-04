<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_search_forms.inc,v 1.8 2011-10-22 08:08:52 arenou Exp $

function pmb_get_search_fields() {
	return array(
		 'all_fields' => t('All fields'),
	     'title' => t('Titles'),
	     'author' => t('Authors'),
	     'publisher' => t('Publishers'),
	     'collection' => t('Collections'),
	     'subcollection' => t('Sub collections'),
	     'category' => t('Categories'),
	     'indexint' => t('Decimal indexing'),
	);
}

function pmb_search_form_form($form_state) {
	$search_form = array();
    $search_form['search_query'] = array(
      '#type' => 'textfield',
      '#title' => t('Search terms'),
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('The search terms'),
    );
   
    $search_fields = pmb_get_search_fields();
    $search_form['search_fields'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Fields'),
      '#description' => t('Fields to search'),
      '#options' => $search_fields,
    );
    
    $search_form['submit'] = array('#type' => 'submit', '#value' => t('Rechercher'));

    return $search_form;
}

function pmb_search_form_form_submit($form, &$form_state) {
	$search_term = $form_state['values']['search_query'];
	$search_fields = array();
	foreach($form_state['values']['search_fields'] as $asearch_field) {
		if ($asearch_field) {
			$search_fields[] = $asearch_field;
		}
	}
	$search_fields = implode(',', $search_fields);
	$form_state['redirect'] = 'pmb/search/local/'.$search_fields.'/'.$search_term;
}

function pmb_search_form_form_validate($form, &$form_values) {
	$form_values['values']['search_query'] = preg_replace('/\//', '', $form_values['values']['search_query']);
	if (!$form_values['values']['search_query']) {
		form_set_error('search_query', t('Please enter a search query.'));
	}
	$somewhere_to_search = FALSE;
	foreach($form_values['values']['search_fields'] as $asearch_field) {
		if ($asearch_field) {
			$somewhere_to_search = TRUE;
			break;
		}
	}
	if (!$somewhere_to_search) {
		form_set_error('search_fields', t('Please enter at least one field to search in.'));
	}
}

function pmb_search_form_block_form($form_state) {
	$search_form = array();
    $search_form['search_query'] = array(
      '#type' => 'textfield',
      '#title' => t('Quick search terms'),
      '#size' => 15,
      '#maxlength' => 255,
      '#description' => t('Please enter one or more search terms'),
    );

    $search_form['submit'] = array('#type' => 'submit', '#value' => t('Search'));

    return $search_form;
}

function pmb_search_form_block_form_submit($form, &$form_state) {
	$search_term = $form_state['values']['search_query'];
	$search_fields = array('all_fields');
	$search_fields = implode(',', $search_fields);
	$form_state['redirect'] = 'pmb/search/local/'.$search_fields.'/'.$search_term;
}

function pmb_search_form_block_form_validate($form, &$form_values) {
	$form_values['values']['search_query'] = preg_replace('/\//', '', $form_values['values']['search_query']);
	if (!$form_values['values']['search_query']) {
		form_set_error('search_query', t('Please enter a search query.'));
	}
}

function pmb_get_external_search_fields() {
	return array(
		 'all_fields' => t('All fields'),
	     'title' => t('Titles'),
	     'author' => t('Authors'),
	     'publisher' => t('Publishers'),
	     'collection' => t('Collections'),
	     'subcollection' => t('Sub collections'),
	     'isbn_bar_code' => t('ISBN/Bar Code'),
	);
}

function theme_pmb_external_search_form_form($form) {
  foreach (element_children($form['sources']) as $key) {
	drupal_render($form['sources'][$key]);    
    if (is_array($form['sources'][$key])) {
      $row = array();
      if (!is_numeric($key)) {
        $row[] = array('data' => t($form['sources'][$key]['#value']), 'class' => 'module', 'colspan' => 2);
      }
      else {
		$row[] = array('data' => drupal_render($form['checkboxes'][$key]), 'class' => 'permission');
      	$row[] = array('data' => $form['sources'][$key]['#comment'], 'class' => 'permission');
        }
      }
      $rows[] = $row;
    }

  $header = array(t('Sources'), t('Comments'));
  $output = drupal_render($form['search_query']);
  $output .= drupal_render($form['search_fields']);
  $output .= theme('table', $header, $rows, array('id' => 'sources'));
  $output .= drupal_render($form);
  return $output;
}

function pmb_external_search_form_form($form_state, $sources) {
	$search_form = array();
    $search_form['search_query'] = array(
      '#type' => 'textfield',
      '#title' => t('Search terms'),
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('The search terms'),
    );

    $search_fields = pmb_get_external_search_fields();
    $search_form['search_fields'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Fields'),
      '#description' => t('Fields to search'),
      '#options' => $search_fields,
    );
    
	$search_form['checkboxes'] = array(
		'#type' => 'checkboxes',
		'#options' => array(),
	);
	
	$search_form['sources'] = array();
	if ($sources) {
		foreach($sources as $asource_category_index => $asource_category) {
			$search_form['sources']['c'.$asource_category_index] = array(
				'#value' => $asource_category->category_caption
			);
			foreach($asource_category->sources as $asource) {
				$search_form['sources'][$asource->source_id] = array(
					'#value' => $asource->source_caption,
					'#comment' => $asource->source_comment,
				);
				$search_form['checkboxes']['#options'][$asource->source_id] = $asource->source_caption;
			}
		}
	}

    $search_form['submit'] = array('#type' => 'submit', '#value' => t('Rechercher'));
    return $search_form;
}

function pmb_external_search_form_form_validate($form, &$form_values) {
	$form_values['values']['search_query'] = preg_replace('/\//', '', $form_values['values']['search_query']);
	if (!$form_values['values']['search_query']) {
		form_set_error('search_query', t('Please enter a search query.'));
	}
	$somewhere_to_search = FALSE;
	foreach($form_values['values']['checkboxes'] as $asource) {
		if ($asource) {
			$somewhere_to_search = TRUE;
			break;
		}
	}
	if (!$somewhere_to_search) {
		form_set_error('search_fields', t('Please enter at least one source to search in.'));
	}
	
	$somewhere_to_search = FALSE;
	foreach($form_values['values']['search_fields'] as $asearch_field) {
		if ($asearch_field) {
			$somewhere_to_search = TRUE;
			break;
		}
	}
	if (!$somewhere_to_search) {
		form_set_error('search_fields', t('Please enter at least one field to search in.'));
	}
}

function pmb_external_search_form_form_submit($form, &$form_state) {
	//drupal encode automatiquement ses urls...
	
	//$search_term = rawurlencode($form_state['values']['search_query']);
	$search_term = $form_state['values']['search_query'];
	$search_fields = array();
	foreach($form_state['values']['search_fields'] as $asearch_field) {
		if ($asearch_field) {
			$search_fields[] = $asearch_field;
		}
	}
	foreach($form_state['values']['checkboxes'] as $asource_id) {
		if ($asource_id) {
			$search_sources[] = $asource_id;
		}
	}
//	$search_fields = rawurlencode(implode(',', $search_fields));
	$search_fields = implode(',', $search_fields);
//	$search_sources = rawurlencode(implode(',', $search_sources));
	$search_sources = implode(',', $search_sources);
	$form_state['redirect'] = 'pmb/search/external/'.$search_fields.'/'.$search_sources.'/'.$search_term;
}

function pmb_get_advanced_search_fields() {
	$pmb_data = new pmb_data();
	$fields = array();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);

	$results = $pmb_data->getAdvancedSearchFields(true);
	$fields = array();
	foreach($results as $result){
		$fields[$result->id]= $result->label;
	}
	return $fields;
}

function pmb_get_advanced_current_fields_form($form,$current_fields){
	$pmb_data = new pmb_data();
	$fields = array();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);

	$fields = $pmb_data->getAdvancedSearchFields(false);
	$header = $row = array();
	$element = array();
	foreach($fields as $field){	
		if(in_array($field->id,$current_fields)){
			//Label
			$opts = array();
			$form['fields']['field_'.$field->id]['label'] = array(
				'#type' => "item",
				'#value' => $field->label
			);
			//Opérateurs			
			foreach($field->operators as $operator){
				$opts[$operator->id] = $operator->label;
			}
			$form['fields']['field_'.$field->id]['op_'.$field->id] =array(
				'#type' => "select",
				'#title' => t('Operators'),
				'#options' => $opts
			);
			//Valeur
			$values = array();
			foreach($field->values as $val){
				$values[$val->value_id] = $val->value_caption;
			}
			switch($field->type){
				case "authoritie" :
					$form['fields']['field_'.$field->id]['value_'.$field->id] =array(
						'#type' => "textfield",
						'#title' => t('Value')
					);					
					break;
				case "list" :
				case "query_list" :
				case "marc_list" :
					$form['fields']['field_'.$field->id]['value_'.$field->id] =array(
						'#type' => "select",
						'#title' => t('Value'),
						'#options' => $values
					);
					break;
				case "date" :
						$form['fields']['field_'.$field->id]['value_'.$field->id] =array(
							'#type' => "date",
							'#title' => t('Value')
						);						
					break;	
				case "small_text" :
					if(count($values)){
						$form['fields']['field_'.$field->id]['value_'.$field->id] =array(
							'#type' => "select",
							'#title' => t('Value'),
							'#options' => $values
						);						
					}else{
						$form['fields']['field_'.$field->id]['value_'.$field->id] =array(
							'#type' => "textfield",
							'#title' => t('Value')
						);					
					}
					break;										
				case "text" :
				default :
					$form['fields']['field_'.$field->id]['value_'.$field->id] =array(
						'#type' => "textfield",
						'#title' => t('Value')
					);						
					break;
			}
//			//la suppression d'un critère
//			$form['fields']['field_'.$field->id]['del_'.$field->id] = array(
//				'#type' => 'checkbox',
//				'#title' => t("Delete crit"),
//				'#value' => t("Delete Crit"),
//				'#ahah' => array(
//					'event' => "click",
//		    		'method' => "replace",
//					'wrapper'=>'fields_content',
//		    		'path' => 'pmb/ajax/get_field'				
//				)
//			);
		}
	}
}

function pmb_advanced_search_form_form($form_state) {
	$form = array();
	//on doit déjà récupérer la liste des critères...
	$fields = pmb_get_advanced_search_fields();
    $form['#action'] = url('pmb/advanced_search/result');
	$form['advancedSearchCrit'] = array(
		'#type' => 'select',
		'#title' => t('Criterias'),
		'#options' => $fields,
		'#ahah' => array(
    		'event' => "change",
    		'method' => "replace",
			'wrapper'=>'fields_content',
    		'path' => 'pmb/ajax/get_field'	
    	)
	);
	$form['current_fields'] = array(
		'#type' => "hidden",
		'#value' => $form_state['values']['current_fields']
	);
	$form['fields'] = array(
		'#type'=>'item',
		'#prefix'=>'<div id="fields_content">',
		'#suffix'=>'</div>'
	);
	$current_fields = unserialize($form_state['values']['current_fields']);
	if(is_array($current_fields)){
		pmb_get_advanced_current_fields_form(&$form,$current_fields);
	}
    $form['submit'] = array('#type' => 'submit', '#value' => t('Rechercher'));
    return $form;
}

function pmb_advanced_search_form_form_submit($form ,&$form_state) {
	$current_fields = unserialize($form_state['values']['current_fields']);
	for($i=0 ; $i<count($current_fields) ; $i++){
		if($form_state['values']['del_'.$current_fields[$i]] == "1"){
			array_splice($current_fields,$i,1);
			$i--;
		}
	}
	$current_fields[] = $form_state['values']['advancedSearchCrit'];
	$form_state['values']['current_fields'] = serialize($current_fields);
	return "plop";	
}
