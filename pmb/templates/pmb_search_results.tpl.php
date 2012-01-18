<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_search_results.tpl.php,v 1.7 2011-10-21 20:32:24 gueluneau Exp $

$template.= t('Search: ').check_plain($search_terms);
$template.= '<br />';

$header = array(
	'',
);

$rows = array();

if (isset($notices) && count($notices)) {
	dsm($notices);
	foreach($notices as $anotice) {
		$rows[] =  array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
	}

	$template.= theme('table', $header, $rows);	
	
	$search_terms_u = $search_terms;
	$search_fields_u = implode(',', $search_fields);
	$page_path = 'pmb/search/local/'.$search_fields_u.'/'.$search_terms_u.'/';
	$link_maker_function = create_function('$page_number', 'return "'.addslashes($page_path).'".$page_number;');
	$template.= theme('pmb_pager', $parameters['page_number'], ceil($parameters['section_notice_count'] / $parameters['notices_per_pages']), array(), 7, $link_maker_function);
}
else {
	$template.= t('This search has no results');
}
