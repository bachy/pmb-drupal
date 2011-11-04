<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_notice_display.tpl.php,v 1.6 2011-10-21 20:32:24 gueluneau Exp $

	$notice_id = $notice['id'];
	$notice_notice = $notice['notice'];

	switch($display_type) {
		case 'medium_line':
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
					$authors[] = l($display, 'pmb/view_author/'.$afield['id'].'/');
				}
			}
			
			if (isset($notice_notice['f']['701'])) {
				foreach($notice_notice['f']['701'] as $afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = l($display, 'pmb/view_author/'.$afield['id'].'/');
				}
			}
		
			if (isset($notice_notice['f']['702'])) {
				foreach($notice_notice['f']['702'] as &$afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = l($display, 'pmb/view_author/'.$afield['id'].'/');
				}
			}			
			
			$publisher = '';
			if (isset($notice_notice['f']['210'])) {
				foreach($notice_notice['f']['210'] as &$afield) {
					$display = '';
					if($afield['c'] != ""){
						$publisher = l($afield['c'], 'pmb/view_publisher/'.$afield['id']);
					}
				}
			}			
			
			switch($notice_notice['header']['hl']) {
		    	case 1:
		    		$link = 'pmb/view_serial/'.$notice_id.'/';
		    		break;
		    	case 2:
		    		$link = 'pmb/view_notice/'.$notice_id.'/';
		    		break;
		    	default:
		    	case 0:
					$link = 'pmb/view_notice/'.$notice_id.'/';
		    		break;
		    }
			
			$template.= '<div id="notice_'.$notice_id.'_info" style="display:inline-block;margin-left:5px;vertical-align:top;">';
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
			}
			$template.= '</div>';
			break;
		case 'small_line':
			$cover_url = '';
		
			if (isset($notice_notice['f']['896'][0]['a'])) {
				$cover_url = $notice_notice['f']['896'][0]['a'];
			}
		
			if ($cover_url) {
				$template.= '<div id="notice_'.$notice_id.'_cover" style="display:inline-block;">';
				$template.= '<img src="'.check_plain($cover_url).'" style="max-width: 40px;">';
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
					$authors[] = l($display, 'pmb/view_author/'.$afield['id'].'/');
				}
			}
			
			if (isset($notice_notice['f']['701'])) {
				foreach($notice_notice['f']['701'] as $afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = l($display, 'pmb/view_author/'.$afield['id'].'/');
				}
			}
		
			if (isset($notice_notice['f']['702'])) {
				foreach($notice_notice['f']['702'] as &$afield) {
					$display = '';
					$display .= isset($afield['a']) ? $afield['a'].' ' : '';
					$display .= isset($afield['b']) ? $afield['b'].' ' : '';
					$display = trim($display);
					$authors[] = l($display, 'pmb/view_author/'.$afield['id'].'/');
				}
			}			
			
			$publisher = '';
			if (isset($notice_notice['f']['210'])) {
				foreach($notice_notice['f']['210'] as &$afield) {
					$display = '';
					$publisher = l($afield['c'], 'pmb/view_publisher/'.$afield['id']);
				}
			}			
			
			switch($notice_notice['header']['hl']) {
		    	case 1:
		    		$link = 'pmb/view_serial/'.$notice_id.'/';
		    		break;
		    	case 2:
		    		$link = 'pmb/view_notice/'.$notice_id.'/';
		    		break;
		    	default:
		    	case 0:
					$link = 'pmb/view_notice/'.$notice_id.'/';
		    		break;
		    }
			
			$template.= '<div id="notice_'.$notice_id.'_info" style="display:inline-block;margin-left:5px;vertical-align:top;">';
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