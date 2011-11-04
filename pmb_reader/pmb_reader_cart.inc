<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_cart.inc,v 1.3 2011-10-21 20:32:23 gueluneau Exp $

function pmb_reader_view_cart($user) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$cart_content = $pmb_data->reader_get_cart();
	
	drupal_set_title(t('My reader account: Cart: '));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Cart'), 'pmb_reader/'.$user->uid.'/cart');
    drupal_set_breadcrumb($breadcrumb);

    $notices = $pmb_data->get_notices($cart_content);
    
    return drupal_get_form('pmb_reader_cart_form', $notices);    
}

function pmb_reader_delete_notices_from_cart($user, $notice_ids) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$pmb_data->reader_delete_notices_from_cart($notice_ids);
}

function pmb_reader_empty_cart($user) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$pmb_data->reader_empty_cart();
}

function pmb_reader_add_notices_to_cart($user, $notice_ids) {
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	$pmb_data->add_notices_to_cart($notice_ids);	
}