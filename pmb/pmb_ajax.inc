<?php 
/*
 * Fonctions Ajax 
 */

function pmb_ajax_get_field_callback() {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  // Enable the submit/validate handlers to determine whether AHAH-submittted.
  $form_state['ahah_submission'] = TRUE;
  $form['#programmed'] = $form['#redirect'] = FALSE;
  drupal_process_form($form_id, $form, $form_state);
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  return $form;
}


function pmb_ajax_get_field(){
	$form = pmb_ajax_get_field_callback();
	$fields = $form['fields'];
	$header = $row = array();
	foreach(element_children($fields) as $field){
		$ligne = array();
		foreach(element_children($fields[$field]) as $elem){
			$ligne[] = drupal_render( $form['fields'][$field][$elem]);
		}
		$row[] = $ligne;
	}
	$output.= theme('table',$header,$row);
	drupal_json(array('status' => TRUE, 'data' => $output));
}

function pmb_get_page_shelf_block($shelf_id, $page=1){
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);

	$shelves = $pmb_data->get_shelves();
    $shelf = array();
	foreach($shelves as $ashelf) {
		if ($ashelf->id == $shelf_id) {
			$shelf = $ashelf;
			break;
		}
	}

	if(!isset($shelf)) {
		return t('Shelf not found!');
	}			
		
	$notice_ids = $pmb_data->get_shelf_notice_ids($shelf_id);
    if (!$notice_ids)
    	$notice_ids = array();
	$notices_pages = array_chunk($notice_ids, 3);
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	
	if (isset($notices) && count($notices)) {
		foreach($notices as $anotice) {
			$rows[] =  array(theme('pmb_notice_display', $anotice, 'small_line', array()));
		}
		
		$template.= theme('table', $header, $rows);	
		$link_maker_function = create_function('$page_number', 'return "'.addslashes("pmb/ajax/block/shelf/".$shelf_id."/").'".$page_number;');
		
		
		$callback = "";
		$template.= theme('pmb_block_pager', $page, ceil(count($notice_ids) / 3), array(), "block_shelf_".$shelf_id, $link_maker_function);
	}
	else {
		$template.= t('This shelf has no notices');
	}
	print $template;
}