<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_serials.tpl.php,v 1.4 2011-10-21 20:32:25 gueluneau Exp $

$categories = array();
foreach($serials as $aserial) {
	if (!$aserial->serial_title) {
		$categories['?'][] = $aserial;
		continue;
	}
	$char = ord(strtoupper(substr($aserial->serial_title, 0, 1)));
	if ($char >= ord('0') && $char <= ord('9'))
		$categories['#'][] = $aserial;
	else if ($char >= ord('A') && $char <= ord('Z'))
		$categories[chr($char)][] = $aserial;
	else
		$categories['?'][] = $aserial;
}

$links = '';
if ($categories['?'])
	$links .= '<a href="#p'.ord('?').'">?</a>&nbsp;';
else
	$links .= '?&nbsp;';
if ($categories['#'])
	$links .= '<a href="#p'.ord('#').'">#</a>&nbsp;';
else
	$links .= '#&nbsp;';
for($i=ord('A'); $i<=ord('Z'); $i++) {
	if ($categories[chr($i)])
		$links .= '<a href="#p'.($i).'">'.check_plain(chr($i)).'</a>&nbsp;';
	else
		$links .= check_plain(chr($i)).'&nbsp;';
}

$template.= $links;

$header = array(t('Title'), t('Number of issue'), t('Number of items'), t('Number of analysis'));
$rows = array();
foreach($categories as $caption => $category) {
	$count=0;
	foreach($category as $aserial) {
		$count++;
		$anchor = $count ? '<a name="p'.ord($caption).'"/>' : '';
		$rows[] = array($anchor.l($aserial->serial_title, 'pmb/view_serial/'.$aserial->serial_id), $aserial->serial_issues_count, $aserial->serial_items_count, $aserial->serial_analysis_count);
	}
	$rows[] = array('data' => array('&nbsp;', '&nbsp;', '&nbsp;', '&nbsp;'));
}
$template.= theme('table', $header, $rows);

