<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reading_lists.inc,v 1.3 2011-10-21 20:32:23 gueluneau Exp $

function pmb_reader_view_reading_lists($user) {
	drupal_set_title(t('My reader account: Reading Lists'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Reading Lists'), 'pmb_reader/'.$user->uid.'/reading_lists');
    drupal_set_breadcrumb($breadcrumb);

	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
    $reading_lists = $pmb_data->reader_get_reading_lists();
	
	return theme('pmb_reader_reader_reading_lists', $user, $reading_lists, array());
}

function pmb_reader_view_public_reading_lists($user) {
	drupal_set_title(t('My reader account: Public Reading Lists'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Public Reading Lists'), 'pmb_reader/'.$user->uid.'/public_reading_lists');
    drupal_set_breadcrumb($breadcrumb);

	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
    $reading_lists = $pmb_data->reader_get_public_reading_lists();
	
	return theme('pmb_reader_reader_public_reading_lists', $user, $reading_lists, array());
}

function pmb_reader_view_reading_list($user, $list_id) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$reading_lists = $pmb_data->reader_get_reading_lists();
	$the_list = FALSE;
	foreach ($reading_lists as $alist) {
		if ($alist->reading_list_id == $list_id) {
			$the_list = $alist;
			break;
		}
	}
	if (!$the_list) {
		drupal_set_title(t('Reading list not found!'));
		drupal_set_message(t('Reading list not found!'), 'error');
		return FALSE;
	}
	
	drupal_set_title(t('My reader account: Reading List: '.$the_list->reading_list_name));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Reading Lists'), 'pmb_reader/'.$user->uid.'/reading_lists');
    $breadcrumb[] = l(t($the_list->reading_list_name), 'pmb_reader/'.$user->uid.'/reading_lists/'.$the_list->reading_list_id);
    drupal_set_breadcrumb($breadcrumb);

    $notices = $pmb_data->get_notices($the_list->reading_list_notice_ids);
    
	return drupal_get_form('pmb_reader_reading_list_form', $the_list, $notices);
}

function pmb_reader_view_public_reading_list($user, $list_id) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$reading_lists = $pmb_data->reader_get_public_reading_lists();
	$the_list = FALSE;
	foreach ($reading_lists as $alist) {
		if ($alist->reading_list_id == $list_id) {
			$the_list = $alist;
			break;
		}
	}
	if (!$the_list) {
		drupal_set_title(t('Reading list not found!'));
		drupal_set_message(t('Reading list not found!'), 'error');
		return FALSE;
	}
	
	drupal_set_title(t('My reader account: Public Reading List: '.$the_list->reading_list_name));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Reading Lists'), 'pmb_reader/'.$user->uid.'/public_reading_lists');
    $breadcrumb[] = l(t($the_list->reading_list_name), 'pmb_reader/'.$user->uid.'/public_reading_list/'.$the_list->reading_list_id);
    drupal_set_breadcrumb($breadcrumb);

    $notices = $pmb_data->get_notices($the_list->reading_list_notice_ids);
    
	return theme('pmb_reader_reader_public_reading_list', $user, $the_list, $notices, array());
}

function pmb_reader_add_notices_to_reading_list($user, $list_id, $notice_ids) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$pmb_data->add_notices_to_reading_list($list_id, $notice_ids);
}


function pmb_reader_remove_notices_from_reading_list($user, $list_id, $notice_ids) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$pmb_data->remove_notices_to_reading_list($list_id, $notice_ids);
}

function pmb_reader_empty_reading_list($user, $list_id) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$pmb_data->empty_reading_list($list_id);
}

