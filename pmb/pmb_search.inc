<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_search.inc,v 1.6 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

function pmb_search_catalog() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);

    return theme('pmb_search_form');
}

function pmb_search_catalog_search($search_fields, $search_terms, $page = 1) {
	require_once(drupal_get_path('module', 'pmb').'/forms/pmb_search_forms.inc');
	
	$search_fields = rawurldecode($search_fields);
	$search_terms = rawurldecode($search_terms);
	$search_fields = explode(',', $search_fields);
	$allowed_search_fields = array_keys(pmb_get_search_fields());
	$search_fields = array_intersect($search_fields, $allowed_search_fields);
	if (!$search_terms || !$allowed_search_fields) {
		drupal_set_title(t('Invalid search!'));
		drupal_set_message(t('Invalid search!'), 'error');
		return '';
	}

	drupal_set_title(t('Search: ').check_plain($search_terms));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Search the catalog'), 'pmb/search/local');
    $breadcrumb[] = l(t('Search results'), 'pmb/search/local/'.implode(',', $search_fields).'/'.$search_terms.'/'.$page);
    drupal_set_breadcrumb($breadcrumb);
	
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$notice_ids = $pmb_data->get_search_notice_ids($search_terms, $search_fields);
	
    if (!$notice_ids)
    	$notice_ids = array();

	$notice_count = variable_get('pmb_noticeperpage_search', 10);
	$notices_pages = array_chunk($notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
    
	return theme('pmb_search_results', $search_terms, $search_fields, $notices, array('page_number' => $page, 'notices_per_pages' => $notice_count, 'section_notice_count' => count($notice_ids)));;	
}

function pmb_search_external_catalog() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Search the external catalog'), 'pmb/search/external');
    drupal_set_breadcrumb($breadcrumb);
	
    $search_sources = $pmb_data->get_external_search_sources();

	return drupal_get_form('pmb_external_search_form_form', $search_sources);
}

function pmb_search_external_catalog_search($search_fields, $search_sources, $search_terms, $page = 1) {
	require_once(drupal_get_path('module', 'pmb').'/forms/pmb_search_forms.inc');
	
	$search_sources = explode(',', $search_sources);
	array_walk($search_sources, create_function('&$a', '$a+=0;'));	//Virons ce qui n'est pas entier
	$search_sources = array_unique($search_sources);
	$search_fields = rawurldecode($search_fields);
	$search_fields = explode(',', $search_fields);
	$search_terms = rawurldecode($search_terms);
	$allowed_search_fields = array_keys(pmb_get_external_search_fields());
	$search_fields = array_intersect($search_fields, $allowed_search_fields);
	if (!$search_terms || !$allowed_search_fields || !$search_sources) {
		drupal_set_title(t('Invalid search!'));
		drupal_set_message(t('Invalid search!'), 'error');
		return '';
	}

	drupal_set_title(t('External search: ').check_plain($search_terms));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Search the external catalog'), 'pmb/search/external');
    $breadcrumb[] = l(t('Search results'), 'pmb/search/external/'.$search_fields.'/'.implode(',',$search_sources).'/'.$search_terms.'/'.$page);
    drupal_set_breadcrumb($breadcrumb);
	
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$notice_ids = $pmb_data->get_external_search_notice_ids($search_terms, $search_fields, $search_sources);
//	//on a plus un tableau de d'ids, mais un tableau d'id de sources contenant un tableau d'ids
//	foreach($notice_ids as $source_id => $notices_ids){
//	    if (!$notices_ids)
//	    	$notices_ids = array();
//	
//		$notice_count = variable_get('pmb_noticeperpage_search', 10);
//		$notices_pages = array_chunk($notices_ids, $notice_count);
//		$page = min($page, count($notices_pages));
//		$page = max(1, $page);
//		
//		$notices = $pmb_data->get_external_notices($notices_pages[$page-1]);
//		$output.= theme('pmb_external_search_results', $search_terms, array($source_id), $search_fields, $notices, array('page_number' => $page, 'notices_per_pages' => $notice_count, 'section_notice_count' => count($notices_ids)));	
//			
//	}
//	return $output;
    if (!$notice_ids)
    	$notice_ids = array();

	$notice_count = variable_get('pmb_noticeperpage_search', 10);
	$notices_pages = array_chunk($notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_external_notices($notices_pages[$page-1]);
    
	return theme('pmb_external_search_results', $search_terms, $search_sources, $search_fields, $notices, array('page_number' => $page, 'notices_per_pages' => $notice_count, 'section_notice_count' => count($notice_ids)));	
}

function pmb_search_aggregate($search_terms){
	$search_fields = "all_fields";
	$search_fields = explode(',', $search_fields);
	$allowed_search_fields = array_keys(pmb_get_search_fields());
	$search_fields = array_intersect($search_fields, $allowed_search_fields);
	$results = array();
	if ($search_terms && $allowed_search_fields) {
	    $breadcrumb = array();
	    $breadcrumb[] = l(t('Home'), NULL);
	    $breadcrumb[] = l(t('Search the catalog'), 'pmb/search/local');
	    $breadcrumb[] = l(t('Search results'), 'pmb/search/local/'.implode(',', $search_fields).'/'.$search_terms.'/'.$page);
	    drupal_set_breadcrumb($breadcrumb);
		
		$pmb_data = new pmb_data();
		if 	(isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
			$pmb_data->set_user($GLOBALS["user"]);
		$notice_ids = $pmb_data->get_search_notice_ids($search_terms, $search_fields);
	
	    if (!$notice_ids)
	    	$notice_ids = array();
	
		$notice_count = variable_get('pmb_noticeperpage_search', 10);
		$notices_pages = array_chunk($notice_ids, $notice_count);
		$page = min($page, count($notices_pages));
		$page = max(1, $page);
	
//		$notices = $pmb_data->get_notices($notices_pages[$page-1]);
		$notices = $pmb_data->get_notices($notice_ids);
	
		foreach($notices as $notice){
			$result[]=array(
				'link'=> theme('pmb_notice_info', $notice, "link"),
	    	 	'title'=> theme('pmb_notice_info', $notice, "title"),
		     	'snippet'=> theme('pmb_notice_display', $notice, 'medium_line', array())
			);
		}
	}
	return $result;
}

//function pmb_advanced_search_catalog(){
//	$pmb_data = new pmb_data();
//	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
//		$pmb_data->set_user($GLOBALS["user"]);
//	$fields = $pmb_data->getAdvancedSearchFields(true);
//    return theme('pmb_advanced_search_form');	
//}