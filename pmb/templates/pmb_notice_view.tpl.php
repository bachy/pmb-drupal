<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_notice_view.tpl.php,v 1.10 2011-10-22 08:08:52 arenou Exp $
	
	$notice_notice = $notice['notice'];
	if (!$notice_notice)
		$notice_notice = array();

	$notice_id = $notice['id'];
	$template.= '<div id="notice_'.$notice_id.'">';
		
	$cover_url = '';

	if (isset($notice_notice['f']['896'][0]['a'])) {
		$cover_url = $notice_notice['f']['896'][0]['a'];
	}

	if ($cover_url) {
		$template.= '<div id="notice_'.$notice_id.'_cover" style="float: left; padding-right: 20px; padding-top: 20px">';
		$template.= '<img src="'.check_plain($cover_url).'" style="max-width: 130px;">';
		$template.= '</div>';
	}
	
	$template.= '<h2>'.t('Information').'</h2>';
	$template.= '<div style="float: left;" id="notice_'.$notice_id.'_table">';
	$template.= '<table>';
	$template.= '	<tbody>';
	
	if (isset($notice_notice['f']['200'])) {
		foreach($notice_notice['f']['200'] as &$afield) {
			if (!isset($afield['a']))
				continue;
			$template.= '<tr><td>'.t('Title').'</td><td>'.check_plain($afield['a']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['700'])) {
		foreach($notice_notice['f']['700'] as &$afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			if($display)
				$template.= '<tr><td>'.t('Author').'</td><td>'.l($display, 'pmb/view_author/'.$afield['id']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['701'])) {
		foreach($notice_notice['f']['701'] as $afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			if($display)
				$template.= '<tr><td>'.t('Author').'</td><td>'.l($display, 'pmb/view_author/'.$afield['id']).'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['702'])) {
		foreach($notice_notice['f']['702'] as &$afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			if($display)			
				$template.= '<tr><td>'.t('Author').'</td><td>'.l($display, 'pmb/view_author/'.$afield['id']).'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['210'])) {
		foreach($notice_notice['f']['210'] as &$afield) {
			$display = '';
			$display .= isset($afield['c']) ? $afield['c'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Publisher').'</td><td>'.l($display, 'pmb/view_publisher/'.$afield['id']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['461'])) {
		foreach($notice_notice['f']['461'] as &$afield) {
			if (is_array($afield[9]) ? in_array('lnk:perio', $afield[9]) : 0) {
				$display = '';
				$display .= isset($afield['t']) ? $afield['t'].' ' : '';
				$display = trim($display);
				if($display)
					$template.= '<tr><td>'.t('Serial').'</td><td>'.l($display, 'pmb/view_serial/'.$afield['id']).'</td></tr>';
			}
		}
	}
	
	if (isset($notice_notice['f']['463'])) {
		foreach($notice_notice['f']['463'] as &$afield) {
			if (is_array($afield[9]) ? in_array('lnk:bull', $afield[9]) : 0) {
				$display = '';
				$display .= isset($afield['e']) ? $afield['e'].' ' : '';
				$display .= isset($afield['t']) ? $afield['t'].' ' : '';
				$display = trim($display);
				if($display)
					$template.= '<tr><td>'.t('Issue').'</td><td>'.l($display, 'pmb/view_bulletin/'.$afield['id']).'</td></tr>';
			}
		}
	}

	if (isset($notice_notice['f']['410'])) {
		foreach($notice_notice['f']['410'] as &$afield) {
			$display = '';
			$display .= isset($afield['t']) ? $afield['t'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Collection').'</td><td>'.l($display, 'pmb/view_collection/'.$afield['id']).'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['411'])) {
		foreach($notice_notice['f']['411'] as &$afield) {
			$display = '';
			$display .= isset($afield['t']) ? $afield['t'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Sub-collection').'</td><td>'.l($display, 'pmb/view_subcollection/'.$afield['id']).'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['215'])) {
		foreach($notice_notice['f']['215'] as &$afield) {
			$display = '';
			$display .= isset($afield['d']) ? $afield['d'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Format').'</td><td>'.check_plain($display).'</td></tr>';
			
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Importance').'</td><td>'.check_plain($display).'</td></tr>';
		}
	}
	
	$template.= '	</tbody>';
	$template.= '</table>';
	$template.= '</div>';

	$template.= '<br style="clear: both;"/>';
	$template.= '<h2>'.t('Description').'</h2>';
	$template.= '<div id="notice_'.$notice_id.'_desc">';
	if(isset($notice_notice['f']['330'][0]['a'])) {
		$template.= check_plain($notice_notice['f']['330'][0]['a']);
	}
	$template.= '</div>';
	$template.= '<br style="clear: both;"/>';
	if(!$parameters['no_items']) {

		$notice_items = $notice['items'];
		if (!$notice_items)
			$notice_items = array();
		if(count($notice_items)){
			$template.= '<br style="clear: both;"/>';
			$template.= '<h2>'.t('Items').'</h2>';
			$template.= '<div id="notice_'.$notice_id.'_items">';
			$template.= '<table>';
			$template.= '<thead><tr><th>'.t('Barcode').'</th><th>'.t('Cote').'</th><th>'.t('Media type').'</th><th>'.t('Location').'</th><th>'.t('Section').'</th><th>'.t('Availability').'</th><th>'.t('Situation').'</th></tr></thead>';
			$template.= '<tbody>';
	
			foreach ($notice_items as &$aitem_o) {
				$aitem = (array)$aitem_o;
				$template.= '<tr><td>'.check_plain($aitem['cb']).'</td><td>'.check_plain($aitem['cote']).'</td><td>'.check_plain($aitem['support']).'</td><td>'.check_plain($aitem['location_caption']).'</td><td>'.check_plain($aitem['section_caption']).'</td><td>'.check_plain($aitem['statut']).'</td><td>'.check_plain($aitem['situation']).'</td></tr>';
			}
	
			$template.= '</tbody></table>';
			$template.= '</div>';
	
			if($parameters['can_reserve']) {
				$template.= '<h3>'.t('Holding').'</h3>';		
				$template.= l(t('Hold this document'), 'pmb_reader/'.$GLOBALS["user"]->uid.'/add_reservation/'.$notice_id);
			}
			$template.= '<br style="clear: both;"/>';
		}
	}

	$template.= '<br />';
	
	$notice_explnums = $notice['expl_nums'];
	if (!$notice_explnums)
		$notice_explnums = array();
	
	if(count($notice_explnums)){
		$template.= '<h2>'.t('Digital items').'</h2>';
		$template.= '<div id="notice_'.$notice_id.'_explnums">';
		//$template.= '<table>';
		//$template.= '<thead><tr><th>'.t('Download URL').'</th><th>'.t('Name').'</th></thead>';
		//$template.= '<tbody>';
		
		$items = array();
		foreach ($notice_explnums as &$aexplnum_o) {
			$aexplnum = (array)$aexplnum_o;
		//	$template.= '<tr><td>'.check_plain($aexplnum['downloadUrl']).'</td><td>'.check_plain($aexplnum['name']).'</td></tr>';
			$items[] = array("<img src='".$aexplnum['vignUrl']."'/>",l($aexplnum['name'],$aexplnum['downloadUrl'],array('attributes' => array('target' => "_blank"))));
		}
		$template.= theme('table', array(),$items);
		//$template.= '</tbody></table>';
		$template.= '</div>';	
		$template.= '<br style="clear: both;"/>';
	}
	if($parameters['can_add_to_cart']) {
		$template.= '<h2>'.t('Add to cart').'</h2>';		
		$template.= drupal_get_form('pmb_reader_add_notice_to_cart_form', $notice_id);
	}	
	
	$template.= '</div>';
?>