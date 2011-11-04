<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_reading_list.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

//$header = array(t('Name'), t('Description'), t('Public'), t('Subscribers only'), t('Read only'));
//
//$rows = array();
//$rows[] = array(
//	$reading_list->reading_list_name,
//	$reading_list->reading_list_caption,
//	$reading_list->reading_list_public ? t("Yes") : t("No"),
//	$reading_list->reading_list_confidential ? t("Yes") : t("No"),
//	$reading_list->reading_list_readonly ? t("Yes") : t("No"),
//);	
//
//$template.= theme('table', $header, $rows);
//
//$rows = array();
//$header = array('');
//foreach($notices as $anotice) {
//		$rows[] =  array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
//}
//$template.= theme('table', $header, $rows);
//
//$template.= drupal_get_form('pmb_reader_add_cart_to_reading_list_form', $reading_list->reading_list_id);