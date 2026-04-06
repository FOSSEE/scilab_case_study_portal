<?php
/*
Approval Status :
0 - Pending
1 - Approved
2 - Dis-Approved
3 - Completed
Solution Status :
0 - Pending
1 - Approved
2 - Dis-Approved
Solution Display :
0 - No
1 - Yes
is_completed
0 - in progress
1 - Completed
Tables :
case_study_solution : approval_status
0 - Pending
1 - Approved
2 - Disapproved (delete it)
*/
function scilab_case_study_proposal_form($form, &$form_state, $no_js_use = FALSE)
{
	global $user;
	/************************ start approve book details ************************/
	if ($user->uid == 0)
	{
		$msg = drupal_set_message(t('It is mandatory to ' . l('login', 'user') . ' on this website to access the case study proposal form. If you are new user please create a new account first.'), 'error');
		drupal_goto('user');
		return $msg;
	} //$user->uid == 0
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('uid', $user->uid);
	$query->orderBy('id', 'DESC');
	$query->range(0, 1);
	$proposal_q = $query->execute();
	$proposal_data = $proposal_q->fetchObject();
	if ($proposal_data)
	{
		if ($proposal_data->approval_status == 0 || $proposal_data->approval_status == 1)
		{
			drupal_set_message(t('We have already received your proposal.'), 'status');
			drupal_goto('');
			return;
		} //$proposal_data->approval_status == 0 || $proposal_data->approval_status == 1
	} //$proposal_data
	$form['#attributes'] = array(
		'enctype' => "multipart/form-data"
	);

	$form['name_title'] = array(
		'#type' => 'select',
		'#title' => t('Title'),
		'#options' => array(
			'Dr' => 'Dr',
			'Prof' => 'Prof',
			'Mr' => 'Mr',
			'Ms' => 'Ms'
		),
		'#required' => TRUE
	);
	$form['contributor_name'] = array(
		'#type' => 'textfield',
		'#title' => t('Name of the contributor'),
		'#size' => 100,
		'#attributes' => array(
			'placeholder' => t('Enter your full name.....')
		),
		'#maxlength' => 250,
		'#required' => TRUE
	);
	$form['contributor_email_id'] = array(
		'#type' => 'textfield',
		'#title' => t('Email'),
		'#size' => 30,
		'#value' => $user->mail,
		'#disabled' => TRUE
	);
	$form['contributor_contact_no'] = array(
		'#type' => 'textfield',
		'#title' => t('Contact No.'),
		'#size' => 10,
		'#attributes' => array(
			'placeholder' => t('Enter your contact number')
		),
		'#maxlength' => 10,
		'#required' => TRUE
	);
	$form['university'] = array(
		'#type' => 'textfield',
		'#title' => t('University'),
		'#size' => 80,
		'#maxlength' => 200,
		'#required' => TRUE,
		'#attributes' => array(
			'placeholder' => 'Insert full name of your university.... '
		)
	);
	$form['institute'] = array(
		'#type' => 'textfield',
		'#title' => t('Institute'),
		'#size' => 80,
		'#maxlength' => 200,
		'#required' => TRUE,
		'#attributes' => array(
			'placeholder' => 'Insert full name of your institute.... '
		)
	);
	$form['how_did_you_know_about_project'] = array(
		'#type' => 'select',
		'#title' => t('How did you come to know about the Case Study Project?'),
		'#options' =>  array(
			'Poster' => 'Poster',
			'Website' => 'Website',
			'Email' => 'Email',
			'Others' => 'Others'
		),
		'#required' => TRUE
	);
	$form['others_how_did_you_know_about_project'] = array(
		'#type' => 'textfield',
		'#title' => t('If ‘Other’, please specify'),
		'#maxlength' => 50,
		'#description' => t('<span style="color:red">Maximum character limit is 50</span>'),
		'#states' => array(
			'visible' => array(
				':input[name="how_did_you_know_about_project"]' => array(
					'value' => 'Others'
				)
			)
		)		
	);
	$form['faculty_name'] = array(
		'#type' => 'textfield',
		'#title' => t('Name of the Faculty Member of your Institution, if any, who helped you with this Case Study Project'),
		'#size' => 50,
		'#maxlength' => 50,
		'#validated' => TRUE,
		'#description' => t('<span style="color:red">Maximum character limit is 50</span>')
	);
	$form['faculty_department'] = array(
		'#type' => 'textfield',
		'#title' => t('Department of the Faculty Member of your Institution, if any, who helped you with this Case Study Project'),
		'#size' => 50,
		'#maxlength' => 50,
		'#validated' => TRUE,
		'#description' => t('<span style="color:red">Maximum character limit is 50</span>')
	);
	$form['faculty_email'] = array(
		'#type' => 'textfield',
		'#title' => t('Email id of the Faculty Member of your Institution, if any, who helped you with this Case Study Project'),
		'#size' => 100,
		'#maxlength' => 255,
		'#validated' => TRUE,
		'#description' => t('<span style="color:red">Maximum character limit is 255</span>')
	);
	$form['country'] = array(
		'#type' => 'select',
		'#title' => t('Country'),
		'#options' => array(
			'India' => 'India',
			'Others' => 'Others'
		),
		'#required' => TRUE,
		'#tree' => TRUE,
		'#validated' => TRUE
	);
	$form['other_country'] = array(
		'#type' => 'textfield',
		'#title' => t('Other than India'),
		'#size' => 100,
		'#attributes' => array(
			'placeholder' => t('Enter your country name')
		),
		'#states' => array(
			'visible' => array(
				':input[name="country"]' => array(
					'value' => 'Others'
				)
			)
		)
	);
	$form['other_state'] = array(
		'#type' => 'textfield',
		'#title' => t('State other than India'),
		'#size' => 100,
		'#attributes' => array(
			'placeholder' => t('Enter your state/region name')
		),
		'#states' => array(
			'visible' => array(
				':input[name="country"]' => array(
					'value' => 'Others'
				)
			)
		)
	);
	$form['other_city'] = array(
		'#type' => 'textfield',
		'#title' => t('City other than India'),
		'#size' => 100,
		'#attributes' => array(
			'placeholder' => t('Enter your city name')
		),
		'#states' => array(
			'visible' => array(
				':input[name="country"]' => array(
					'value' => 'Others'
				)
			)
		)
	);
	$form['all_state'] = array(
		'#type' => 'select',
		'#title' => t('State'),
		'#options' => _cs_list_of_states(),
		'#validated' => TRUE,
		'#states' => array(
			'visible' => array(
				':input[name="country"]' => array(
					'value' => 'India'
				)
			)
		)
	);
	$form['city'] = array(
		'#type' => 'select',
		'#title' => t('City'),
		'#options' => _cs_list_of_cities(),
		'#states' => array(
			'visible' => array(
				':input[name="country"]' => array(
					'value' => 'India'
				)
			)
		)
	);
	$form['pincode'] = array(
		'#type' => 'textfield',
		'#title' => t('Pincode'),
		'#size' => 6,
		'#maxlength' => 6
	);
	/***************************************************************************/
	$form['hr'] = array(
		'#type' => 'item',
		'#markup' => '<hr>'
	);

	$form['project_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Project Title'),
		'#size' => 100,
		'#maxlength' => 250,
		'#description' => t('Maximum character limit is 250'),
		'#required' => TRUE,
		'#validated' => TRUE,
	);
	$form['operating_system'] = array(
		'#type' => 'textfield',
		'#title' => t('Operating System version used'),
		'#required' => TRUE,
		'#size' => 30,
		'#maxlength' => 50
	);
	$form['scilab_version'] = array(
		'#type' => 'textfield',
		'#title' => t('Scilab version used'),
		'#maxlength' => 20,
		//'#options' => $version_options,
		'#attributes' => array(
			'placeholder' => t('Format: Scilab x.x.x')
		),
		'#description' => t('<span style="color:red;">Note: Use Scilab 6.0.0 and above. </span><span>Format: Scilab x.x.x</span>'),
		'#required' => TRUE
	);
	$form['abstract_file'] = array(
		'#type' => 'fieldset',
		'#title' => t('Submit an Abstract'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE
	);
	$form['abstract_file']['abstract_file_path'] = array(
		'#type' => 'file',
		'#size' => 48,
		'#description' => t('<span style="color:red;">Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.</span>') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('resource_upload_extensions', '') . '</span>'
	);
	$form['date_of_proposal'] = array(
		'#type' => 'date_popup',
		'#title' => t('Date of Proposal'),
		'#default_value' => date("Y-m-d H:i:s"),
		'#date_format' => 'd M Y',
		'#disabled' => TRUE,
		'#date_label_position' => '',
	);
	$form['expected_date_of_completion'] = array(
		'#type' => 'date_popup',
		'#title' => t('Expected Date of Completion'),
		'#date_label_position' => '',
		'#description' => '',
		'#default_value' => '',
		'#date_format' => 'd-M-Y',
		//'#date_increment' => 0,
		//'#minDate' => '+0',
		//'#date_year_range' => '+0 : +1',
		'#required' => TRUE,
		 '#datepicker_options' => array(
           'maxDate' => '+45D', // not more than current date
           'minDate' => '+1' // not more than given date
       ),
	);
	$form['term_condition'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Terms And Conditions'),
		'#options' => array(
			'status' => t('<a href="/case-study-project/term-and-conditions" target="_blank">I agree to the Terms and Conditions</a>')
		),
		'#required' => TRUE
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit')
	);
	return $form;
}

function scilab_case_study_proposal_form_validate($form, &$form_state)
{
	if ($form_state['values']['term_condition'] == '1')
	{
		form_set_error('term_condition', t('Please check the terms and conditions'));
		// $form_state['values']['country'] = $form_state['values']['other_country'];
	} //$form_state['values']['term_condition'] == '1'
	if ($form_state['values']['country'] == 'Others')
	{
		if ($form_state['values']['other_country'] == '')
		{
			form_set_error('other_country', t('Enter country name'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['other_country'] == ''
		else
		{
			$form_state['values']['country'] = $form_state['values']['other_country'];
		}
		if ($form_state['values']['other_state'] == '')
		{
			form_set_error('other_state', t('Enter state name'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['other_state'] == ''
		else
		{
			$form_state['values']['all_state'] = $form_state['values']['other_state'];
		}
		if ($form_state['values']['other_city'] == '')
		{
			form_set_error('other_city', t('Enter city name'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['other_city'] == ''
		else
		{
			$form_state['values']['city'] = $form_state['values']['other_city'];
		}
	} //$form_state['values']['country'] == 'Others'
	else
	{
		if ($form_state['values']['country'] == '')
		{
			form_set_error('country', t('Select country name'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['country'] == ''
		if ($form_state['values']['all_state'] == '')
		{
			form_set_error('all_state', t('Select state name'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['all_state'] == ''
		if ($form_state['values']['city'] == '')
		{
			form_set_error('city', t('Select city name'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['city'] == ''
	}
	//Validation for project title

	if(strtotime(date($form_state['values']['expected_date_of_completion'])) < time())
	{
		form_set_error('expected_date_of_completion', t('Completion date should not be earlier than proposal date'));
	}

	if ($form_state['values']['how_did_you_know_about_project'] == 'Others')
	{
		if ($form_state['values']['others_how_did_you_know_about_project'] == '')
		{
			form_set_error('others_how_did_you_know_about_project', t('Please enter how did you know about the project'));
			// $form_state['values']['country'] = $form_state['values']['other_country'];
		} //$form_state['values']['other_country'] == ''
		else
		{
			$form_state['values']['how_did_you_know_about_project'] = $form_state['values']['others_how_did_you_know_about_project'];
		}
	}
	/*if ($form_state['values']['faculty_name'] != '' || $form_state['values']['faculty_name'] != "NULL") {
		if($form_state['values']['faculty_email'] == '' || $form_state['values']['faculty_email'] == "NULL")
		{
			form_set_error('faculty_email', t('Please enter the email id of your faculty'));
		}
		if($form_state['values']['faculty_department'] == '' || $form_state['values']['faculty_department'] == 'NULL'){
			form_set_error('faculty_department', t('Please enter the Department of your faculty'));
		}
	}*/
	
if (isset($_FILES['files']))
	{
		/* check if atleast one source or result file is uploaded */
		if (!($_FILES['files']['name']['abstract_file_path']))
			form_set_error('abstract_file_path', t('Please upload the abstract file'));
		/* check for valid filename extensions */
		foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
		{
			if ($file_name)
			{
				/* checking file type */
				$allowed_extensions_str = variable_get('resource_upload_extensions', '');
				$allowed_extensions = explode(',', $allowed_extensions_str);
				$fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
				$temp_extension = end($fnames);
				if (!in_array($temp_extension, $allowed_extensions))
					form_set_error($file_form_name, t('Only file with ' . $allowed_extensions_str . ' extensions can be uploaded.'));
				if ($_FILES['files']['size'][$file_form_name] <= 0)
					form_set_error($file_form_name, t('File size cannot be zero.'));
				/* check if valid file name */
				if (!scilab_case_study_check_valid_filename($_FILES['files']['name'][$file_form_name]))
					form_set_error($file_form_name, t('Invalid file name specified. Only alphabets and numbers are allowed as a valid filename.'));
			} //$file_name
		} //$_FILES['files']['name'] as $file_form_name => $file_name
	} 
	return $form_state;
}
function scilab_case_study_proposal_form_submit($form, &$form_state)
{
	global $user;
	$root_path = scilab_case_study_path();
	if (!$user->uid)
	{
		drupal_set_message('It is mandatory to login on this website to access the proposal form', 'error');
		return;
	}
	if ($form_state['values']['how_did_you_know_about_project'] == 'Others')
	{
			$how_did_you_know_about_project = $form_state['values']['others_how_did_you_know_about_project'];
	}
	else {
		$how_did_you_know_about_project = $form_state['values']['how_did_you_know_about_project'];
	}
	/* inserting the user proposal */
	$v = $form_state["values"];
	$project_title = trim($v['project_title']);
	$proposar_name = $v['name_title'] . ' ' . $v['contributor_name'];
	$university = $v['university'];
	$directory_name = _cs_dir_name($project_title, $proposar_name);
	$result = "INSERT INTO case_study_proposal
    (
    uid, 
    approver_uid,
    name_title, 
    contributor_name,
    contact_no,
    university,
    institute,
    how_did_you_know_about_project,
    faculty_name,
    faculty_department,
    faculty_email,
    city, 
    pincode, 
    state, 
    country,
    project_title,
    operating_system, 
    scilab_version,
    directory_name,
    approval_status,
    is_completed, 
    dissapproval_reason,
    creation_date, 
    expected_date_of_completion,
    approval_date
    ) VALUES
    (
    :uid, 
    :approver_uid, 
    :name_title, 
    :contributor_name, 
    :contact_no,
    :university, 
    :institute,
    :how_did_you_know_about_project,
    :faculty_name,
    :faculty_department,
    :faculty_email,
    :city, 
    :pincode, 
    :state,  
    :country,
    :project_title,
    :operating_system, 
    :scilab_version,
    :directory_name,
    :approval_status,
    :is_completed, 
    :dissapproval_reason,
    :creation_date, 
    :expected_date_of_completion,
    :approval_date
    )";
	$args = array(
		":uid" => $user->uid,
		":approver_uid" => 0,
		":name_title" => $v['name_title'],
		":contributor_name" => trim($v['contributor_name']),
		":contact_no" => trim($v['contributor_contact_no']),
		":university" => trim($v['university']),
		":institute" => trim($v['institute']),
		":how_did_you_know_about_project" => trim($how_did_you_know_about_project),
		":faculty_name" => $v['faculty_name'],
		":faculty_department" => $v['faculty_department'],
		":faculty_email" => $v['faculty_email'],
		":city" => $v['city'],
		":pincode" => $v['pincode'],
		":state" => $v['all_state'],
		":country" => $v['country'],
		":project_title" => $project_title,
		":operating_system" => $v['operating_system'],
		":scilab_version" => $v['scilab_version'],
		":directory_name" => $directory_name,
		":approval_status" => 0,
		":is_completed" => 0,
		":dissapproval_reason" => "NULL",
		":creation_date" => time(),
		":expected_date_of_completion" => strtotime(date($v['expected_date_of_completion'])),
		":approval_date" => 0
		);
	$proposal_id = db_query($result, $args, array(
		'return' => Database::RETURN_INSERT_ID
	));
	$dest_path = $directory_name . '/';
	$dest_path1 = $root_path . $dest_path;
	//var_dump($dest_path1);die;	
	if (!is_dir($root_path . $dest_path))
		mkdir($root_path . $dest_path);
	/* uploading files */
	foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
	{
		if ($file_name)
		{
			/* checking file type */
			//$file_type = 'S';
			if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
			{
				 drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
				//unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
			} //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
			/* uploading file */
			if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
			{
				$query = "UPDATE case_study_proposal SET samplefilepath = :samplefilepath WHERE id = :id";
				$args = array(
					":samplefilepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
					":id" => $proposal_id
				);
				
				$updateresult = db_query($query, $args);
				//var_dump($args);die;

				drupal_set_message($file_name . ' uploaded successfully.', 'status');
			} //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
			else
			{
				drupal_set_message('Error uploading file : ' . $dest_path . '/' . $file_name, 'error');
			}
		} //$file_name
	} //$_FILES['files']['name'] as $file_form_name => $file_name
	if (!$proposal_id)
	{
		drupal_set_message(t('Error receiving your proposal. Please try again.'), 'error');
		return;
	} //!$proposal_id
	/* sending email */
	$email_to = $user->mail;
	$form = variable_get('case_study_from_email', '');
	$bcc = variable_get('case_study_emails', '');
	$cc = variable_get('case_study_cc_emails', '');
	$params['case_study_proposal_received']['result1'] = $proposal_id;
	$params['case_study_proposal_received']['user_id'] = $user->uid;
	$params['case_study_proposal_received']['headers'] = array(
		'From' => $form,
		'MIME-Version' => '1.0',
		'Content-Type' => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
		'Content-Transfer-Encoding' => '8Bit',
		'X-Mailer' => 'Drupal',
		'Cc' => $cc,
		'Bcc' => $bcc
	);
	if (!drupal_mail('scilab_case_study', 'case_study_proposal_received', $email_to, user_preferred_language($user), $params, $form, TRUE))
		drupal_set_message('Error sending email message.', 'error');
	drupal_set_message(t('We have received your case study proposal. We will get back to you soon.'), 'status');
	drupal_goto('');
}
