<?php

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

/**
 * Search Local
 * 
 * menu callback
 * 
 */
function pmb_search_catalog($search_fields = null, $search_terms = null, $page = 1){
	if($search_fields && $search_terms)
		return _pmb_search_catalog_search($search_fields, $search_terms, $page);

	return _pmb_search_catalog();
}

function _pmb_search_catalog(){
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);

  return theme('pmb_search_form');
}

function _pmb_search_catalog_search($search_fields, $search_terms, $page) {
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

/**
 * Search External
 * 
 * menu callback
 * 
 */
function pmb_search_external_catalog($search_fields = null, $search_sources = null, $search_terms = null, $page = 1) {
	
	if($search_fields && $search_sources && $search_terms)
		return _pmb_search_external_catalog_search($search_fields, $search_sources, $search_terms, $page);
	
	return _pmb_search_external_catalog();
	
}

function _pmb_search_external_catalog(){
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

function _pmb_search_external_catalog_search($search_fields, $search_sources, $search_terms, $page = 1) {
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
/*
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
*/
/*
function pmb_advanced_search_catalog(){
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$fields = $pmb_data->getAdvancedSearchFields(true);
   return theme('pmb_advanced_search_form');	
}
*/
/**
 * pmb_browse_locations()
 * 
 * menu callback
 * 
 */
function pmb_browse_locations($loc_id = null, $sect_id = null, $page = 1){
	if($loc_id && $sect_id)
		return _pmb_browse_section($loc_id, $sect_id, $page);
		
	if($loc_id)
		return _pmb_browse_location($loc_id);
		
	return _pmb_browse_locations();
}

/**
 * _pmb_browse_locations()
 */
function _pmb_browse_locations() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$locations_and_sections = $pmb_data->get_location_and_sections();
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse/locations');
    drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_locations', $locations_and_sections, array());
}

/**
 * _pmb_browse_location()
 */
function _pmb_browse_location($location_id) {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$locations_and_sections = $pmb_data->get_location_and_sections();
	if(!isset($locations_and_sections[$location_id])) {
		drupal_set_title(t('Location not found!'));
		drupal_set_message(t('Location not found!'), 'error');		
		return '';
	}
	$location = $locations_and_sections[$location_id];
	
	drupal_set_title(t('Location: ').check_plain($location->location->location_caption));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse/locations');
    $breadcrumb[] = l(t('Browse location').': '.$location->location->location_caption, 'pmb/browse/locations/'.$location_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	return theme('pmb_browse_location', $location, array());
}

/**
 * _pmb_browse_section()
 */
function _pmb_browse_section($location_id, $section_id, $page) {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$locations_and_sections = $pmb_data->get_location_and_sections();
	$section = array();
	$location = array();
	foreach($locations_and_sections as $alocation) {
		foreach($alocation->sections as $asection) {
			if ($asection->section_id == $section_id) {
				$section = $asection;
				break;
			}
		}
		if ($section) {
			$location = $alocation;
			break;
		}
	}

	if(!isset($location)) {
		drupal_set_title(t('Location not found!'));
		drupal_set_message(t('Location not found!'), 'error');		
		return '';
	}
	if(!isset($section)) {
		drupal_set_title(t('Section not found!'));
		drupal_set_message(t('Section not found!'), 'error');		
		return '';
	}	
	
	drupal_set_title(t('Section').': '.check_plain($section->section_caption));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse/locations');
    $breadcrumb[] = l(t('Browse location').': '.$location->location->location_caption, 'pmb/browse/locations/'.$location->location->location_id);
    $breadcrumb[] = l(t('Browse section').': '.$section->section_caption, 'pmb/browse/locations/'.$location->location->location_id.'/'.$section->section_id);
    drupal_set_breadcrumb($breadcrumb);	
	
    $notice_ids = $pmb_data->get_section_notice_ids($section_id);
    if (!$notice_ids)
    	$notice_ids = array();

	$notice_count = variable_get('pmb_noticeperpage_section', 10);
	$notices_pages = array_chunk($notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
    
	return theme('pmb_browse_section', $location, $section, $notices, array('page_number' => $page, 'notices_per_pages' => $notice_count, 'section_notice_count' => count($notice_ids)));;
}


/**
 * pmb_browse_thesauri
 * 
 * menu callback
 * 
 */
function pmb_browse_thesauri($category_id = null, $page=1) {
	if($category_id)
		return _pmb_browse_category($category_id, $page);
		
	return _pmb_browse_thesauri();
}

/**
 * _pmb_browse_thesauri()
 */
function _pmb_browse_thesauri() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$thesauri = $pmb_data->get_thesauri();

	if (count($thesauri) == 1) {
		drupal_goto('pmb/browse_category/'.$thesauri[0]->thesaurus_num_root_node);
	}
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog - Thesauri'), 'pmb/browse/thesauri');
    drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_thesauri', $thesauri, array());
}

/**
 * _pmb_browse_category()
 */
function _pmb_browse_category($category_id, $page) {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$category = $pmb_data->get_category($category_id);

	if(!isset($category)) {
		drupal_set_title(t('Category not found!'));
		drupal_set_message(t('Category not found!'), 'error');		
		return '';
	}

	if ($category->node->node_target_id) {
		drupal_goto('pmb/browse/thesauri/'.$category->node->node_target_id);
	}
	
	$is_thesaurus = FALSE;
	$thesauri = $pmb_data->get_thesauri();
	$the_thesaurus = NULL;
	foreach($thesauri as $athesaurus) {
		if ($athesaurus->thesaurus_id == $category->node->node_thesaurus) {
			$the_thesaurus = $athesaurus;
		}
	}
	$is_thesaurus = $the_thesaurus->thesaurus_num_root_node == $category->node->node_id;
	if ($is_thesaurus) {
		$caption = $the_thesaurus->thesaurus_caption;
		drupal_set_title(t('Thesaurus').': '.$caption);		
	}
	else {
		$chosen_language = 'fr_FR';
		$caption = '';
		foreach($category->node->node_categories as $acategory) {
			if ($acategory->category_lang == $chosen_language) {
				$caption = $acategory->category_caption;
				break;
			}
		}
		if (!$caption) {
			$caption = count($category->node->node_categories) ? $category->node->node_categories[0]->category_caption : t('Unknown caption');
			if (!$caption) {
				$caption = t('Unknown caption');
			}
		}
		drupal_set_title(t('Category').': '.$caption);
	}
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog - Thesauri'), 'pmb/browse/thesauri');
    if ($the_thesaurus)
    	$breadcrumb[] = l(t('Thesaurus').': '.$the_thesaurus->thesaurus_caption, 'pmb/browse/thesauri/'.$the_thesaurus->thesaurus_num_root_node);
    if (!$is_thesaurus) {
	    foreach($category->node->node_path as $apath) {
			$caption = '';
			foreach($apath->categories as $acategory) {
				if ($acategory->category_lang == $chosen_language) {
					$caption = $acategory->category_caption;
					break;
				}
			}
			if (!$caption) {
				$caption = count($apath->categories) ? $apath->categories[0]->category_caption : t('Unknown caption');
				if (!$caption) {
					$caption = t('Unknown caption');
				}
			}    	
	    	
	    	$breadcrumb[] = l($caption, 'pmb/browse/thesauri/'.$apath->node_id);	
	    }
    }
    drupal_set_breadcrumb($breadcrumb);

	$page += 0;
	$notice_count = variable_get('pmb_noticeperpage_categories', 5);
	$notices_pages = array_chunk($category->notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	return theme('pmb_browse_category', $category, array('notices' => $notices, 'page_number' => $page, 'notices_per_pages' => $notice_count));
}

/**
 * pmb_browse_serials()
 * 
 * menu callback
 * 
 */
function pmb_browse_serials(){
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$serials = $pmb_data->get_serials();

    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog - Serials'), 'pmb/browse_catalog/serials');
    drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_serials', $serials, array());
}

/**
 * pmb_browse_shelves()
 * 
 * menu callback
 * 
 */
function pmb_browse_shelves($shelf_id = null, $page=1){

	if($shelf_id)
		return _pmb_browse_shelf($shelf_id, $page);
	
	return _pmb_browse_shelves();
	
}

/**
 * _pmb_browse_shelves()
 */
function _pmb_browse_shelves() {
	
	$pmb_data = new pmb_data();

	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
		
	$shelves = $pmb_data->get_shelves();
	
	  $breadcrumb = array(
	 	l(t('Home'), NULL),
		l(t('Browse the catalog'), 'pmb/browse/shelves'),
	);
	  drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_shelves', $shelves, array());
}

/**
 * _pmb_browse_shelf()
 */
function _pmb_browse_shelf($shelf_id, $page) {
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
		drupal_set_title(t('Shelf not found!'));
		drupal_set_message(t('Shelf not found!'), 'error');		
		return '';
	}
	
	drupal_set_title(t('Shelf').': '.check_plain($shelf->name));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse_catalog/shelves');
    $breadcrumb[] = l(t('Browse shelf').': '.$shelf->name, 'pmb/browse_shelf/'.$shelf->id);
    drupal_set_breadcrumb($breadcrumb);	
	
    $notice_ids = $pmb_data->get_shelf_notice_ids($shelf_id);
    if (!$notice_ids)
    	$notice_ids = array();

	$notice_count = variable_get('pmb_noticeperpage_shelf', 10);
	$notices_pages = array_chunk($notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
    
	return theme('pmb_browse_shelf', $shelf, $notices, array('page_number' => $page, 'notices_per_pages' => $notice_count, 'section_notice_count' => count($notice_ids)));;
}


/**
 * VIEWS
 */
/**
 * pmb_view_notice($notice_id) 
 * 
 * menu callback
 */
function pmb_view_notice($notice_id) {
	if (!$notice_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$notice = $pmb_data->get_notice($notice_id);
	if (!$notice) {
		drupal_set_title(t('Record not found!'));
		drupal_set_message(t('Record not found!'), 'error');
		return '';
	}

	if(   $notice['notice']['header']['rs'] == 'n'
       && $notice['notice']['header']['dt'] == 'a'
       && $notice['notice']['header']['bl'] == 's'
       && $notice['notice']['header']['hl'] == '2'
    ) {	
		//C'est un bulletin
		$bulletin_id = $pmb_data->find_notice_bulletin($notice_id);
		if ($bulletin_id)
			drupal_goto('pmb/view_bulletin/'.$bulletin_id);
    }
			
	$can_reserve_notice = FALSE;
	if (module_exists('pmb_reader'))
		if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)) {
			$can_reserve_notice = $pmb_data->reader_can_reserve_notice($GLOBALS["user"]->pmb_credentials['login'], $GLOBALS["user"], $notice_id, 0);
		}
	
	$title = '';
	if (isset($notice['notice']['f']['200'][0]['a']))
		$title = $notice['notice']['f']['200'][0]['a'];
	drupal_set_title(t('Record').': '.check_plain($title));
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Record').': '.$title, 'pmb/view_notice/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);	
	
    $no_items = false;
    $no_items = false;
    if(   $notice['notice']['header']['rs'] == 'n'
       && $notice['notice']['header']['dt'] == 'a'
       && $notice['notice']['header']['bl'] == 'a'
       && $notice['notice']['header']['hl'] == '2'
    ) {
    	//C'est un article
    	$no_items = true;
    }
    
	$can_add_to_cart = FALSE;
	if (module_exists('pmb_reader'))
		if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)) {
			$can_add_to_cart = TRUE;
		}
    
    switch($notice['notice']['header']['hl']) {
    	case 1:
    		return theme('pmb_serial_view', $notice, array('can_reserve' => $can_reserve_notice, 'no_items' => $no_items));
    		break;
    	case 2:
    		return theme('pmb_notice_view', $notice, array('can_reserve' => $can_reserve_notice, 'no_items' => $no_items, 'can_add_to_cart' => $can_add_to_cart));
    		break;
    	default:
    	case 0:
			return theme('pmb_notice_view', $notice, array('can_reserve' => $can_reserve_notice, 'no_items' => $no_items, 'can_add_to_cart' => $can_add_to_cart));
    		break;
    }
    
}

function pmb_view_external_notice($notice_id) {
	if (!$notice_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$notice = $pmb_data->get_external_notice($notice_id);
	if (!$notice) {
		drupal_set_title(t('Notice not found!'));
		drupal_set_message(t('Notice not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($notice['notice']['f']['200'][0]['a']))
		$title = $notice['notice']['f']['200'][0]['a'];
	if (isset($notice['notice']['f']['801'][0][9]))
		$source = $notice['notice']['f']['801'][0][9];
	drupal_set_title(check_plain($source).' : '.check_plain($title));
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View External Notice').': '.$title, 'pmb/view_external_notice/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	return theme('pmb_external_notice_view', $notice, array());
    
}

function pmb_view_serial($notice_id, $page=1) {
	if (!$notice_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	$notice = $pmb_data->get_notice($notice_id);
	if (!$notice) {
		drupal_set_title(t('Serial not found!'));
		drupal_set_message(t('Serial not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($notice['notice']['f']['200'][0]['a']))
		$title = $notice['notice']['f']['200'][0]['a'];
	drupal_set_title('Serial: '.check_plain($title));
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Serial').': '.$title, 'pmb/view_serial/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	$page += 0;

	$bulletins_count = variable_get('pmb_bulletinsperpage_serials', 20);
	$bulletins_pages = array_chunk($notice['bulletins'], $bulletins_count);
	$page = min($page, count($bulletins_pages));
	$page = max(1, $page);
	
	$bulletins = $bulletins_pages[$page-1];
	
	return theme('pmb_serial_view', $notice, array('bulletins' => $bulletins, 'page_number' => $page, 'bulletins_per_page' => $bulletins_count));
}

function pmb_view_bulletin($bulletin_id) {
	if (!$bulletin_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	$bulletin = $pmb_data->get_bulletin($bulletin_id);
	if (!$bulletin) {
		drupal_set_title(t('Issue not found!'));
		drupal_set_message(t('Issue not found!'), 'error');
		return '';
	}
	$serial = $pmb_data->get_notice($bulletin['bulletin']->serial_id);
	
	if ($bulletin['analysis']) {
		$analysis = $pmb_data->get_notices($bulletin['analysis']);
	}
	else
		$analysis = array();
	
	$can_reserve_notice = FALSE;
	if (module_exists('pmb_reader'))
		if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)) {
			$can_reserve_notice = $pmb_data->reader_can_reserve_notice($GLOBALS["user"]->pmb_credentials['login'], $GLOBALS["user"], 0, $bulletin_id);
		}

	return theme('pmb_bulletin_view', $bulletin, $serial, array('can_reserve' => $can_reserve_notice, 'analysis' => $analysis));

}

function pmb_view_author($author_id, $page=1) {
	if (!$author_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$author = $pmb_data->get_author($author_id);
	if (!$author) {
		drupal_set_title(t('Author not found!'));
		drupal_set_message(t('Author not found!'), 'error');
		return '';
	}
	//highlight_string(print_r($author, true));
	$title = '';
	if (isset($author->information->author_name))
		$title = $author->information->author_name;
	if (isset($author->information->author_rejete))
		$title .= ' '.$author->information->author_rejete;
	$title = trim($title);
	drupal_set_title(t('Author').': '.check_plain($title));

    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Author').': '.$title, 'pmb/view_author/'.$author_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	$page += 0;

	$notice_count = variable_get('pmb_noticeperpage_author', 3);
	$notices_pages = array_chunk($author->notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	
	return theme('pmb_author_view', $author, array('notices' => $notices, 'page_number' => $page, 'notices_per_pages' => $notice_count));
}

function pmb_view_publisher($publisher_id, $page=1) {
	if (!$publisher_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$publisher = $pmb_data->get_publisher($publisher_id);
	if (!$publisher) {
		drupal_set_title(t('Publisher not found!'));
		drupal_set_message(t('Publisher not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($publisher->information->publisher_name))
		$title = $publisher->information->publisher_name;
	$title = trim($title);
	drupal_set_title(t('Publisher').': '.check_plain($title));

    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Publisher').': '.$title, 'pmb/view_publisher/'.$publisher_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	$page += 0;

	$notice_count = variable_get('pmb_noticeperpage_publisher', 3);
	$notices_pages = array_chunk($publisher->notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	
	return theme('pmb_publisher_view', $publisher, array('notices' => $notices, 'page_number' => $page, 'notices_per_pages' => $notice_count));
}

function pmb_view_collection($collection_id, $page=1) {
	if (!$collection_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$collection = $pmb_data->get_collection($collection_id);
	if (!$collection) {
		drupal_set_title(t('Collection not found!'));
		drupal_set_message(t('Collection not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($collection->information->collection_name))
		$title = $collection->information->collection_name;
	$title = trim($title);
	drupal_set_title(t('Collection').': '.check_plain($title));

    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Collection').': '.$title, 'pmb/view_collection/'.$collection_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	$page += 0;

	$notice_count = variable_get('pmb_noticeperpage_collection', 3);
	$notices_pages = array_chunk($collection->notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	
	$parent_publisher = $pmb_data->get_publisher($collection->information->collection_parent);
	
	return theme('pmb_collection_view', $collection, $parent_publisher, array('notices' => $notices, 'page_number' => $page, 'notices_per_pages' => $notice_count));
}

function pmb_view_subcollection($subcollection_id, $page=1) {
	if (!$subcollection_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$subcollection = $pmb_data->get_subcollection($subcollection_id);
	if (!$subcollection) {
		drupal_set_title(t('Subcollection not found!'));
		drupal_set_message(t('Subcollection not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($subcollection->information->sous_collection_name))
		$title = $subcollection->information->sous_collection_name;
	$title = trim($title);
	drupal_set_title(t('Subcollection').': '.check_plain($title));

    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Subcollection').': '.$title, 'pmb/view_subcollection/'.$subcollection_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	$page += 0;

	$notice_count = variable_get('pmb_noticeperpage_subcollection', 3);
	$notices_pages = array_chunk($subcollection->notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	
	$parent_collection = $pmb_data->get_collection($subcollection->information->sous_collection_parent);

	return theme('pmb_subcollection_view', $subcollection, $parent_collection, array('notices' => $notices, 'page_number' => $page, 'notices_per_pages' => $notice_count));
}

/**
 * pmb_debug
 * 
 * menu callback
 * 
 */
function pmb_debug(){
	
}


/**
 * Fonctions Ajax 
 */

/**
 * pmb_ajax_get_field()
 * 
 * menu callback
 */
function pmb_ajax_get_field(){
	$form = pmb_ajax_get_field_form();
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

function pmb_ajax_get_field_form() {
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

/**
 * pmb_get_page_shelf_block()
 * 
 * menu callback
 * 
 */
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
