<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_account_suggestions.tpl.php,v 1.5 2011-10-21 20:32:25 gueluneau Exp $

$header = array(t('Title'), t('Author'), t('Publisher'), t('State'), t('View/Edit'));

$rows = array();

foreach($suggestions as $asuggestion) {
	$link = $asuggestion->sugg_state == 1 ? l(t('View/Edit'), 'pmb_reader/'.$reader->uid.'/suggestions/'.$asuggestion->sugg_id) : l(t('View'), 'pmb_reader/'.$reader->uid.'/suggestions/'.$asuggestion->sugg_id);
	$rows[] = array(
		$asuggestion->sugg_title,
		$asuggestion->sugg_author,
		$asuggestion->sugg_editor,
		$asuggestion->sugg_state_caption,
		$link,
	);	
}

$template.= theme('table', $header, $rows);

$template.= '<br />';
$template.= l(t('Add a suggestion'), 'pmb_reader/'.$reader->uid.'/suggestions/add');