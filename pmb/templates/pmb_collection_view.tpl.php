<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_collection_view.tpl.php,v 1.8 2011-10-21 20:32:25 gueluneau Exp $

	$collection_id = $collection->information->collection_id;
	$collection_collection = $collection->information;

	$template.= '<br />';
	$template.= '<div id="collection_'.$collection_id.'">';

	$template.= '<h2>'.t('Information').'</h2>';
	$template.= '<div style="float: left;" id="collection_'.$collection_id.'_table">';
	$header = array();

	$rows[] = array(t('Name'), $collection_collection->collection_name);
	if ($parent_publisher) {
		$rows[] = array(t('Publisher'), l($parent_publisher->information->publisher_name, 'pmb/view_publisher/'.$parent_publisher->information->publisher_id));
	}
	if ($collection_collection->collection_issn) {
		$rows[] = array(t('ISSN'), $collection_collection->collection_issn);
	}
	if ($collection_collection->collection_web) {
		$rows[] = array(t('Web'), $collection_collection->collection_web);
	}

	$template.= theme('table', $header, $rows);		
	$template.= '</div>';

	$template.= '<br style="clear: both"/>';
	$template.= '<h2>'.t('Records').'</h2>';
	$template.= '<div style="float: left;" id="collection_'.$collection_id.'_notices">';
	if (isset($parameters['notices'])) {
		$header = array('');
		$rows = array();
		foreach($parameters['notices'] as $anotice) {
			$rows[] = array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
		}
		$template.= theme('table', $header, $rows);		
	}
	else {
		foreach($collection->notice_ids as $anotice) {
			$anotice += 0;
			$template.= l($anotice, 'pmb/view_notice/'.$anotice.'/').'<br />';
		}		
	}
	
	$link_maker_function = create_function('$page_number', 'return "pmb/view_collection/'.$collection_id.'/".$page_number;');
	

	$template.= theme('pmb_pager', $parameters['page_number'], ceil(count($collection->notice_ids) / $parameters['notices_per_pages']), array(), 7, $link_maker_function);  
	
	$template.= '</div>';
	
	$template.= '<br style="clear: both"/>';
	$template.= '<div>';
	$template.= '<h2>'.t('Linked entities').'</h2>';
	$header = array('');
	$rows = array();
	foreach($collection->information->collection_links as $alink) {
		$link = "";
		switch($alink->autlink_to) {
			case 1: 
				$link = "pmb/view_author/".$alink->autlink_to_id;
				break;
			case 2: 
				$link = "pmb/browse_category/".$alink->autlink_to_id;
				break;
			case 3: 
				$link = "pmb/view_publisher/".$alink->autlink_to_id;
				break;
			case 4: 
				$link = "pmb/view_collection/".$alink->autlink_to_id;
				break;
			case 5: 
				$link = "pmb/view_subcollection/".$alink->autlink_to_id;
				break;
			default:
				break;
		}
		$rows[] = array(l($alink->autlink_to_libelle, $link));
	}
	$template.= theme('table', $header, $rows);		
	
	$template.= '</div>';
	
	$template.= '</div>';
?>