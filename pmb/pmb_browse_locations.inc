<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_browse_locations.inc,v 1.4 2011-10-21 20:32:24 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_data.inc');

function pmb_browse_locations() {
	$pmb_data = new pmb_data();
	if (isset($GLOBALS["user"]->uid) && isset($GLOBALS["user"]->pmb_credentials))
		$pmb_data->set_user($GLOBALS["user"]);
	$locations_and_sections = $pmb_data->get_location_and_sections();
	
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Browse the catalog'), 'pmb/browse_locations');
    drupal_set_breadcrumb($breadcrumb);

	return theme('pmb_browse_locations', $locations_and_sections, array());
}