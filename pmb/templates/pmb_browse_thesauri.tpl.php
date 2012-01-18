<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_thesauri.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$header = array(
	t('Thesaurus'),
);

$rows = array();
foreach($thesauri as $thesaurus) {
	$rows[] = array(l($thesaurus->thesaurus_caption, 'pmb/browse/thesauri/'.$thesaurus->thesaurus_num_root_node));
}

$template.= theme('table', $header, $rows);
