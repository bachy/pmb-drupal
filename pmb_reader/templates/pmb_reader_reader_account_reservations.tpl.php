<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_account_reservations.tpl.php,v 1.8 2011-10-21 20:32:25 gueluneau Exp $

$header = array(t('Rank'), t('Title'), t('Information'), t('Action'));

$rows = array();

foreach($reservations as $areservation) {
	$title = '';
	if ($areservation->notice_id) {
		if (isset($parameters['notices'][$areservation->notice_id]['notice']['f']['200'])) {
			foreach($parameters['notices'][$areservation->notice_id]['notice']['f']['200'] as &$afield) {
				if (!isset($afield['a']))
					continue;
				$title .= $afield['a'].' ';
			}
		}
	}
	else if ($areservation->bulletin_id) {
		if(isset($parameters['bulletins'][$areservation->bulletin_id]['bulletin']->bulletin_title))
			$title = $parameters['bulletins'][$areservation->bulletin_id]['bulletin']->bulletin_title; 
	}
	$title = trim($title);
	$notice_link = $title;
	if ($areservation->notice_id) 
		$notice_link = l($title, 'pmb/view_notice/'.$areservation->notice_id);
	else if ($areservation->bulletin_id) 
		$notice_link = l($title, 'pmb/view_bulletin/'.$areservation->bulletin_id);
		
	$resa_caption = '';
	if($areservation->resa_dateend) {
		if (preg_match('/(\d?\d)\/(\d?\d)\/(\d\d\d\d)/', $areservation->resa_dateend,$m)) {
			$time_stamp = mktime(0,0,0,$m[2],$m[1],$m[3]);
			if ($time_stamp < time())
				$resa_caption = t('Your reservation is overtime');
		}
		if (!$resa_caption)
			$resa_caption = t('Your item is holded until the ').$areservation->resa_dateend;
	}
	
	if (!$resa_caption)
		$resa_caption = t('In need of approuval');

	$delete_resa_link = l(t('Delete'), 'pmb_reader/'.$GLOBALS["user"]->uid.'/delete_reservation/'.$areservation->resa_id);
		
	$rows[] = array(
		$areservation->resa_rank,
		$notice_link,
		$resa_caption,
		$delete_resa_link,
	);	
}

$template.= theme('table', $header, $rows);
