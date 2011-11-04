<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_thesauri.inc,v 1.3 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

function pmb_browse_thesauri() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$thesauri = $pmb_data->get_thesauri();

	if (count($thesauri) == 1) {
		drupal_goto('pmb/browse_category/'.$thesauri[0]->thesaurus_num_root_node);
	}
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog - Thesauri'), 'pmb/browse_catalog/thesauri');
    drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_thesauri', $thesauri, array());
}

function pmb_browse_category($category_id, $page=1) {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$category = $pmb_data->get_category($category_id);

	if(!isset($category)) {
		drupal_set_title(t('Category not found!'));
		drupal_set_message(t('Category not found!'), 'error');		
		return '';
	}

	if ($category->node->node_target_id) {
		drupal_goto('pmb/browse_category/'.$category->node->node_target_id);
	}
	
	$is_thesaurus = FALSE;
	$thesauri = $pmb_data->get_thesauri();
	$the_thesaurus = NULL;
	foreach($thesauri as $athesaurus) {
		if ($athesaurus->thesaurus_id == $category->node->node_thesaurus) {
			$the_thesaurus = $athesaurus;
		}
	}
	$is_thesaurus = $the_thesaurus->thesaurus_num_root_node == $category->node->node_id;
	if ($is_thesaurus) {
		$caption = $the_thesaurus->thesaurus_caption;
		drupal_set_title(t('Thesaurus').': '.$caption);		
	}
	else {
		$chosen_language = 'fr_FR';
		$caption = '';
		foreach($category->node->node_categories as $acategory) {
			if ($acategory->category_lang == $chosen_language) {
				$caption = $acategory->category_caption;
				break;
			}
		}
		if (!$caption) {
			$caption = count($category->node->node_categories) ? $category->node->node_categories[0]->category_caption : t('Unknown caption');
			if (!$caption) {
				$caption = t('Unknown caption');
			}
		}
		drupal_set_title(t('Category').': '.$caption);
	}
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog - Thesauri'), 'pmb/browse_catalog/thesauri');
    if ($the_thesaurus)
    	$breadcrumb[] = l(t('Thesaurus').': '.$the_thesaurus->thesaurus_caption, 'pmb/browse_category/'.$the_thesaurus->thesaurus_num_root_node);
    if (!$is_thesaurus) {
	    foreach($category->node->node_path as $apath) {
			$caption = '';
			foreach($apath->categories as $acategory) {
				if ($acategory->category_lang == $chosen_language) {
					$caption = $acategory->category_caption;
					break;
				}
			}
			if (!$caption) {
				$caption = count($apath->categories) ? $apath->categories[0]->category_caption : t('Unknown caption');
				if (!$caption) {
					$caption = t('Unknown caption');
				}
			}    	
	    	
	    	$breadcrumb[] = l($caption, 'pmb/browse_category/'.$apath->node_id);	
	    }
    }
    drupal_set_breadcrumb($breadcrumb);

	$page += 0;
	$notice_count = variable_get('pmb_noticeperpage_categories', 5);
	$notices_pages = array_chunk($category->notice_ids, $notice_count);
	$page = min($page, count($notices_pages));
	$page = max(1, $page);
	$notices = $pmb_data->get_notices($notices_pages[$page-1]);
	return theme('pmb_browse_category', $category, array('notices' => $notices, 'page_number' => $page, 'notices_per_pages' => $notice_count));
}

