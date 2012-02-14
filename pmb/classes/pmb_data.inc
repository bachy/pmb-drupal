<?php
// +-------------------------------------------------+
// © 2011-2012 PMB Services / www.sigb.net pmb@sigb.net et contributeurs (voir www.sigb.net)
// +-------------------------------------------------+
// $Id: pmb_data.inc,v 1.18 2011-10-21 20:32:26 gueluneau Exp $

require_once(drupal_get_path('module', 'pmb').'/classes/pmb_gateway.inc');

class pmb_data {
	protected $gateway;
	protected $user = NULL;
	protected $cache_profile = 'cache_anonymous_all';
	
	public function __construct() {
		$factory = new pmb_gateway_factory();
		$this->gateway = $factory->get_gateway();
		$this->cache_profile = variable_get('pmb_user_cache_profile', 'cache_anonymous_all');
	}
	
	public function set_user($user) {
		$this->user = $user;
	}
	
	protected function get_cache_profile_suffix() {
		$suffix = '_anonymous';
		if ($this->user) {
			if($this->cache_profile == 'cache_anonymous_empr_all') {
				$suffix = '_empr';
			}
			else if($this->cache_profile == 'cache_anonymous_empr_separate') {
				$suffix  = '_empr_'.$this->user->uid;
			}
		}
		return $suffix;
	}
	
	protected function delete_old_cache_objects() {
		db_query("DELETE FROM {pmb_cache} WHERE delete_on_date < NOW() ");		
	}
	
	public function get_notice($notice_id) {
		if (!$this->gateway)
			return array();
		$notice_id += 0;
		if (!$notice_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'notice_'.$notice_id.$this->get_cache_profile_suffix();
		
		$notice_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($notice_db && $record=db_fetch_array($notice_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}
		
		$notice = $this->gateway->get_notice($notice_id);

		if ($notice) {
			$notice_cache_duration = variable_get('pmb_notice_cache_duration', 3600);
			$notice_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $notice_cache_duration, serialize($notice));
		}

		return $notice;
	}
	
	public function get_notices($notice_ids) {
		if (!$this->gateway)
			return array();

		if (!$notice_ids)
			return array();
		
		array_walk($notice_ids, create_function('&$a', '$a+=0;'));	//Virons ce qui n'est pas entier
		$notice_ids = array_unique($notice_ids);
		if (!$notice_ids)
			return array();

		$this->delete_old_cache_objects();
		
		$ids_in_cache = $notice_ids;
		$cache_suffix = $this->get_cache_profile_suffix();
		array_walk($ids_in_cache, create_function('&$a', '$a="\'notice_".$a."'.$cache_suffix.'\'";'));;
		
		$results = array();
		
		$notice_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id IN (".implode(',', $ids_in_cache).")");
		if ($notice_db) {
			while($record=db_fetch_array($notice_db)) {
				$anotice = unserialize($record['object_data']);
				$results[$anotice['id']] = $anotice;
				$notice_ids = array_diff($notice_ids, array($anotice['id']));
			}
		}

		if ($notice_ids) {

			if ($this->user) {
				$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
				if ($session_id)
					$this->gateway->set_session_id($session_id);
			}

			$fetched_notices = $this->gateway->get_notices($notice_ids);
			foreach($fetched_notices as $anotice) {
				$results[$anotice['id']] = $anotice;
			}
			
			$notice_cache_duration = variable_get('pmb_notice_cache_duration', 3600);
			$notice_cache_duration += 0;
			foreach($fetched_notices as $notice_id => $anotice) {
				if (!$anotice)
					continue;
				$object_ref_name = 'notice_'.$notice_id.$cache_suffix;
				db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $object_ref_name, $notice_cache_duration, serialize($anotice));
			}
		}

		return $results;
	}

	public function get_external_notices($notice_ids) {
		if (!$this->gateway)
			return array();

		if (!$notice_ids)
			return array();
		
		array_walk($notice_ids, create_function('&$a', '$a+=0;'));	//Virons ce qui n'est pas entier
		$notice_ids = array_unique($notice_ids);
		if (!$notice_ids)
			return array();

		$this->delete_old_cache_objects();
		
		$ids_in_cache = $notice_ids;
		$cache_suffix = $this->get_cache_profile_suffix();
		array_walk($ids_in_cache, create_function('&$a', '$a="\'external_notice_".$a."'.$cache_suffix.'\'";'));;
		
		$results = array();
		
		$notice_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id IN (".implode(',', $ids_in_cache).")");
		if ($notice_db) {
			while($record=db_fetch_array($notice_db)) {
				$anotice = unserialize($record['object_data']);
				$results[$anotice['id']] = $anotice;
				$notice_ids = array_diff($notice_ids, array($anotice['id']));
			}
		}

		if ($notice_ids) {

			if ($this->user) {
				$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
				if ($session_id)
					$this->gateway->set_session_id($session_id);
			}

			$fetched_notices = $this->gateway->get_external_notices($notice_ids);
			foreach($fetched_notices as $anotice) {
				$results[$anotice['id']] = $anotice;
			}
			
			$notice_cache_duration = variable_get('pmb_external_notice_cache_duration', 3600);
			$notice_cache_duration += 0;
			foreach($fetched_notices as $notice_id => $anotice) {
				if (!$anotice)
					continue;
				$object_ref_name = 'external_notice_'.$notice_id.$cache_suffix;
				db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $object_ref_name, $notice_cache_duration, serialize($anotice));
			}
		}

		return $results;
	}

	public function get_external_notice($notice_id) {
		if (!$this->gateway)
			return array();
		$notice_id += 0;
		if (!$notice_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'external_notice_'.$notice_id.$this->get_cache_profile_suffix();
		
		$notice_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($notice_db && $record=db_fetch_array($notice_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}
		
		$notice = $this->gateway->get_external_notice($notice_id);

		if ($notice) {
			$notice_cache_duration = variable_get('pmb_external_notice_cache_duration', 3600);
			$notice_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $notice_cache_duration, serialize($notice));
		}

		return $notice;
	}
	
	public function get_bulletin($bulletin_id) {
		if (!$this->gateway)
			return array();
		$bulletin_id += 0;
		if (!$bulletin_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'bulletin_'.$bulletin_id.$this->get_cache_profile_suffix();
		
		$bulletin_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($bulletin_db && $record=db_fetch_array($bulletin_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$bulletin = $this->gateway->get_bulletin($bulletin_id);

		$notice_cache_duration = variable_get('pmb_notice_cache_duration', 3600);
		$notice_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $notice_cache_duration, serialize($bulletin));

		return $bulletin;
	}
	
	public function get_serials() {
		if (!$this->gateway)
			return array();

		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'serials_'.$this->get_cache_profile_suffix();
		
		$author_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($author_db && $record=db_fetch_array($author_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$serials = $this->gateway->get_serials();

		if ($serials) {
			$serials_cache_duration = variable_get('pmb_serials_cache_duration', 3600);
			$serials_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $serials_cache_duration, serialize($serials));
		}

		return $serials;
	}
	
	public function get_bulletins($bulletin_ids) {
		if (!$this->gateway)
			return array();

		if (!$bulletin_ids)
			return array();
		
		array_walk($bulletin_ids, create_function('&$a', '$a+=0;'));	//Virons ce qui n'est pas entier
		$bulletin_ids = array_unique($bulletin_ids);
		if (!$bulletin_ids)
			return array();

		$this->delete_old_cache_objects();
		
		$ids_in_cache = $bulletin_ids;
		$cache_suffix = $this->get_cache_profile_suffix();
		array_walk($ids_in_cache, create_function('&$a', '$a="\'bulletin_".$a."'.$cache_suffix.'\'";'));;
		
		$results = array();
		
		$bulletin_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id IN (".implode(',', $ids_in_cache).")");
		if ($bulletin_db) {
			while($record=db_fetch_array($bulletin_db)) {
				$bulletin = unserialize($record['object_data']);
				$results[$bulletin['id']] = $bulletin;
				$bulletin_ids = array_diff($bulletin_ids, array($bulletin['id']));
			}
		}

		if ($bulletin_ids) {

			if ($this->user) {
				$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
				if ($session_id)
					$this->gateway->set_session_id($session_id);
			}

			$fetched_bulletins = $this->gateway->get_bulletins($bulletin_ids);
			foreach($fetched_bulletins as $bulletin) {
				$results[$bulletin['id']] = $bulletin;
			}
			
			$notice_cache_duration = variable_get('pmb_notice_cache_duration', 3600);
			$notice_cache_duration += 0;
			foreach($fetched_bulletins as $bulletin_id => $abulletin) {
				if (!$abulletin)
					continue;
				$object_ref_name = 'bulletin_'.$bulletin_id.$cache_suffix;
				db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $object_ref_name, $notice_cache_duration, serialize($abulletin));
			}
		}

		return $results;
	}
	
	public function find_notice_bulletin($notice_id) {
		if (!$this->gateway)
			return array();
		$notice_id += 0;
		if (!$notice_id)
			return array();
		$result = array();
		
		return $this->gateway->find_notice_bulletin($notice_id);
	}	
	
	public function get_author($author_id) {
		if (!$this->gateway)
			return array();
		$author_id += 0;
		if (!$author_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'author_'.$author_id.$this->get_cache_profile_suffix();
		
		$author_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($author_db && $record=db_fetch_array($author_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$author = $this->gateway->get_author($author_id);

		if ($author) {
			$author_cache_duration = variable_get('pmb_author_cache_duration', 3600);
			$author_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $author_cache_duration, serialize($author));
		}

		return $author;
	}
	
	public function get_publisher($publisher_id) {
		if (!$this->gateway)
			return array();
		$publisher_id += 0;
		if (!$publisher_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'publisher_'.$publisher_id.$this->get_cache_profile_suffix();
		
		$publisher_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($publisher_db && $record=db_fetch_array($publisher_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$publisher = $this->gateway->get_publisher($publisher_id);

		if ($publisher) {
			$publisher_cache_duration = variable_get('pmb_publisher_cache_duration', 3600);
			$publisher_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $publisher_cache_duration, serialize($publisher));
		}

		return $publisher;
	}	
	
	public function get_collection($collection_id) {
		if (!$this->gateway)
			return array();
		$collection_id += 0;
		if (!$collection_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'collection_'.$collection_id.$this->get_cache_profile_suffix();
		
		$collection_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($collection_db && $record=db_fetch_array($collection_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$collection = $this->gateway->get_collection($collection_id);

		if ($collection) {
			$collection_cache_duration = variable_get('pmb_collection_cache_duration', 3600);
			$collection_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $collection_cache_duration, serialize($collection));
		}

		return $collection;
	}	
	
	public function get_subcollection($subcollection_id) {
		if (!$this->gateway)
			return array();
		$subcollection_id += 0;
		if (!$subcollection_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'subcollection_'.$subcollection_id.$this->get_cache_profile_suffix();
		
		$subcollection_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($subcollection_db && $record=db_fetch_array($subcollection_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$subcollection = $this->gateway->get_subcollection($subcollection_id);

		if ($subcollection) {
			$subcollection_cache_duration = variable_get('pmb_subcollection_cache_duration', 3600);
			$subcollection_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $subcollection_cache_duration, serialize($subcollection));
		}

		return $subcollection;
	}	
	
	public function get_location_and_sections() {
		if (!$this->gateway)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$author_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'locations_and_sections');
		if ($author_db && $record=db_fetch_array($author_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$locations_and_sections = $this->gateway->get_location_and_sections();

		$location_and_sections_cache_duration = variable_get('pmb_location_and_sections_cache_duration', 3600);
		$location_and_sections_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'locations_and_sections', $location_and_sections_cache_duration, serialize($locations_and_sections));

		return $locations_and_sections;		
	}

	public function get_thesauri() {
		if (!$this->gateway)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$author_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'thesauri');
		if ($author_db && $record=db_fetch_array($author_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$thesauri = $this->gateway->get_thesauri();

		if ($thesauri) {
			$thesauri_cache_duration = variable_get('pmb_thesauri_cache_duration', 24*3600);
			$thesauri_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'thesauri', $thesauri_cache_duration, serialize($thesauri));
		}

		return $thesauri;		
	}
	
	public function get_shelves() {
		if (!$this->gateway)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$shelves_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'shelves');
		if ($shelves_db && $record=db_fetch_array($shelves_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}
			
		$shelves = $this->gateway->get_shelves();

		if ($shelves) {
			$shelves_cache_duration = variable_get('pmb_shelves_cache_duration', 3600);
			$shelves_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'shelves', $shelves_cache_duration, serialize($shelves));
		}

		return $shelves;		
	}
	
	public function get_shelf_notice_ids($shelf_id) {
		if (!$this->gateway)
			return array();
			
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'shelf_'.$shelf_id.$this->get_cache_profile_suffix();

		$author_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($author_db && $record=db_fetch_array($author_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}	

		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}			
			
		$result = $this->gateway->get_shelf_notice_ids($shelf_id);
		
		$shelf_cache_duration = variable_get('pmb_shelves_cache_duration', 3600);
		$shelf_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $shelf_cache_duration, serialize($result));

		return $result;
	}	
	
	public function get_category($category_id) {
		if (!$this->gateway)
			return array();
		$category_id += 0;
		if (!$category_id)
			return array();
		$result = array();
		
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'category_'.$category_id.$this->get_cache_profile_suffix();
		
		$category_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($category_db && $record=db_fetch_array($category_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}
		
		$category = $this->gateway->get_category($category_id);

		if ($category) {
			$category_cache_duration = variable_get('pmb_category_cache_duration', 3600);
			$category_cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $category_cache_duration, serialize($category));
		}

		return $category;
	}	
	
	public function get_section_notice_ids($section_id) {
		if (!$this->gateway)
			return array();
			
		$this->delete_old_cache_objects();
		
		$cache_ref_name = 'section_'.$section_id.$this->get_cache_profile_suffix();

		$author_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($author_db && $record=db_fetch_array($author_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}

		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}						
			
		$result = $this->gateway->get_section_notice_ids($section_id);
		
		$location_and_sections_cache_duration = variable_get('pmb_location_and_sections_cache_duration', 3600);
		$location_and_sections_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $location_and_sections_cache_duration, serialize($result));

		return $result;
	}
	
	public function get_search_fields() {
		if (!$this->gateway)
			return array();
			
		$this->delete_old_cache_objects();
		
		$cache_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'search_fields');
		if ($cache_db && $record=db_fetch_array($cache_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}			
			
		$result = $this->gateway->get_search_fields();
		
		$search_fields_cache_duration = variable_get('pmb_search_fields_cache_duration', 24*3600);
		$search_fields_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'search_fields', $search_fields_cache_duration, serialize($result));

		return $result;
	}	
	
	public function get_search_notice_ids($search_terms, $search_fields) {
		if (!$this->gateway)
			return array();
			
		$this->delete_old_cache_objects();
		
		$search_id = md5(serialize(array($search_terms, $search_fields)));
		
		$cache_ref_name = 'search_'.$search_id.$this->get_cache_profile_suffix();
		
		$search_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($search_db && $record=db_fetch_array($search_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}	

		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}			
			
		$result = $this->gateway->get_search_notice_ids($search_terms, $search_fields);
		
		$search_cache_duration = variable_get('pmb_search_cache_duration', 3600);
		$search_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $search_cache_duration, serialize($result));

		return $result;

	}
	public function get_external_search_notice_ids($search_terms, $search_fields, $source_ids) {
		if (!$this->gateway)
			return array();
			
		$this->delete_old_cache_objects();
		$search_cache_duration = variable_get('pmb_external_search_cache_duration', 3600);
		$search_cache_duration += 0;
		
		if ($this->user) {
			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
			if ($session_id)
				$this->gateway->set_session_id($session_id);
		}			
		
//		//si on veut faire ca bien on effectue une recherche par source....
//		$result = array();
//		foreach($source_ids as $source_id){
//			$search_id = md5(serialize(array($search_terms, $search_fields,$source_id)));
//			$cache_ref_name = 'external_search_'.$search_id.$this->get_cache_profile_suffix();
//			$search_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
//			if ($search_db && $record=db_fetch_array($search_db)) {
//				$partial_result = unserialize($record['object_data']);
//				$result[$source_id]= $partial_result;
//				break;
//			}
//			$partial_result = $this->gateway->get_external_search_notice_ids($search_terms, $search_fields, array($source_id));
//			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $search_cache_duration, serialize($partial_result));
//			$result[$source_id]= $partial_result;
//		}
		
		//fin // search
		
		$search_id = md5(serialize(array($search_terms, $search_fields,$source_ids)));
		
		$cache_ref_name = 'external_search_'.$search_id.$this->get_cache_profile_suffix();
		
		$search_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", $cache_ref_name);
		if ($search_db && $record=db_fetch_array($search_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}

		$result = $this->gateway->get_external_search_notice_ids($search_terms, $search_fields, $source_ids);
		
		$search_cache_duration = variable_get('pmb_external_search_cache_duration', 3600);
		$search_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", $cache_ref_name, $search_cache_duration, serialize($result));

		return $result;
	}
	
	public function get_external_search_sources() {
		if (!$this->gateway)
			return array();
			
		$this->delete_old_cache_objects();
		
		$cache_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'external_search_sources');
		if ($cache_db && $record=db_fetch_array($cache_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}			
			
		$result = $this->gateway->get_external_search_sources();
		
		$external_search_sources_cache_duration = variable_get('pmb_external_search_sources_cache_duration', 24*3600);
		$external_search_sources_cache_duration += 0;
		db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'external_search_sources', $external_search_sources_cache_duration, serialize($result));

		return $result;
	}	
	
	public function get_unimarc_labels() {
		global $pmb_labels;
		
		if(!$pmb_labels){
			if (!$this->gateway)
				return array();
			
			$this->delete_old_cache_objects();
			
			$cache_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'unimarc_labels');
			if ($cache_db && $record=db_fetch_array($cache_db)) {
				$result = unserialize($record['object_data']);
				return $result;
			}			
				
			$pmb_labels = $this->gateway->get_unimarc_labels();
			
			$cache_duration = 3*3600;
			$cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'unimarc_labels', $cache_duration, serialize($result));
		}
		return $pmb_labels;
	}
	
	public function reader_sessid($login, $password) {
		$user = user_load(array('name' => $login));
		if ($user && isset($user->pmb_session['sessid_date'])) {
			if (time() - ($user->pmb_session['sessid_date']) < (variable_get('pmb_reader_session_duration', 20*60) - 5)) {
				return $user->pmb_session['sessid'];
			}
		}
		
		if (!$this->gateway)
			return FALSE;
		$sessid = $this->gateway->reader_login($login, $password);
		if (!$sessid)
			return FALSE;
		
		$reader_info = $this->gateway->reader_get_account_info($sessid);
			
		if ($user) {
			if ($reader_info) {
			if (isset($reader_info->personal_information->email) && $reader_info->personal_information->email)
				$to_save['mail'] = $reader_info->personal_information->email;
				$to_save['pmb_reader_info'] = $reader_info;
			}
			$to_save['pmb_session'] = array('sessid' => $pmb_sess_id, 'sessid_date' => time());
			user_save($user, $to_save);
		//	user_save($user, array('pmb_session' => array('sessid' => $sessid, 'sessid_date' => time()), 'pmb_reader_info' => $reader_info));
		}
		return $sessid;
	}
	
	public function reader_get_account_info($session_id) {
		if (!$this->gateway)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		return $this->gateway->reader_get_account_info();
	}
	
	public function reader_get_loans($login, $user=NULL) {
		if (!$this->gateway)
			return FALSE;
		if (!$user)
			$user = user_load(array('name' => $login));
			
		if ($user && isset($user->pmb_reader_loans['fetched_date'])) {
			if (time() - ($user->pmb_reader_loans['fetched_date']) < (variable_get('pmb_reader_loans_cache_duration', 20*60) - 5)) {
				return $user->pmb_reader_loans['loans'];
			}
		}
			
		$session_id = $this->reader_sessid($user->pmb_credentials['login'], $user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$loans = $this->gateway->reader_get_loans();
		if ($user) {
			user_save($user, array('pmb_reader_loans' => array('fetched_date' => time(), 'loans' => $loans)));
		}
		return $loans;
	}
	
	public function reader_get_reservations($login, $user=NULL) {
		if (!$this->gateway)
			return FALSE;
		if (!$user)
			$user = user_load(array('name' => $login));
			
		if ($user && isset($user->pmb_reader_reservations['fetched_date'])) {
			if (time() - ($user->pmb_reader_reservations['fetched_date']) < (variable_get('pmb_reader_reservations_duration', 5))) {
				return $user->pmb_reader_reservations['reservations'];
			}
		}
			
		$session_id = $this->reader_sessid($user->pmb_credentials['login'], $user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$resas = $this->gateway->reader_get_reservations();
		if ($user) {
			user_save($user, array('pmb_reader_reservations' => array('fetched_date' => time(), 'reservations' => $resas)));
		}
		return $resas;
	}

	public function reader_delete_reservation($login, $user=NULL, $reservation_id) {
		if (!$this->gateway)
			return FALSE;
		if (!$user)
			$user = user_load(array('name' => $login));
			
		$session_id = $this->reader_sessid($user->pmb_credentials['login'], $user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->reader_delete_reservation($reservation_id);
		user_save($user, array('pmb_reader_reservations' => array('fetched_date' => 0, 'reservations' => array())));
		return TRUE;
	}
	
	public function reader_can_reserve_notice($login, $user=NULL, $notice_id, $bulletin_id) {
		if (!$this->gateway)
			return FALSE;
		if (!($notice_id || $bulletin_id))
			return FALSE;
		if (!$user)
			$user = user_load(array('name' => $login));
			
		$session_id = $this->reader_sessid($user->pmb_credentials['login'], $user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		return $this->gateway->reader_can_reserve_notice($notice_id, $bulletin_id);
	}
	
	public function reader_get_reservation_locations($notice_id, $bulletin_id) {
		if (!$this->gateway)
			return FALSE;
		if (!($notice_id || $bulletin_id))
			return FALSE;
		if (!$this->user)
			return FALSE;
			
		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		return $this->gateway->reader_get_reservation_locations($notice_id, $bulletin_id);
	}	
	
	public function reader_add_reservation($notice_id, $bulletin_id, $location_id) {
		if (!$this->gateway)
			return FALSE;
		if (!($notice_id || $bulletin_id))
			return FALSE;
		if (!$this->user)
			return FALSE;
			
		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		return $this->gateway->reader_add_reservation($notice_id, $bulletin_id, $location_id);
	}
	
	public function reader_get_suggestions() {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$suggs = $this->gateway->reader_get_suggestions();
		return $suggs;
	}

	public function reader_get_reading_lists() {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$lists = $this->gateway->reader_get_reading_lists();
		return $lists;
	}

	public function reader_get_public_reading_lists() {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$lists = $this->gateway->reader_get_public_reading_lists();
		return $lists;
	}
	
	public function reader_get_suggestion_sources_and_categories() {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$cache_db = db_query("SELECT object_data FROM {pmb_cache} WHERE object_id = '%s'", 'reader_suggestions_sources_and_categories');
		if ($cache_db && $record=db_fetch_array($cache_db)) {
			$result = unserialize($record['object_data']);
			return $result;
		}			
			
		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$sugg_categs_and_sources = $this->gateway->reader_get_suggestion_sources_and_categories();
		
		if ($sugg_categs_and_sources) {
			$cache_duration = variable_get('pmb_suggs_categs_and_sources_cache_duration', 24*3600);
			$cache_duration += 0;
			db_query("INSERT INTO {pmb_cache} (object_id, delete_on_date, object_data) VALUES ('%s', NOW() + INTERVAL %s SECOND, '%s')", 'reader_suggestions_sources_and_categories', $cache_duration, serialize($sugg_categs_and_sources));
		}
		
		return $sugg_categs_and_sources;
	}

	public function reader_add_suggestion($suggestion) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$result = $this->gateway->reader_add_suggestion($suggestion);
		return $result;
	}
	
	public function reader_edit_suggestion($suggestion) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$result = $this->gateway->reader_edit_suggestion($suggestion);
		return $result;
	}	
	
	public function reader_delete_suggestion($suggestion_id) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$result = $this->gateway->reader_delete_suggestion($suggestion_id);
		return $result;
	}
	
	public function reader_get_cart() {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$cart = $this->gateway->reader_get_cart();
		return $cart;
	}

	public function reader_delete_notices_from_cart($notice_ids) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->reader_delete_notices_from_cart($notice_ids);
		return TRUE;
	}

	public function reader_empty_cart() {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->reader_empty_cart();
		return TRUE;
	}
	
	public function add_notices_to_cart($notice_ids) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->add_notices_to_cart($notice_ids);
		return TRUE;
	}
	
	public function add_notices_to_reading_list($list_id, $notice_ids) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->add_notices_to_reading_list($list_id, $notice_ids);
		return TRUE;
	}

	public function remove_notices_to_reading_list($list_id, $notice_ids) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->remove_notices_to_reading_list($list_id, $notice_ids);
		return TRUE;
	}

	public function empty_reading_list($list_id) {
		if (!$this->gateway)
			return FALSE;
		if (!$this->user)
			return FALSE;

		$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
		if (!$session_id)
			return FALSE;
		$this->gateway->set_session_id($session_id);
		$this->gateway->empty_reading_list($list_id);
		return TRUE;
	}
	
//	public function getAdvancedSearchFields($fetch_values=false){
//		if (!$this->gateway)
//			return FALSE;
//		if ($this->user) {
//			$session_id = $this->reader_sessid($this->user->pmb_credentials['login'], $this->user->pmb_credentials['password']);
//			if ($session_id)
//				$this->gateway->set_session_id($session_id);
//		}	
//		$fields = $this->gateway->getAdvancedSearchFields($fetch_values);
//		return $fields;
//	}
}