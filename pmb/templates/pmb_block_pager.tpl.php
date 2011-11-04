<?php 
$items = array();
if ($current_page > 1) {
	$items[] = array(
		'class' => 'pager-previous',
		'data' => l(t('< previous'), $link_generator_callback($current_page-1)),
		'onclick' => "pmb_block_get_page('".$id."','".$link_generator_callback($current_page-1)."');return false;"

	);
}
$items[] = array(
	'class' => 'pager-item',
	'data' => $current_page,
);

if ($current_page != $page_count) {
	$items[] = array(
		'class' => 'pager-next',
		'data' => l(t('next >'), $link_generator_callback($current_page+1)),
		'onclick' => "pmb_block_get_page('".$id."','".$link_generator_callback($current_page+1)."');return false;"
	);
}

$template .= theme('item_list', $items, NULL, 'ul', array('class' => 'pager'));