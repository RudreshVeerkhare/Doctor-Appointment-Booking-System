#include <gtk/gtk.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include "struct.h"
#include "func_decl.h"


// sql connection details
static const char *host = "localhost";
static const char *user = "root";
static const char *pass = "";
static char *dbname = "doctor";
unsigned int port = 3306;
static const char *unix_socket = NULL;
unsigned int flag = 0;


int main(int argn, char **arga){


	// CONNECTIING TO MYSQL SERVER
	MYSQL *connection = mysql_init(NULL);
	MYSQL_RES *result;
	MYSQL_ROW row;
	if(!mysql_real_connect(connection,host,user,pass,NULL,port,unix_socket,flag)){

		fprintf(stderr, "Error : %s [%d]\n",mysql_error(connection), mysql_errno(connection));
		exit(1);
	}

	
	create_database(connection,dbname);
	create_table(connection, "doctor(id int(3) not null auto_increment primary key,\
						name text not null,\
						start_time int(5) unsigned not null,\
						end_time int(5) unsigned not null,\
                                                avail text not null)");
        create_table(connection, "user_details(email text not null,\
                                password text not null,\
                                fullname text not null,\
                                age int(3) not null,\
                                gender varchar(2) not null)");


	//GTK 
	GtkBuilder *builder;
	
	GError *error = NULL;
	GtkCssProvider *css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider,"custom.css",NULL);
	
	p_data *data;
	data = g_slice_new(p_data);

	gtk_init(&argn, &arga);

	builder = gtk_builder_new();

	if(! gtk_builder_add_from_file(builder,"gui/hms.glade",&error)){
		g_warning("%s\n", error->message);
		g_free(error);
		return 1;
	}

	


	data->start_up_window = GTK_WINDOW( gtk_builder_get_object(builder,"start_up_window") );
	data->user_login = GTK_WINDOW( gtk_builder_get_object(builder,"user_login") );
	data->admin_login_window = GTK_WINDOW( gtk_builder_get_object(builder, "admin_login_window"));
	data->sign_up = GTK_WINDOW( gtk_builder_get_object(builder, "sign_up"));
	data->admin_workspace = GTK_WINDOW( gtk_builder_get_object(builder, "admin_workspace"));
	data->user_workspace = GTK_WINDOW( gtk_builder_get_object(builder, "user_workspace") );
	data->popup_admin = GTK_WINDOW( gtk_builder_get_object(builder, "popup_admin"));
	data->popup_for_user = GTK_WINDOW( gtk_builder_get_object(builder, "popup_for_user") );
        data->chatbot_window = GTK_WINDOW( gtk_builder_get_object( builder, "chatbot_window") );
        
	data->admin_list = GTK_TREE_VIEW( gtk_builder_get_object(builder, "admin_list"));
	data->user_list = GTK_TREE_VIEW( gtk_builder_get_object(builder, "user_list"));

	data->admin_tree_entry_start = GTK_ENTRY( gtk_builder_get_object(builder, "admin_tree_entry_start") );
	data->admin_tree_entry_end = GTK_ENTRY( gtk_builder_get_object(builder, "admin_tree_entry_end") );
	data->admin_tree_entry_name = GTK_ENTRY( gtk_builder_get_object(builder, "admin_tree_entry_name"));
	data->sign_up_fullname = GTK_ENTRY( gtk_builder_get_object(builder, "sign_up_fullname"));
	data->sign_up_age = GTK_ENTRY( gtk_builder_get_object(builder, "sign_up_age"));
	data->sign_up_email = GTK_ENTRY( gtk_builder_get_object(builder, "sign_up_email"));
	data->sign_up_password = GTK_ENTRY( gtk_builder_get_object(builder, "sign_up_password"));
	data->sign_up_re_password = GTK_ENTRY( gtk_builder_get_object(builder, "sign_up_re_password"));
	data->user_login_email = GTK_ENTRY( gtk_builder_get_object(builder, "user_login_email"));
        data->user_login_password = GTK_ENTRY( gtk_builder_get_object(builder, "user_login_password"));     
        data->admin_login_user = GTK_ENTRY( gtk_builder_get_object(builder, "admin_login_user"));
        data->admin_login_pwd = GTK_ENTRY( gtk_builder_get_object(builder, "admin_login_pwd"));
        data->appointment_time = GTK_ENTRY( gtk_builder_get_object(builder, "appointment_time"));
        data->chatbot_entry = GTK_ENTRY( gtk_builder_get_object(builder, "chatbot_entry"));
        
	data->sign_up_error_msg = GTK_LABEL( gtk_builder_get_object(builder, "sign_up_error_msg"));
        data->user_login_error_msg = GTK_LABEL( gtk_builder_get_object(builder, "user_login_error_msg"));
        data->label_for_admin = GTK_LABEL( gtk_builder_get_object(builder, "label_for_admin"));
        data->invalid_time = GTK_LABEL( gtk_builder_get_object(builder, "invalid_time"));
        data->user_workspace_error_msg = GTK_LABEL(gtk_builder_get_object(builder, "user_workspace_error_msg")); 
        data->user_profile = GTK_LABEL( gtk_builder_get_object(builder, "user_profile"));
        data->appointment_status = GTK_LABEL ( gtk_builder_get_object(builder, "appointment_status"));
        data->chatbot_output = GTK_LABEL( gtk_builder_get_object(builder, "chatbot_output"));
                
	data->sql_conn = connection;
	data->t_name = "doctor";
	data->gender = 'M';
	

	// gtk_widget_set_name(main_window,"main_window");

	gtk_style_context_add_provider_for_screen(gtk_widget_get_screen(GTK_WIDGET(data->start_up_window)),\
                               GTK_STYLE_PROVIDER(css_provider),\
                               GTK_STYLE_PROVIDER_PRIORITY_USER);



	gtk_builder_connect_signals(builder, data);

	init_list(data->admin_list);//for tree view in admin
	init_list(data->user_list);//for tree view in user
	refersh_list(data,0);
	refersh_list(data,1);

	g_object_unref(G_OBJECT(builder));

	gtk_widget_show(GTK_WIDGET(data->start_up_window));

	gtk_main();

	// closing mysql connection
	mysql_close(connection);
	mysql_library_end();

	return 0;

}


