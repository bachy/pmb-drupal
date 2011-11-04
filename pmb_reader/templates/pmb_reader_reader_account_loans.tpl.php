<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_account_loans.tpl.php,v 1.6 2011-10-21 20:32:25 gueluneau Exp $

$header = array(t('Title'), t('Bar code'), t('Media type'), t('Location'), t('Section'), t('Loan start date'), t('Loan return date'));

$rows = array();
foreach($loans as $aloan) {
	$notice_link = $aloan->notice_id ? l($aloan->expl_libelle, 'pmb/view_notice/'.$aloan->notice_id) : $aloan->expl_libelle;
	//on regarde si le pret est en retard...
	if($key == 'late'){
		$return_date ="<span style='color:red;'>".$aloan->loan_returndate."<br>";
	}else {
		$return_date =$aloan->loan_returndate;
	}
	$rows[] = array(
		$notice_link,
		$aloan->expl_cb, 
		$aloan->expl_support,
		l($aloan->expl_location_caption, 'pmb/browse_location/'.$aloan->expl_location_id),
		l($aloan->expl_section_caption, 'pmb/browse_section/'.$aloan->expl_section_id),
		$aloan->loan_startdate,
		$aloan->loan_returndate,
	);
}

$template.= theme('table', $header, $rows);
