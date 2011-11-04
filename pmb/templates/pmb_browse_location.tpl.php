<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_location.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$header = array(
	'',
	t('Section')
);

$rows = array();
foreach($location->sections as $asection) {
	$rows[] = array('<img src="http://tence.bibli.fr/opac/'.$asection->section_image.'"/>', l($asection->section_caption, 'pmb/browse_section/'.$asection->section_id));
}

$template.= theme('table', $header, $rows);
