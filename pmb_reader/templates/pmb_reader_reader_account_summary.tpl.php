<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_reader_reader_account_summary.tpl.php,v 1.6 2011-10-21 20:32:25 gueluneau Exp $

$header = array();

$rows = array();

$rows[] = array(
	t('Last Name'), $reader->pmb_reader_info->personal_information->lastname
);
$rows[] = array(
	t('First Name'), $reader->pmb_reader_info->personal_information->firstname
);
$rows[] = array(
	t('Bar Code'), $reader->pmb_reader_info->cb
);
$rows[] = array(
	t('Join date'), $reader->pmb_reader_info->adhesion_date
);
$rows[] = array(
	t('Expiration date'), $reader->pmb_reader_info->expiration_date
);

$template.= theme('table', $header, $rows);