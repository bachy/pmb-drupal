<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_account.inc,v 1.8 2011-10-21 20:32:23 gueluneau Exp $

function pmb_reader_reader_information($user) {
	drupal_set_title(t('My reader account: Summary'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    drupal_set_breadcrumb($breadcrumb);	
	return theme('pmb_reader_reader_account_summary', $user, array());
}

function pmb_reader_loans($user) {
	drupal_set_title('My reader account: Loans');
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Loans'), 'pmb_reader/'.$user->uid.'/loans');
    drupal_set_breadcrumb($breadcrumb);
	
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
    $loans = $pmb_data->reader_get_loans($user->pmb_credentials['login'], $user);
	
	return theme('pmb_reader_reader_account_loans', $user, $loans, array());
}
