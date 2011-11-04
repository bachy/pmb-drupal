<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_view_author.inc,v 1.5 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

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