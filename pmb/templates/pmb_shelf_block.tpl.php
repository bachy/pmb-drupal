<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_shelf_block.tpl.php,v 1.4 2011-10-21 20:32:24 gueluneau Exp $

$header = array(
	'',
);

$template.= $shelf->comment;

$rows = array();

if (isset($notices)) {
	foreach($notices as $anotice) {
		$rows[] =  array(theme('pmb_notice_display', $anotice, 'small_line', array()));
	}

	$template.= theme('table', $header, $rows);
}
else {
	$template.= t('This shelf has no notices');
}
