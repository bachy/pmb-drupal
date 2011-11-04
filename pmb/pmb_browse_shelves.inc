<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_shelves.inc,v 1.3 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

function pmb_browse_shelves() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$shelves = $pmb_data->get_shelves();
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse_catalog/shelves');
    drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_shelves', $shelves, array());
}

function pmb_browse_shelf($shelf_id, $page=1) {
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