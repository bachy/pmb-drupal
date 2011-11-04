<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_reading_lists.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$template.= '<h2>'.t('Your lists').'</h2>';

$header = array(t('Name'), t('Description'));

$rows = array();
foreach($reading_lists as $a_reading_list) {
	$link = l($a_reading_list->reading_list_name, 'pmb_reader/'.$reader->uid.'/reading_lists/'.$a_reading_list->reading_list_id);
	$rows[] = array(
		$link,
		$a_reading_list->reading_list_caption,
	);	
}

$template.= theme('table', $header, $rows);

$template.= '<h2>'.t('Public lists').'</h2>';
$template.= l(t('View public reading lists'), 'pmb_reader/'.$reader->uid.'/public_reading_lists/');