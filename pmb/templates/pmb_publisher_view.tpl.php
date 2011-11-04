<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_publisher_view.tpl.php,v 1.8 2011-10-21 20:32:25 gueluneau Exp $

	$publisher_id = $publisher->information->publisher_id;
	$publisher_publisher = $publisher->information;
		
	$template.= '<br />';
	$template.= '<div id="publisher_'.$publisher_id.'">';

	$template.= '<h2>'.t('Information').'</h2>';
	$template.= '<div style="float: left;" id="publisher_'.$publisher_id.'_table">';

	$header = array();
	if ($publisher_publisher->publisher_name)
		$rows[] = array(t('Name'), $publisher_publisher->publisher_name);
	if ($publisher_publisher->publisher_address1)
		$rows[] = array(t('Address'), $publisher_publisher->publisher_address1);
	if ($publisher_publisher->publisher_address2)
		$rows[] = array(t('Address'), $publisher_publisher->publisher_address2);
	if ($publisher_publisher->publisher_zipcode)
		$rows[] = array(t('Zipcode'), $publisher_publisher->publisher_zipcode);
	if ($publisher_publisher->publisher_city)
		$rows[] = array(t('City'), $publisher_publisher->publisher_city);
	if ($publisher_publisher->publisher_country)
		$rows[] = array(t('Country'), $publisher_publisher->publisher_country);
	if ($publisher_publisher->publisher_web)
		$rows[] = array(t('Web'), $publisher_publisher->publisher_web);
	if ($publisher_publisher->publisher_comment)
		$rows[] = array(t('Comment'), $publisher_publisher->publisher_comment);

	$template.= theme('table', $header, $rows);	
	$template.= '</div>';

	$template.= '<br style="clear: both"/>';
	$template.= '<h2>'.t('Records').'</h2>';
	$template.= '<div style="float: left;" id="publisher_'.$publisher_id.'_notices">';
	if (isset($parameters['notices'])) {
		$header = array('');
		$rows = array();
		foreach($parameters['notices'] as $anotice) {
			$rows[] = array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
		}
		$template.= theme('table', $header, $rows);		
	}
	else {
		foreach($publisher->notice_ids as $anotice) {
			$anotice += 0;
			$template.= l($anotice, 'pmb/view_notice/'.$anotice.'/').'<br />';
		}		
	}
	
	$link_maker_function = create_function('$page_number', 'return "pmb/view_publisher/'.$publisher_id.'/".$page_number;');
	

	$template.= theme('pmb_pager', $parameters['page_number'], ceil(count($publisher->notice_ids) / $parameters['notices_per_pages']), array(), 7, $link_maker_function);  
	
	$template.= '</div>';
	
	$template.= '<br style="clear: both"/>';
	$template.= '<div>';
	$template.= '<h2>'.t('Linked entities').'</h2>';
	$header = array('');
	$rows = array();
	foreach($publisher->information->publisher_links as $alink) {
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