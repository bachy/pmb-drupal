<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_cart_form.tpl.php,v 1.5 2011-10-21 20:32:25 gueluneau Exp $

$rows = array();
$header = array();

$count = 0;
foreach($form['notices']['notice_ids'] as $anotice_id => $nothing) {
	if (is_numeric($anotice_id)) {
		$rows[] =  array(array('data' => drupal_render($form['checked_notices'][$anotice_id]), 'class' => 'checkbox'), theme('pmb_notice_display', $form['#parameters'][2][$anotice_id], 'medium_line', array()));
		$count++;
	}
}
if ($count) {
	$template.= theme('table', $header, $rows);
	$template.= drupal_render($form['delete_selected']);
	$template.= '&nbsp;';
	$template.= drupal_render($form['empty_cart']);
	
	$template.= drupal_render($form);	
}
else {
	$templates.= (t('Your cart is empty').'<br /><br />');
}

