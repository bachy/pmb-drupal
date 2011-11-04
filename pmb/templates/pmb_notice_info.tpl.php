<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_notice_info.tpl.php,v 1.3 2011-10-21 20:32:24 gueluneau Exp $

	$notice_id = $notice['id'];
	$notice_notice = $notice['notice'];
	switch($info) {
		case "title" :
			$title = '';
			if (isset($notice_notice['f']['200'][0]['a'])) {
				$title = $notice_notice['f']['200'][0]['a'];
			}
			$template.= $title;
			break;
		case "link" :
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
			    $template.= url($link);
			break;
	}
?>