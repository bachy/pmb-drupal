<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_templates.inc,v 1.5 2011-10-22 08:08:52 arenou Exp $

/**
* Get pmb_notice_diplay template
* @param current_page 
* @param page_count 
* @param tags 
* @param quantity 
* @param link_generator_callback 
* @return html template
*/
function theme_pmb_pager($current_page,$page_count,$tags,$quantity,$link_generator_callback){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_pager.tpl.php');
	return $template;
}

/**
* Get pmb_notice_diplay template
* @param notice pmb_unimarc notice array;
* @param display_type display mode (medium_line, small_line)
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_notice_display($notice,$display_type,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_notice_display.tpl.php');
	return $template;
}

/**
* Get pmb_notice_view template
* @param notice pmb_unimarc notice array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_notice_view($notice,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_notice_view.tpl.php');
	return $template;
}

/**
* Get pmb_notice_info template
* @param notice pmb_unimarc notice array;
* @param info info to dispaly
* @return html template
*/
function theme_pmb_notice_info($notice,$info=""){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_notice_info.tpl.php');
	return $template;
}

/**
* Get pmb_external_notice_view template
* @param notice pmb_unimarc notice array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_external_notice_view($notice,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_external_notice_view.tpl.php');
	return $template;
}

/**
* Get pmb_serial_view template
* @param notice pmb_unimarc notice array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_serial_view($notice,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_serial_view.tpl.php');
	return $template;
}

/**
* Get pmb_bulletin_view template
* @param bulletin pmb_unimarc bulletin array;
* @param serial pmb_unimarc serial array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_bulletin_view($bulletin,$serial,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_bulletin_view.tpl.php');
	return $template;
}

/**
* Get pmb_external_notice_diplay template
* @param notice pmb_unimarc notice array;
* @param display_type display mode (medium_line, small_line)
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_external_notice_display($notice,$display_type,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_external_notice_display.tpl.php');
	return $template;
}

/**
* Get pmb_author_view template
* @param author author array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_author_view($author,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_author_view.tpl.php');
	return $template;
}

/**
* Get pmb_publisher_view template
* @param publisher publisher array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_publisher_view($publisher,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_publisher_view.tpl.php');
	return $template;
}

/**
* Get pmb_collection_view template
* @param collection collection array;
* @param parent_publisher publisher array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_collection_view($collection,$parent_publisher,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_collection_view.tpl.php');
	return $template;
}

/**
* Get pmb_subcollection_view template
* @param subcollection subcollection array;
* @param parent_collection parent_collection array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_subcollection_view($subcollection,$parent_collection,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_subcollection_view.tpl.php');
	return $template;
}

/**
* Get pmb_browse_locations template
* @param locations_and_sections locations_and_sections array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_locations($locations_and_sections, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_locations.tpl.php');
	return $template;
}

/**
* Get pmb_browse_shelves template
* @param shelves shelves array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_shelves($shelves, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_shelves.tpl.php');
	return $template;
}

/**
* Get pmb_browse_thesauri template
* @param thesauri thesauri array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_thesauri($thesauri, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_thesauri.tpl.php');
	return $template;
}

/**
* Get pmb_browse_category template
* @param category category array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_category($category, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_category.tpl.php');
	return $template;
}

/**
* Get pmb_browse_serials template
* @param serials serials array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_serials($serials, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_serials.tpl.php');
	return $template;
}

/**
* Get pmb_browse_location template
* @param location location array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_location($location, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_location.tpl.php');
	return $template;
}

/**
* Get pmb_browse_section template
* @param location location array;
* @param section section array;
* @param notices notices array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_section($location,$section,$notices, $parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_section.tpl.php');
	return $template;
}

/**
* Get pmb_browse_shelf template
* @param shelf shelf array;
* @param notices notices array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_browse_shelf($shelf,$notices,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_browse_shelf.tpl.php');
	return $template;
}

/**
* Get pmb_shelf_block template
* @param shelf shelf array;
* @param notices notices array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_shelf_block($shelf,$notices,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_shelf_block.tpl.php');
	return $template;
}

/**
* Get pmb_search_form template
* @return html template
*/
function theme_pmb_search_form(){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_search_form.tpl.php');
	return $template;
}

/**
* Get pmb_search_results template
* @param search_terms search_terms array;
* @param search_fields search_fields array;
* @param notices notices array;
* @param parameters parameters array;
* @return html template
*/
function theme_pmb_search_results($search_terms,$search_fields,$notices,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_search_results.tpl.php');
	return $template;
}

/**
* Get pmb_external_search_results template
* @param search_terms search_terms array;
* @param search_sources search_sources array;
* @param search_fields search_fields array;
* @param notices notices array;
* @param parameters parameters array;
* @return html template
*/
function theme_pmb_external_search_results($search_terms,$search_sources, $search_fields,$notices,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_external_search_results.tpl.php');
	return $template;
}

/**
* Get pmb_external_search_form template
* @param search_sources search_sources array;
* @return html template
*/
function theme_pmb_external_search_form($search_sources){
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_external_search_form.tpl.php');
	return $template;
}

/**
* Get pmb_search_form template
* @return html template
*/
//function theme_pmb_advanced_search_form(){
//	$template = "";
//	include(drupal_get_path('module', 'pmb').'/templates/pmb_advanced_search_form.tpl.php');
//	return $template;
//}


function theme_pmb_block_pager($current_page,$page_count,$tags,$id,$link_generator_callback){
	
	$template = "";
	include(drupal_get_path('module', 'pmb').'/templates/pmb_block_pager.tpl.php');
	return $template;
}




