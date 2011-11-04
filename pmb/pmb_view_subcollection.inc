<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_view_subcollection.inc,v 1.5 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

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