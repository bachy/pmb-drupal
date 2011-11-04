<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_public_reading_list.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$header = array(t('Name'), t('Description'), t('Author'));

$rows = array();
$rows[] = array(
	$reading_list->reading_list_name,
	$reading_list->reading_list_caption,
	$reading_list->reading_list_empr_caption,
);	

$template.= theme('table', $header, $rows);

$rows = array();
$header = array('');
foreach($notices as $anotice) {
		$rows[] =  array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
}
$template.= theme('table', $header, $rows);