<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reservations.inc,v 1.5 2011-10-21 20:32:23 gueluneau Exp $

function pmb_reader_reservations($user) {
	drupal_set_title(t('My reader account: Reservations'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('My reader account'), 'pmb_reader/'.$user->uid);
    $breadcrumb[] = l(t('Reservations'), 'pmb_reader/'.$user->uid.'/reservations');
    drupal_set_breadcrumb($breadcrumb);
	
    require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    $pmb_data = new pmb_data();
    $reservations = $pmb_data->reader_get_reservations($user->pmb_credentials['login'], $user);
	
    $notice_ids = array();
    $bulletins_ids = array();
    foreach($reservations as $areservation) {
    	if ($areservation->notice_id)
	    	$notice_ids[] = $areservation->notice_id;
    	if ($areservation->bulletin_id)
	    	$bulletins_ids[] = $areservation->bulletin_id;
    }
    
    $notices = $pmb_data->get_notices($notice_ids);
    $bulletins = $pmb_data->get_bulletins($bulletins_ids);
    
	return theme('pmb_reader_reader_account_reservations', $user, $reservations, array('notices'=>$notices, 'bulletins' => $bulletins));
}

function pmb_reader_delete_reservation($user, $reservation_id) {
	$reservation_id += 0;
	if ($reservation_id) {
		require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
    	$pmb_data = new pmb_data();
    	$pmb_data->reader_delete_reservation($user->pmb_credentials['login'], $user, $reservation_id);
	}
	drupal_goto('pmb_reader/'.$user->uid.'/reservations');
}

function pmb_reader_add_reservation($user, $notice_id, $location_id=0) {
	$bulletin_id = 0;
	if($notice_id && ($notice_id[0] == 'b')) {
		$bulletin_id = substr($notice_id, 1) + 0;
	}
	else {
		$notice_id += 0;
	}
	if (!($notice_id || $bulletin_id)) {
		drupal_set_title(t('Missing notice id!'));
		drupal_set_message(t('Missing notice id!'), 'error');
		return FALSE;
	}

	if (!(isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials)))
		return FALSE;
	
	require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');
   	$pmb_data = new pmb_data();
	$pmb_data->set_user($GLOBALS["user"]);

	$notice_title = '';
	if ($bulletin_id) {
		$bulletin = $pmb_data->get_bulletin($bulletin_id);
		$notice_title = $bulletin['bulletin']->bulletin_title;
	}
	else {
		$notice = $pmb_data->get_notice($notice_id);
		if (isset($notice['notice']['f']['200'])) {
			foreach($notice['notice']['f']['200'] as &$afield) {
				if (!isset($afield['a']))
					continue;
				$notice_title .= ' '.$afield['a'];
			}
		}
		$notice_title = trim($notice_title);		
	}
	
	drupal_set_title(t('Add a reservation'));
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Notice: '.$notice_title), 'pmb/view_notice/'.$notice_id);
    $breadcrumb[] = l(t('Add a reservation'), 'pmb_reader/'.$user->uid.'/add_reservation/'.$notice_id);
    drupal_set_breadcrumb($breadcrumb);
	
    if (!$location_id) {
    	if (!$pmb_data->reader_add_reservation($notice_id, $bulletin_id, 0)) {
			drupal_set_message(t('Could not create reservation!'), 'error');
    	}
    }

	user_save($user, array('pmb_reader_reservations' => array('fetched_date' => 0, 'reservations' => NULL)));    
    
	drupal_goto('pmb_reader/'.$user->uid.'/reservations');
}

