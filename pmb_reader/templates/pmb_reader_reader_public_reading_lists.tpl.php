<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_public_reading_lists.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$header = array(t('Name'), t('Description'), t('Author'), t('Access'));

$rows = array();
foreach($reading_lists as $a_reading_list) {
	$link = l($a_reading_list->reading_list_name, 'pmb_reader/'.$reader->uid.'/public_reading_lists/'.$a_reading_list->reading_list_id);
	$access = t('Open');
	if ($a_reading_list->reading_list_confidential && $a_reading_list->reading_list_public) {
		$access = t('Confidential');
	}
	$rows[] = array(
		$link,
		$a_reading_list->reading_list_caption,
		$a_reading_list->reading_list_empr_caption,
		$access,
	);	
}

$template.= theme('table', $header, $rows);

