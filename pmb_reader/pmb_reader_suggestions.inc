<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_suggestions.inc,v 1.4 2011-10-21 20:32:23 gueluneau Exp $

function pmb_reader_suggestions($user) {
	drupal_set_title(t('My reader account: Suggestions'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Suggestions'), 'pmb_reader/'.$user->uid.'/suggestions');
    drupal_set_breadcrumb($breadcrumb);

	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;
	
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
    $suggestions = $pmb_data->reader_get_suggestions();
	
	return theme('pmb_reader_reader_account_suggestions', $user, $suggestions, array());
}

function pmb_reader_suggestion_edit($user, $suggestion_id) {
	drupal_set_title(t('View, add or edit a suggestion'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Suggestions'), 'pmb_reader/'.$user->uid.'/suggestions');
    drupal_set_breadcrumb($breadcrumb);

	if (!(isset($user->uid) && isset($user->pmb_credentials)))
		return FALSE;

    $suggestion = array();

    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
	$pmb_data->set_user($user);
	$categ_and_sources = $pmb_data->reader_get_suggestion_sources_and_categories();
    
	if ($suggestion_id == 'add') {
		
	}
	else if($suggestion_id+0) {
	    $suggestions = $pmb_data->reader_get_suggestions();
		
	    foreach($suggestions as $asuggestion) {
	    	if ($asuggestion->sugg_id == $suggestion_id) {
	    		$suggestion = $asuggestion;
	    		break;
	    	}
	    }
	    
		if (!$suggestion) {
			drupal_set_title(t('Suggestion not found!'));
			drupal_set_message(t('Suggestion not found!'), 'error');
	    	return '';
		}
	}
    
    $result = drupal_get_form('pmb_reader_suggestion_edit_form', $suggestion, $categ_and_sources);
//	$result .= theme('pmb_reader_reader_account_suggestions', $user, $suggestions, array());
	
	return $result;
}

