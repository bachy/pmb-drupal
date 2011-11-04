<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_view_notice.inc,v 1.13 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

function pmb_view_notice($notice_id) {
	if (!$notice_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$notice = $pmb_data->get_notice($notice_id);
	if (!$notice) {
		drupal_set_title(t('Record not found!'));
		drupal_set_message(t('Record not found!'), 'error');
		return '';
	}

	if(   $notice['notice']['header']['rs'] == 'n'
       && $notice['notice']['header']['dt'] == 'a'
       && $notice['notice']['header']['bl'] == 's'
       && $notice['notice']['header']['hl'] == '2'
    ) {	
		//C'est un bulletin
		$bulletin_id = $pmb_data->find_notice_bulletin($notice_id);
		if ($bulletin_id)
			drupal_goto('pmb/view_bulletin/'.$bulletin_id);
    }
			
	$can_reserve_notice = FALSE;
	if (module_exists('pmb_reader'))
		if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)) {
			$can_reserve_notice = $pmb_data->reader_can_reserve_notice($GLOBALS["user"]->pmb_credentials['login'], $GLOBALS["user"], $notice_id, 0);
		}
	
	$title = '';
	if (isset($notice['notice']['f']['200'][0]['a']))
		$title = $notice['notice']['f']['200'][0]['a'];
	drupal_set_title(t('Record').': '.check_plain($title));
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Record').': '.$title, 'pmb/view_notice/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);	
	
    $no_items = false;
    $no_items = false;
    if(   $notice['notice']['header']['rs'] == 'n'
       && $notice['notice']['header']['dt'] == 'a'
       && $notice['notice']['header']['bl'] == 'a'
       && $notice['notice']['header']['hl'] == '2'
    ) {
    	//C'est un article
    	$no_items = true;
    }
    
	$can_add_to_cart = FALSE;
	if (module_exists('pmb_reader'))
		if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)) {
			$can_add_to_cart = TRUE;
		}
    
    switch($notice['notice']['header']['hl']) {
    	case 1:
    		return theme('pmb_serial_view', $notice, array('can_reserve' => $can_reserve_notice, 'no_items' => $no_items));
    		break;
    	case 2:
    		return theme('pmb_notice_view', $notice, array('can_reserve' => $can_reserve_notice, 'no_items' => $no_items, 'can_add_to_cart' => $can_add_to_cart));
    		break;
    	default:
    	case 0:
			return theme('pmb_notice_view', $notice, array('can_reserve' => $can_reserve_notice, 'no_items' => $no_items, 'can_add_to_cart' => $can_add_to_cart));
    		break;
    }
    
}

function pmb_view_external_notice($notice_id) {
	if (!$notice_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$notice = $pmb_data->get_external_notice($notice_id);
	if (!$notice) {
		drupal_set_title(t('Notice not found!'));
		drupal_set_message(t('Notice not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($notice['notice']['f']['200'][0]['a']))
		$title = $notice['notice']['f']['200'][0]['a'];
	if (isset($notice['notice']['f']['801'][0][9]))
		$source = $notice['notice']['f']['801'][0][9];
	drupal_set_title(check_plain($source).' : '.check_plain($title));
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View External Notice').': '.$title, 'pmb/view_external_notice/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	return theme('pmb_external_notice_view', $notice, array());
    
}

function pmb_view_serial($notice_id, $page=1) {
	if (!$notice_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	$notice = $pmb_data->get_notice($notice_id);
	if (!$notice) {
		drupal_set_title(t('Serial not found!'));
		drupal_set_message(t('Serial not found!'), 'error');
		return '';
	}

	$title = '';
	if (isset($notice['notice']['f']['200'][0]['a']))
		$title = $notice['notice']['f']['200'][0]['a'];
	drupal_set_title('Serial: '.check_plain($title));
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('View Serial').': '.$title, 'pmb/view_serial/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);	
	
	$page += 0;

	$bulletins_count = variable_get('pmb_bulletinsperpage_serials', 20);
	$bulletins_pages = array_chunk($notice['bulletins'], $bulletins_count);
	$page = min($page, count($bulletins_pages));
	$page = max(1, $page);
	
	$bulletins = $bulletins_pages[$page-1];
	
	return theme('pmb_serial_view', $notice, array('bulletins' => $bulletins, 'page_number' => $page, 'bulletins_per_page' => $bulletins_count));
}

function pmb_view_bulletin($bulletin_id) {
	if (!$bulletin_id) {
		return 'ERROR!';
	}
	$pmb_data = new pmb_data();
	$bulletin = $pmb_data->get_bulletin($bulletin_id);
	if (!$bulletin) {
		drupal_set_title(t('Issue not found!'));
		drupal_set_message(t('Issue not found!'), 'error');
		return '';
	}
	$serial = $pmb_data->get_notice($bulletin['bulletin']->serial_id);
	
	if ($bulletin['analysis']) {
		$analysis = $pmb_data->get_notices($bulletin['analysis']);
	}
	else
		$analysis = array();
	
	$can_reserve_notice = FALSE;
	if (module_exists('pmb_reader'))
		if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)) {
			$can_reserve_notice = $pmb_data->reader_can_reserve_notice($GLOBALS["user"]->pmb_credentials['login'], $GLOBALS["user"], 0, $bulletin_id);
		}

	return theme('pmb_bulletin_view', $bulletin, $serial, array('can_reserve' => $can_reserve_notice, 'analysis' => $analysis));

}
