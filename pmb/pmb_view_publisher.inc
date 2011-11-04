<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_view_publisher.inc,v 1.5 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

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