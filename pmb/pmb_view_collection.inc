<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_view_collection.inc,v 1.5 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

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