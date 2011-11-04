<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reading_list_form.tpl.php,v 1.5 2011-10-21 20:32:25 gueluneau Exp $

$reading_list = $form['#reading_list']; 

$header = array(t('Name'), t('Description'), t('Public'), t('Subscribers only'), t('Read only'));

$rows = array();
$rows[] = array(
	$reading_list->reading_list_name,
	$reading_list->reading_list_caption,
	$reading_list->reading_list_public ? t("Yes") : t("No"),
	$reading_list->reading_list_confidential ? t("Yes") : t("No"),
	$reading_list->reading_list_readonly ? t("Yes") : t("No"),
);	

$template.= theme('table', $header, $rows);

$rows = array();
$header = array();

$count = 0;
foreach($form['#notices']['notice_ids'] as $anotice_id => $nothing) {
	if (is_numeric($anotice_id) && $anotice_id) {
		$rows[] =  array(array('data' => drupal_render($form['checked_notices'][$anotice_id]), 'class' => 'checkbox'), theme('pmb_notice_display', $form['#notices']['notices'][$anotice_id], 'medium_line', array()));
		$count++;
	}
}
if ($count) {
	$template.= theme('table', $header, $rows);
}
else {
	$template.= (t('This list is empty').'<br /><br />');
}

$template.= drupal_render($form);

#$template.= drupal_get_form('pmb_reader_add_cart_to_reading_list_form', $reading_list->reading_list_id);