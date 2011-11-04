<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_external_notice_view.tpl.php,v 1.4 2011-10-21 20:32:24 gueluneau Exp $

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
				$template.= '<tr><td>'.t('Author').'</td><td>'.$display.'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['701'])) {
		foreach($notice_notice['f']['701'] as $afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			if($display)
				$template.= '<tr><td>'.t('Author').'</td><td>'.$display.'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['702'])) {
		foreach($notice_notice['f']['702'] as &$afield) {
			$display = '';
			$display .= isset($afield['a']) ? $afield['a'].' ' : '';
			$display .= isset($afield['b']) ? $afield['b'].' ' : '';
			$display = trim($display);
			if($display)			
				$template.= '<tr><td>'.t('Author').'</td><td>'.$display.'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['210'])) {
		foreach($notice_notice['f']['210'] as &$afield) {
			$display = '';
			$display .= isset($afield['c']) ? $afield['c'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Publisher').'</td><td>'.$display.'</td></tr>';
		}
	}
	
	if (isset($notice_notice['f']['410'])) {
		foreach($notice_notice['f']['410'] as &$afield) {
			$display = '';
			$display .= isset($afield['t']) ? $afield['t'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Collection').'</td><td>'.$display.'</td></tr>';
		}
	}

	if (isset($notice_notice['f']['411'])) {
		foreach($notice_notice['f']['411'] as &$afield) {
			$display = '';
			$display .= isset($afield['t']) ? $afield['t'].' ' : '';
			if($display)
				$template.= '<tr><td>'.t('Sub-collection').'</td><td>'.$display.'</td></tr>';
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
	

	$template.= '</div>';
?>