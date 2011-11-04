<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_section.inc,v 1.6 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

function pmb_browse_section($section_id, $page=1) {
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
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse_catalog/locations');
    $breadcrumb[] = l(t('Browse location').': '.$location->location->location_caption, 'pmb/browse_location/'.$location->location->location_id);
    $breadcrumb[] = l(t('Browse section').': '.$section->section_caption, 'pmb/browse_section/'.$section->section_id);
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