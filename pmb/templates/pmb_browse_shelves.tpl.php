<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_shelves.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$header = array(
	t('Shelf'),
	t('Comment'),
);

$rows = array();
foreach($shelves as $ashelf) {
	$rows[] = array(l($ashelf->name, 'pmb/browse/shelves/'.$ashelf->id), $ashelf->comment);
}

$template.= theme('table', $header, $rows);
