<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_templates.tpl.php,v 1.3 2011-10-21 20:32:23 gueluneau Exp $

/**
* Get pmb_reader_reader_account_summary template
* @param reader reader array;
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_account_summary($reader,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_account_summary.tpl.php');
	return $template;
}

/**
* Get pmb_reader_reader_account_loans template
* @param reader reader array;
* @param loans loans array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_account_loans($reader,$loans,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_account_loans.tpl.php');
	return $template;
}

/**
* Get pmb_reader_reader_account_reservations template
* @param reader reader array;
* @param suggestions suggestions array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_account_suggestions($reader,$suggestions,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_account_suggestions.tpl.php');
	return $template;
}

/**
* Get pmb_reader_reader_account_reservations template
* @param reader reader array;
* @param reservations reservations array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_account_reservations($reader,$reservations,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_account_reservations.tpl.php');
	return $template;
}

/**
* Get pmb_reader_reader_reading_lists template
* @param reader reader array;
* @param reading_lists reading_lists array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_reading_lists($reader,$reading_lists,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_reading_lists.tpl.php');
	return $template;
}

//TODO Useless? 
/**
* Get pmb_reader_reader_reading_lists template
* @param reader reader array;
* @param reading_lists reading_lists array
* @param notices notices array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_reading_list($reader,$reading_list,$notices,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_reading_list.tpl.php');
	return $template;
}

/**
* Get pmb_reader_reader_public_reading_lists template
* @param reader reader array;
* @param reading_lists reading_lists array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_public_reading_lists($reader,$reading_lists,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_public_reading_lists.tpl.php');
	return $template;
}

/**
* Get pmb_reader_reader_public_reading_list template
* @param reader reader array;
* @param reading_lists reading_lists array
* @param notices notices array
* @param parameters optional parameters array
* @return html template
*/
function theme_pmb_reader_reader_public_reading_list($reader,$reading_list,$notices,$parameters=array()){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reader_public_reading_list.tpl.php');
	return $template;
}

/**
* Get pmb_reader_cart_form template
* @param form form array;
* @return html template
*/
function theme_pmb_reader_cart_form($form){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_cart_form.tpl.php');
	return $template;
}

/**
* Get pmb_reader_cart_form template
* @param form form array;
* @return html template
*/
function theme_pmb_reader_reading_list_form($form){
	$template = "";
	include(drupal_get_path('module', 'pmb_reader').'/templates/pmb_reader_reading_list_form.tpl.php');
	return $template;
}
