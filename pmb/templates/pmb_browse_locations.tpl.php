<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_locations.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$header = array(
	t('Location'),
	t('Number of sections')
);

$rows = array();
foreach($locations_and_sections as $alocation) {
	$alocation->location->location_id += 0;
	$rows[] = array(l($alocation->location->location_caption, 'pmb/browse_location/'.$alocation->location->location_id), count($alocation->sections));
}

$template.= theme('table', $header, $rows);
