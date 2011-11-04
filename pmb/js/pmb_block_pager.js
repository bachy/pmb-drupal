function pmb_block_get_page(id,url){
	$('#'+id).fadeTo("fast", 0.4);
	$('#'+id).load(Drupal.settings.basePath + '?q='+url, function (){
		$('#'+id).fadeTo("slow", 1);
	});
	return false;
}