<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_author_view.tpl.php,v 1.8 2011-10-21 20:32:25 gueluneau Exp $

	$author_id = $author->information->author_id;
	$author_author = $author->information;
		
	$template.= '<br />';
	$template.= '<div id="author_'.$author_id.'">';

	$template.= '<h2>'.t('Information').'</h2>';
	$header = array();
	$template.= '<div style="float: left;" id="author_'.$author_id.'_table">';

	if (check_plain($author_author->author_name.($author_author->author_rejete ? ', '.$author_author->author_rejete : '')))
		$rows[] = array(t('Name'), check_plain($author_author->author_name.($author_author->author_rejete ? ', '.$author_author->author_rejete : '')));
	
	if (check_plain($author_author->author_date))
		$rows[] = array(t('Date'), $author_author->author_date);
	if (check_plain($author_author->author_web))
		$rows[] = array(t('Web'), $author_author->author_web);
	if (check_plain($author_author->author_lieu))
		$rows[] = array(t('Location'), $author_author->author_lieu.' '.$author_author->author_ville);	
	if (check_plain($author_author->author_comment))
		$rows[] = array(t('Comment'), $author_author->author_comment);	

	$template.= theme('table', $header, $rows);
		
	$template.= '</div>';

	$template.= '<br style="clear: both"/>';
	$template.= '<h2>'.t('Records').'</h2>';
	$template.= '<div style="float: left;" id="author_'.$author_id.'_notices">';
	if (isset($parameters['notices'])) {
		$header = array('');
		$rows = array();
		foreach($parameters['notices'] as $anotice) {
			$rows[] = array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
		}
		$template.= theme('table', $header, $rows);		
	}
	else {
		foreach($author->notice_ids as $anotice) {
			$anotice += 0;
			$template.= l($anotice, 'pmb/view_notice/'.$anotice.'/').'<br />';
		}		
	}
	
	$link_maker_function = create_function('$page_number', 'return "pmb/view_author/'.$author_id.'/".$page_number;');
	

	$template.= theme('pmb_pager', $parameters['page_number'], ceil(count($author->notice_ids) / $parameters['notices_per_pages']), array(), 7, $link_maker_function);  
	
	$template.= '</div>';
	
	$template.= '<br style="clear: both"/>';
	$template.= '<div>';
	$template.= '<h2>'.t('Linked entities').'</h2>';
	$header = array('');
	$rows = array();
	foreach($author->information->author_links as $alink) {
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