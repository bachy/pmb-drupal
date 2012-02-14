<?php 
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_gateway.inc,v 1.12 2011-10-21 20:32:26 gueluneau Exp $

abstract class pmb_gateway {
	protected $session_id = '';
	public function set_session_id($session_id) {
		$this->session_id = $session_id;
	}
	
	abstract public function get_notice($notice_id);
	abstract public function get_external_notice($notice_id);
	abstract public function get_bulletin($bulletin_id);
	abstract public function find_notice_bulletin($notice_id);
	abstract public function get_notices($notice_ids);
	abstract public function get_external_notices($notice_ids);
	abstract public function get_author($author_id);
	abstract public function get_publisher($publisher_id);
	abstract public function get_collection($collection_id);
	abstract public function get_subcollection($subcollection_id);
	abstract public function get_location_and_sections();
	abstract public function get_thesauri();
	abstract public function get_shelves();
	abstract public function get_shelf_notice_ids($shelf_id);
	abstract public function get_category($category_id);
	abstract public function get_section_notice_ids($section_id);
	abstract public function get_search_fields();
	abstract public function get_search_notice_ids($search_terms, $search_fields);
	abstract public function get_external_search_notice_ids($search_terms, $search_fields, $source_ids);
	abstract public function get_external_search_sources();
	abstract public function get_unimarc_labels();
	
	abstract public function reader_login($login, $password);
	abstract public function reader_get_account_info();
	abstract public function reader_get_loans();
	abstract public function reader_get_reservations();
	abstract public function reader_delete_reservation($reservation_id);
	abstract public function reader_can_reserve_notice($notice_id, $bulletin_id);
	abstract public function reader_get_reservation_locations($notice_id, $bulletin_id);
	abstract public function reader_add_reservation($notice_id, $bulletin_id, $location_id);
	abstract public function reader_get_suggestions();
	abstract public function reader_get_suggestion_sources_and_categories();
	abstract public function reader_add_suggestion($suggestion);
	abstract public function reader_edit_suggestion($suggestion);
	abstract public function reader_delete_suggestion($suggestion_id);
	abstract public function reader_get_reading_lists();
	abstract public function reader_get_public_reading_lists();
	abstract public function reader_get_cart();
	abstract public function reader_delete_notices_from_cart($notice_ids);
	abstract public function reader_empty_cart();
	abstract public function add_notices_to_cart($notice_ids);
	abstract public function add_notices_to_reading_list($list_id, $notice_ids);
	abstract public function remove_notices_to_reading_list($list_id, $notice_ids);
	abstract public function empty_reading_list($list_id);
}

class pmb_gateway_factory {
	protected static $gateway = NULL;
	
	function __construct() {
		if (!$this->gateway) {
			$this->gateway = NULL;
			$link_type = variable_get('pmb_link_type', 'json-rpc');
			switch($link_type) {
				case 'json-rpc':
					$server = variable_get('pmb_link_serverurl','');
					$login = variable_get('pmb_link_serveruser','');
					$password = variable_get('pmb_link_serverpassword','');
					require_once(drupal_get_path('module', 'pmb').'/classes/pmb_gateway_jsonrpc.inc');
					$this->gateway = new pmb_gateway_json_rpc($server, $login, $password);
						
					break;
				default:
					break;
			}
		}		
	}
	
	function get_gateway() {
		return $this->gateway;
	}
}