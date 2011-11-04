<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_pager.tpl.php,v 1.6 2011-10-22 08:23:15 arenou Exp $

$values = array();
for ($i = max(1, $current_page - ceil($quantity / 2)); $i<=min($current_page + ceil($quantity / 2), $page_count); $i++) {
	$values[] = $i;
}

$items = array();

if ($current_page != 1) {
	$items[] = array(
		'class' => 'pager-first',
		'data' => l(t('<< first'), $link_generator_callback(1)),
	);	
}

if ($current_page > 2) {
	$items[] = array(
		'class' => 'pager-previous',
		'data' => l(t('< previous'), $link_generator_callback($current_page-1)),
	);
}
foreach($values as $avalue) {
	$items[] = array(
		'class' => 'pager-item',
		'data' => l($avalue, $link_generator_callback($avalue)),
	);
}
if ($current_page != $page_count) {
	$items[] = array(
		'class' => 'pager-next',
		'data' => l(t('next >'), $link_generator_callback($current_page+1)),
	);
}

if ($current_page < $page_count - 1) {
	$items[] = array(
		'class' => 'pager-last',
		'data' => l(t('last').' ('.$page_count.') >>', $link_generator_callback($page_count)),
	);
}

$template .= theme('item_list', $items, NULL, 'ul', array('class' => 'pager'));