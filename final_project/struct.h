#ifndef _STRUCT_H_

#define _STRUCT_H_
 
#define MY_EMAIL "<hospitalforpmdsproject@gmail.com>"


struct upload_status {
  int lines_read;
};

enum {
    
  DOCTOR_NAME = 0,
  START_TIME,
  END_TIME,
  N_COLUMNS
};

typedef struct patient_details{
	GtkWindow   *start_up_window,\
				*admin_login_window,\
				*admin_workspace,\
				*user_login,\
				*popup_admin,\
				*popup_for_user,\
				*sign_up,\
				*user_workspace,\
                                *chatbot_window;   
                                
                                
	GtkEntry    *name,\
				*age,\
				*sex,\
				*email,\
				*time,\
				*admin_tree_entry_name,\
				*admin_tree_entry_start,\
				*admin_tree_entry_end,\
				*user_entry,\
				*sign_up_fullname,\
				*sign_up_age,\
				*sign_up_email,\
				*sign_up_password,\
				*sign_up_re_password,\
                                *user_login_password,\
                                *user_login_email,\
                                *admin_login_user,\
                                *admin_login_pwd,\
                                *appointment_time,\
                                *chatbot_entry;

	GtkTreeView *admin_list,\
				*user_list;

	GtkTreeSelection 	*admin_selection,\
				*user_selection;


	GtkLabel *popup_label,\
			 *sign_up_error_msg,\
                         *user_login_error_msg,\
                         *label_for_admin,\
                         *invalid_time,\
                         *user_workspace_error_msg,\
                         *user_profile,\
                         *appointment_status,\
                         *chatbot_output;
        char gender,\
             current_user_email[100];

	MYSQL *sql_conn;
	char *t_name;	

}p_data;

#endif