<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_section.tpl.php,v 1.5 2011-10-21 20:32:25 gueluneau Exp $

$header = array(
	'',
);

$rows = array();

if (isset($notices)) {
	foreach($notices as $anotice) {
		$rows[] =  array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
	}

	$template.= theme('table', $header, $rows);	
	
	$link_maker_function = create_function('$page_number', 'return "pmb/browse_section/'.$section->section_id.'/".$page_number;');
	$template.= theme('pmb_pager', $parameters['page_number'], ceil($parameters['section_notice_count'] / $parameters['notices_per_pages']), array(), 7, $link_maker_function);
}
else {
	$template.= t('This section has no records');
}
