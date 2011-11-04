<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_category.tpl.php,v 1.7 2011-10-21 20:32:25 gueluneau Exp $

	$template.= '<h2>'.t('Subcategories').'</h2>';
	if ($category->node->node_children) {
		$header = array();
		$rows = array();
		$chosen_language = 'fr_FR';
		foreach($category->node->node_children as $child) {
			if (!$child->node_id)
				continue;
			$caption = '';
			foreach($child->categories as $acategory) {
				if ($acategory->category_lang == $chosen_language) {
					$caption =$acategory->category_caption;
					break;
				}
			}
			if (!$caption) {
				$caption = count($child->categories) ? $child->categories[0]->category_caption : t('Unknown caption');
				if (!$caption) {
					$caption = t('Unknown caption');
				}
			}
			if ($child->is_link)
				$rows[] = array('<i>'.l($caption, 'pmb/browse_category/'.$child->node_id).'</i>');
			else
				$rows[] = array(l($caption, 'pmb/browse_category/'.$child->node_id));
		}
		$template.= theme('table', $header, $rows);
	}
	else {
		$template.= t('This categories has no subcategories');
	}
	
	if ($category->node->node_seealso) {
		$template.= '<br /><br />';
		$template.= '<h2>'.t('See also').'</h2>';
		$header = array(t('Caption'));
		$rows = array();
		$chosen_language = 'fr_FR';
		foreach($category->node->node_seealso as $child) {
			if (!$child->node_id)
				continue;
			$caption = '';
			foreach($child->categories as $acategory) {
				if ($acategory->category_lang == $chosen_language) {
					$caption =$acategory->category_caption;
					break;
				}
			}
			if (!$caption) {
				$caption = count($child->categories) ? $child->node_seealso[0]->category_caption : t('Unknown caption');
				if (!$caption) {
					$caption = t('Unknown caption');
				}
			}
			$rows[] = array(l($caption, 'pmb/browse_category/'.$child->node_id));
		}
		$template.= theme('table', $header, $rows);
	}
	
	$template.= '<br style="clear: both"/>';
	$template.= '<h2>'.t('Records').'</h2>';
	if ($parameters['notices']) {
		$template.= '<div style="float: left;" id="category_'.$category->node->node_id.'_notices">';
		if (isset($parameters['notices'])) {
			$header = array('');
			$rows = array();
			foreach($parameters['notices'] as $anotice) {
				$rows[] = array(theme('pmb_notice_display', $anotice, 'medium_line', array()));
			}
			$template.= theme('table', $header, $rows);		
		}
		else {
			foreach($category->notice_ids as $anotice) {
				$anotice += 0;
				$template.= l($anotice, 'pmb/view_notice/'.$anotice.'/').'<br />';
			}		
		}
		
		$link_maker_function = create_function('$page_number', 'return "pmb/browse_category/'.$category->node->node_id.'/".$page_number;');
		$template.= theme('pmb_pager', $parameters['page_number'], ceil(count($category->notice_ids) / $parameters['notices_per_pages']), array(), 7, $link_maker_function);  
		
		$template.= '</div>';
	}
	else {
		$template.= t('This category has no records');
	}

?>