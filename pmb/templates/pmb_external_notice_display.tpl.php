<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_external_notice_display.tpl.php,v 1.5 2011-10-21 20:32:25 gueluneau Exp $

	$notice_id = $notice['id'];
	$notice_notice = $notice['notice'];

	switch($display_type) {
		case 'medium_line':
			$source='';
			if (isset($notice_notice['f']['801'])) {
				foreach($notice_notice['f']['801'] as &$afield) {
					$source = $afield['9'];
				}
			}

			$cover_url = '';
		
			if (isset($notice_notice['f']['896'][0]['a'])) {
				$cover_url = $notice_notice['f']['896'][0]['a'];
			}

			if ($cover_url) {
				$template.= '<div id="notice_'.$notice_id.'_cover" style="display:inline-block;">';
				$template.= '<img src="'.check_plain($cover_url).'" style="max-width: 80px;">';
				$template.= '</div>';
			}
		
			$title = '';
			if (isset($notice_notice['f']['200'][0]['a'])) {
				$title = $notice_notice['f']['200'][0]['a'];
			}
			
			$authors = array();
			if (isset($notice_notice['f']['700'])) {
				foreach($notice_notice['f']['700'] as &$afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = $display;
				}
			}
			
			if (isset($notice_notice['f']['701'])) {
				foreach($notice_notice['f']['701'] as $afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = $display;
				}
			}
		
			if (isset($notice_notice['f']['702'])) {
				foreach($notice_notice['f']['702'] as &$afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = $display;
				}
			}			
			
			$publisher = '';
			if (isset($notice_notice['f']['210'])) {
				foreach($notice_notice['f']['210'] as &$afield) {
					$display = '';
					$publisher = $afield['c'];
				}
			}			

    		$link = 'pmb/view_external_notice/'.$notice_id.'/';
			$template.= '<div id="notice_'.$notice_id.'_info" style="display:inline-block;margin-left:5px;vertical-align:top;">';
			if ($source) {
				$template.= t('Source').': '.$source;
				$template.= '<br />';
			}
			if ($title) {
				$template.= t('Title').': '.l($title, $link);
				$template.= '<br />';
			}
			if ($authors) {
				$template.= t('Authors').': '.implode(', ', $authors);
				$template.= '<br />';
			}
			if ($publisher) {
				$template.= t('Publisher').': '.$publisher;
				$template.= '</div>';
			}
		break;
	}
	

	
?>