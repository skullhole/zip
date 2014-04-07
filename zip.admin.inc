<?php

function zip_admin_form(){
	$form['box'] = array(
		'#type' => 'fieldset',
		'#title' => t('Zip settings'), 
		'#description' => t('Clear dir with zip files.'), 
	);
			
	$form['box']['button']  = array( 
		'#type' => 'submit', 
		'#value' => t('Clear') 
		
	);
	
	return $form;
}

function zip_admin_form_submit($form , &$form_state) {
	
	$uri_dir = 'public://zip';
	
	$query = db_select('file_managed', 'f')
		->fields('f', array('fid','uri'))
		->condition('f.uri',  $uri_dir . '%', 'LIKE')
		->execute()
		->fetchAllKeyed();
	
	foreach($query as $key=>$value){
		
		$file = new StdClass();
		$file->fid = $key;
		$file->uri = $value;
		
		file_delete($file,true);
	}	
	drupal_set_message('Now directory with zip files clear.');
}
