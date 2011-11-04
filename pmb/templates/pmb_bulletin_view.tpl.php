<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_bulletin_view.tpl.php,v 1.7 2011-10-21 20:32:24 gueluneau Exp $

	$notice_notice = $bulletin['notice'];
	if (!$notice_notice)
		$notice_notice = array();

	$bulletin_id = $bulletin['id'];
	$template.= '<div id="notice_'.$bulletin_id.'">';
		
	$cover_url = '';

	if (isset($notice_notice['f']['896'][0]['a'])) {
		$cover_url = $notice_notice['f']['896'][0]['a'];
	}

	if ($cover_url) {
		$template.= '<div id="notice_'.$bulletin_id.'_cover" style="float: left; padding-right: 20px; padding-top: 20px">';
		$template.= '<img src="'.check_plain($cover_url).'" style="max-width: 130px;">';
		$template.= '</div>';
	}
	
	$template.= '<h2>'.t('Information').'</h2>';
	$template.= '<div style="float: left;" id="notice_'.$bulletin_id.'_table">';
	$template.= '<table>';
	$template.= '	<tbody>';
	

	$template.= '<tr><td>'.t('Title').'</td><td>'.check_plain($bulletin['bulletin']->bulletin_title).'</td></tr>';
	$template.= '<tr><td>'.t('Number').'</td><td>'.check_plain($bulletin['bulletin']->bulletin_numero).'</td></tr>';
	$template.= '<tr><td>'.t('Period').'</td><td>'.check_plain($bulletin['bulletin']->bulletin_date_caption).'</td></tr>';
	
	$caption = '';
	if (isset($serial['notice']['f']['200'])) {
		foreach($serial['notice']['f']['200'] as &$afield) {
			if (!isset($afield['a']))
				continue;
			$caption .= $afield['a'].' ';
		}
	}
	$caption = trim($caption);
	if (!$caption)
		$caption = t('Unknown title');
		
	$template.= '<tr><td>'.t('Serial').'</td><td>'.l($caption, 'pmb/view_serial/'.$serial['id']).'</td></tr>';
	
	if (isset($notice_notice['f']['700'])) {
		foreach($notice_notice['f']['700'] as &$afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			$template.= '<tr><td>'.t('Author').'</td><td>'.l($display, 'pmb/view_author/'.$afield['id']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['701'])) {
		foreach($notice_notice['f']['701'] as $afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			$template.= '<tr><td>'.t('Author').'</td><td>'.l($display, 'pmb/view_author/'.$afield['id']).'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['702'])) {
		foreach($notice_notice['f']['702'] as &$afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			$template.= '<tr><td>'.t('Author').'</td><td>'.l($display, 'pmb/view_author/'.$afield['id']).'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['210'])) {
		foreach($notice_notice['f']['210'] as &$afield) {
			$display = '';
			$display .= isset($afield['c']) ? $afield['c'].' ' : '';
			$template.= '<tr><td>'.t('Publisher').'</td><td>'.l($display, 'pmb/view_publisher/'.$afield['id']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['410'])) {
		foreach($notice_notice['f']['410'] as &$afield) {
			$display = '';
			$display .= isset($afield['t']) ? $afield['t'].' ' : '';
			$template.= '<tr><td>'.t('Collection').'</td><td>'.l($display, 'pmb/view_collection/'.$afield['id']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['411'])) {
		foreach($notice_notice['f']['411'] as &$afield) {
			$display = '';
			$display .= isset($afield['t']) ? $afield['t'].' ' : '';
			$template.= '<tr><td>'.t('Sub-collection').'</td><td>'.l($display, 'pmb/view_subcollection/'.$afield['id']).'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['215'])) {
		foreach($notice_notice['f']['215'] as &$afield) {
			$display = '';
			$display .= isset($afield['d']) ? $afield['d'].' ' : '';
			$template.= '<tr><td>'.t('Format').'</td><td>'.check_plain($display).'</td></tr>';
			
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$template.= '<tr><td>'.t('Importance').'</td><td>'.check_plain($display).'</td></tr>';
		}
	}
	
	$template.= '	</tbody>';
	$template.= '</table>';
	$template.= '</div>';

	$template.= '<br style="clear: both;"/>';
	$template.= '<h2>'.t('Description').'</h2>';
	$template.= '<div id="notice_'.$bulletin_id.'_desc">';
	if(isset($notice_notice['f']['330'][0]['a'])) {
		$template.= check_plain($notice_notice['f']['330'][0]['a']);
	}
	$template.= '</div>';
	
	$notice_items = $bulletin['items'];
	if (!$notice_items)
		$notice_items = array();
	
	if(!$parameters['no_items']) {		
		$template.= '<br style="clear: both;"/>';
		$template.= '<h2>'.t('Items').'</h2>';
		$template.= '<div id="notice_'.$bulletin_id.'_items">';
		$template.= '<table>';
		$template.= '<thead><tr><th>'.t('Barcode').'</th><th>'.t('Cote').'</th><th>'.t('Media type').'</th><th>'.t('Location').'</th><th>'.t('Section').'</th><th>'.t('Availability').'</th></tr></thead>';
		$template.= '<tbody>';
		
		foreach ($notice_items as &$aitem_o) {
			$aitem = (array)$aitem_o;
			$template.= '<tr><td>'.check_plain($aitem['cb']).'</td><td>'.check_plain($aitem['cote']).'</td><td>'.check_plain($aitem['support']).'</td><td>'.check_plain($aitem['location_caption']).'</td><td>'.check_plain($aitem['section_caption']).'</td><td>'.check_plain($aitem['statut']).'</td></tr>';
		}
		
		$template.= '</tbody></table>';
		$template.= '</div>';
	
		if($parameters['can_reserve']) {
			$template.= '<h3>'.t('Holding').'</h3>';		
			$template.= l(t('Hold this document'), 'pmb_reader/'.$GLOBALS["user"]->uid.'/add_reservation/b'.$bulletin_id);
		}
	}
	
	$template.= '<br />';
	
	$notice_explnums = $bulletin['expl_nums'];
	if (!$notice_explnums)
		$notice_explnums = array();
	
	$template.= '<br style="clear: both;"/>';
	$template.= '<h2>'.t('Digital items').'</h2>';
	$template.= '<div id="notice_'.$bulletin_id.'_explnums">';
	$template.= '<table>';
	$template.= '<thead><tr><th>'.t('Download URL').'</th><th>'.t('Name').'</th></thead>';
	$template.= '<tbody>';
	
	foreach ($notice_explnums as &$aexplnum_o) {
		$aexplnum = (array)$aexplnum_o;
		$template.= '<tr><td>'.check_plain($aexplnum['downloadUrl']).'</td><td>'.check_plain($aexplnum['name']).'</td></tr>';
	}
	
	$template.= '</tbody></table>';
	$template.= '</div>';	

	$template.= '<br style="clear: both;"/>';
	$template.= '<h2>'.t('Analysis').'</h2>';
	$template.= '<div id="analysis_'.$bulletin_id.'_explnums">';
	$template.= '<table>';
	$template.= '<thead><tr><th>'.t('Title').'</th></thead>';
	$template.= '<tbody>';
	
	foreach ($parameters['analysis'] as &$anotice) {

		$caption = '';
		if (isset($anotice['notice']['f']['200'])) {
			foreach($anotice['notice']['f']['200'] as &$afield) {
				if (!isset($afield['a']))
					continue;
				$caption .= $afield['a'].' ';
			}
		}
		$caption = trim($caption);
		if (!$caption)
			$caption = t('Unknown title');
		
		$template.= '<tr><td>'.l($caption, 'pmb/view_notice/'.$anotice['id']).'</td></tr>';
	}
	
	$template.= '</tbody></table>';
	$template.= '</div>';
	
	$template.= '</div>';
?>