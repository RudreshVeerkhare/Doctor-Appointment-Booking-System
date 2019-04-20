#include <gtk/gtk.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>
#include "struct.h"
#include "func_decl.h"


 static char payload_text[10][500] = {
    "To: \r\n",
    "From: " MY_EMAIL " HMS Admin\r\n",
    "Subject: Welcome To Hms\r\n",
    "\r\n", 
    "\r\n",
    "\r\n",
    "\r\n",
    "Thanks For Using HMS\r\n",
    NULL
  };


void refersh_list_user(GtkButton *button,gpointer user_data){
  refersh_list(user_data, 1);
}
void user_login(GtkButton *Button, gpointer user_data){
	p_data *data = user_data;
	gtk_window_present(data->user_login);
	gtk_widget_hide(GTK_WIDGET(data->start_up_window));
        
        gtk_entry_set_text(data->sign_up_fullname,"");
        gtk_entry_set_text(data->sign_up_age,"");
        gtk_entry_set_text(data->sign_up_email,"");
        gtk_entry_set_text(data->sign_up_password,"");
        gtk_entry_set_text(data->sign_up_re_password,"");
        gtk_label_set_text(data->sign_up_error_msg,"");

	gtk_widget_hide(GTK_WIDGET(data->sign_up));
}
void admin_login(GtkButton *Button, gpointer user_data){
        p_data *data = user_data;

	gtk_window_present(data->admin_login_window);
	gtk_widget_hide(GTK_WIDGET(data->start_up_window));
        

}

void sign_up(GtkButton *Button, gpointer user_data){
	p_data *data = user_data;
	gtk_window_present(data->sign_up);
	gtk_widget_hide(GTK_WIDGET(data->user_login));
}

void admin_workspace(GtkButton *Button, gpointer user_data){

	p_data *data = user_data;
        char *admin_username = "admin", *admin_password = "admin1234", *username_temp, *password_temp;
        
        username_temp = (char*)gtk_entry_get_text(data->admin_login_user);
        password_temp = (char*)gtk_entry_get_text(data->admin_login_pwd);
        
        if(strcmp(username_temp,admin_username) != 0 || strcmp(password_temp,admin_password) != 0 ){
            gtk_label_set_text(data->label_for_admin,"Invalid Login Credentials!!!");
            return;
        }
        
	gtk_widget_hide( GTK_WIDGET(data->admin_login_window) );
	gtk_window_present(data->admin_workspace);
        gtk_label_set_text(data->label_for_admin,"");
        gtk_entry_set_text(data->admin_login_user,"");
        gtk_entry_set_text(data->admin_login_pwd,"");
}

void user_workspace(GtkButton *Button, gpointer user_data){
	p_data *data = user_data;
        
	gtk_widget_hide( GTK_WIDGET(data->user_login) );
	gtk_widget_hide( GTK_WIDGET(data->sign_up));
	gtk_window_present( data->user_workspace);
//        gtk_label_set_text(data->user_profile,data->current_user_email);

}

void popup_for_user(GtkButton *Button, gpointer user_data){
	p_data *data = user_data;
	gtk_widget_hide(GTK_WIDGET(data->user_workspace));
	gtk_window_present(data->popup_for_user);
}

void popup_admin(GtkButton *Button, gpointer user_data){

	p_data *data = user_data;
	gtk_window_present(data->popup_admin);
	gtk_widget_hide(GTK_WIDGET(data->admin_workspace));

}

void window_hide(GtkButton *Button, gpointer user_data){

	p_data *data = user_data;
	gtk_widget_hide( gtk_widget_get_toplevel(GTK_WIDGET(Button)) ) ;
        gtk_label_set_text(data->user_login_error_msg,"");
        gtk_entry_set_text(data->user_login_password,"");
        gtk_entry_set_text(data->user_login_email,"");
        
        gtk_entry_set_text(data->admin_login_pwd,"");
        gtk_entry_set_text(data->admin_login_user,"");
        gtk_label_set_text(data->label_for_admin,"");
        
        gtk_entry_set_text(data->sign_up_fullname,"");
        gtk_entry_set_text(data->sign_up_age,"");
        gtk_entry_set_text(data->sign_up_email,"");
        gtk_entry_set_text(data->sign_up_password,"");
        gtk_entry_set_text(data->sign_up_re_password,"");
        gtk_label_set_text(data->sign_up_error_msg,"");
	
        gtk_window_present(data->start_up_window);
        


}

void user_popup_hide(GtkButton *Button, gpointer user_data){

	p_data *data = user_data;
	gtk_widget_hide( gtk_widget_get_toplevel(GTK_WIDGET(Button)) ) ;
        
	gtk_window_present(data->user_workspace);
        gtk_label_set_text(data->appointment_status,"");
        gtk_label_set_text(data->user_workspace_error_msg,"");
}

void admin_popup_hide(GtkButton *Button, gpointer user_data){

	p_data *data = user_data;
	gtk_widget_hide( gtk_widget_get_toplevel(GTK_WIDGET(Button)) ) ;
	gtk_window_present(data->admin_workspace);
}
//===============================================CHATBOT==================================================================================================
void show_chatbot(GtkButton *Button,gpointer user_data){
    p_data *data = user_data;
    gtk_widget_hide(GTK_WIDGET(data->user_workspace));
    
    gtk_window_present(data->chatbot_window);
}

void hide_chatbot(GtkButton *Button,gpointer user_data){
    p_data *data = user_data;
    gtk_widget_hide(GTK_WIDGET(data->chatbot_window));
    
    gtk_window_present(data->user_workspace);
}

void quit_function(GtkButton *Button,gpointer user_data){  
    char exit[]="espeak ";
    char speak[]="Goodbye";
    strcat(exit,speak);
    system(exit);
    hide_chatbot(Button,user_data);
}
int upper(char string[],int size)
{ int i;
  for(i=0;i<size;i++)
    { string[i]=toupper(string[i]);}

}

int check_input(char data[],gpointer user_data)
{   
    p_data *u_data = user_data;
  char command[]="espeak ";
  char copy[200];
  FILE *fp;
  int flag=1,array_length=0;
  fp=fopen("gchat.txt","r");
   char array[200];
   while(!feof(fp))
  { fgets(array,200,fp);
     if(strncmp(array,data,strlen(data))==0)
     { flag*=0;
        fgets(array,200,fp); 
        array_length=strlen(array);
      	gtk_label_set_text(u_data->chatbot_output,array);
        removespaces(array,array_length);
        strcat(command,array);
        system(command);
	   	
     }

  }
 if(flag==1)
 {
  strcat(command,"I_am_not_intelligent_enough_to_answer_it");
  system(command);
  gtk_label_set_text(u_data->chatbot_output,"I am not intelligent enough to answer it");
  }
  
  fclose(fp);
} 

int removespaces(char string[],int size)
{ int j;
  for(j=0;j<size;j++)
    { if(string[j]==' ')
       { string[j]='_';}
    }
}  

void on_submit_clicked(GtkButton *button,gpointer user_data)
    { 
    
    p_data *data = user_data;
      char exit[]="espeak ";
      int stringlength;
      char string[200];
      //printf("Getting data from the user:\n");
      strcpy(string,gtk_entry_get_text(data->chatbot_entry));
      stringlength=strlen(string);
      upper(string,stringlength);
      if(strcmp(string,"EXIT")==0)
        {  strcat(exit,"Goodbye");
           system(exit);
    	   gtk_label_set_text(data->chatbot_output,"Goodbye");       
           gtk_main_quit();}

      else if(strcmp(string,"")==0)
      {  }

       else
       { check_input(string,user_data);}    
   
       gtk_entry_set_text(data->chatbot_entry,"");

    }

//==========================================================================================================================================================
// Tree functions

void append_item(GtkButton *button, gpointer user_data) {
  
  p_data *u_data = user_data;
  GtkTreeStore *store;
  GtkTreeIter iter;
  char query[500],*avail;
  int temp,i;
    
  
  const gchar *name = gtk_entry_get_text(u_data->admin_tree_entry_name);
  const gchar *start_time = gtk_entry_get_text(u_data->admin_tree_entry_start);
  const gchar *end_time = gtk_entry_get_text(u_data->admin_tree_entry_end);

  if(strcmp(name,"") == 0 || strcmp(start_time,"") == 0 || strcmp(end_time,"") == 0){
      gtk_label_set_text(u_data->invalid_time,"Fields cannot be Empty!!!");
      return;
  }
  if((atoi(start_time))%100 != 0 || (atoi(end_time))%100 != 0 || (atoi(start_time) >2400 || atoi(start_time) <0000 ) || (atoi(start_time) >2400 || atoi(start_time) <0000 )){
      gtk_label_set_text(u_data->invalid_time,"Please Enter Time in 24hrs Format");
        return;
  }
  
  temp = atoi(end_time)/100 - atoi(start_time)/100;
  
  avail = (char*) calloc(temp,sizeof(char));
  for(i = 0; i< temp;i++){
      avail[i] = '0';
  }
  
  

  sprintf(query,"INSERT INTO doctor (name, start_time, end_time, avail) VALUES('%s',%s,%s,'%s')",\
                                        name ,start_time ,end_time, avail);
  free(avail);
  printf("%s",query);
  if(mysql_query(u_data->sql_conn , query)){
    printf("Query failed\n");
    return;
  }

  refersh_list(user_data,0);
  // store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

  // gtk_list_store_append(store, &iter);//acquire an iterator
  // gtk_list_store_set(store, &iter,\
  // 					 DOCTOR_NAME, name,\
  // 					 START_TIME, start_time,\
  // 					 END_TIME, end_time, -1);
  
  gtk_entry_set_text(u_data->admin_tree_entry_name, "");
  gtk_entry_set_text(u_data->admin_tree_entry_start, "");
  gtk_entry_set_text(u_data->admin_tree_entry_end, "");
  gtk_label_set_text(u_data->invalid_time,"");
}

void refersh_list(gpointer user_data,int tree_flag){
  p_data *u_data = user_data;
  GtkTreeStore *store;
  GtkTreeIter iter;
  GtkTreeView *tree;
  if( tree_flag == 0 ){
    tree = u_data->admin_list;
  }
  if( tree_flag == 1 ){
    tree = u_data->user_list;
  }

  MYSQL_RES *res;
  MYSQL_ROW row;

  store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree)));
  gtk_tree_store_clear(store);//to clear tree
  store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree)));
  gtk_tree_store_append(store, &iter, NULL);

  if(mysql_query(u_data->sql_conn,"SELECT * FROM doctor")){
    printf("Query Failed!\n");
    return;
  }

  res = mysql_store_result(u_data->sql_conn);
  while( row = mysql_fetch_row(res)){
    gtk_tree_store_set(store, &iter, DOCTOR_NAME, row[1],\
                                      START_TIME, row[2],\
                                      END_TIME, row[3],\
                                       -1);

    gtk_tree_store_append(store, &iter, NULL);
  }

}

void remove_item(GtkButton *widget, gpointer user_data) {
    
  p_data *u_data = user_data;

  GtkTreeStore *store;
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *query;
  char q[100];



  u_data->admin_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(u_data->admin_list));
  store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(u_data->admin_list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(u_data->admin_list));

  if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(u_data->admin_selection),&model, &iter) == FALSE ){
    return;
  }
  // gtk_tree_selection_get_selected(GTK_TREE_SELECTION(u_data->selection),&model, &iter);

  gtk_tree_model_get(model, &iter, DOCTOR_NAME, &query, -1);
  sprintf(q,"DELETE FROM doctor WHERE name='%s'",query);
  mysql_query(u_data->sql_conn, q);
  refersh_list(user_data,0);
  // refersh_list();
  // if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {//to ckeck whether list is empty
  //     return;
  // }


  // if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(u_data->selection),\ 
  //        &model, &iter)) {
  //   gtk_tree_store_remove(store, &iter);
  // }
}

void remove_all(GtkButton *widget, gpointer user_data) {

  p_data *u_data = user_data;

  GtkTreeStore *store;
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *query;
  char q[100];



  // u_data->admin_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(u_data->admin_list));
  // store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(u_data->admin_list)));
  // model = gtk_tree_view_get_model(GTK_TREE_VIEW(u_data->admin_list));

  // gtk_tree_selection_get_selected(GTK_TREE_SELECTION(u_data->admin_selection),&model, &iter);
  // gtk_tree_selection_get_selected(GTK_TREE_SELECTION(u_data->selection),&model, &iter);

  // gtk_tree_model_get(model, &iter, DOCTOR_NAME, &query, -1);
  // sprintf(q,"DELETE FROM doctor WHERE name='%s'",query);
  if(mysql_query(u_data->sql_conn, "DELETE FROM doctor")){
    fprintf(stderr, "%s\n",mysql_error(u_data->sql_conn) );
  }
  refersh_list(user_data,0);
}

void init_list(GtkTreeView *list) {

  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *column1, *column2, *column3;
  GtkTreeStore       *store;

  store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  renderer = gtk_cell_renderer_text_new();

  column1 = gtk_tree_view_column_new_with_attributes("Doctor Name",\
          renderer, "text", DOCTOR_NAME, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column1);

  renderer = gtk_cell_renderer_text_new();
  column2 = gtk_tree_view_column_new_with_attributes("Start Time",\
          renderer, "text", START_TIME, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column2);

  renderer = gtk_cell_renderer_text_new();
  column3 = gtk_tree_view_column_new_with_attributes("End Time",\
          renderer, "text", END_TIME, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column3);
  


  

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

  g_object_unref(store);
}


void new_user(GtkButton *Button, gpointer user_data){
  p_data *data = user_data;
  char query[350];

  strcpy(payload_text[2],"Subject: Welcome To Hms\r\n");
  strcpy(payload_text[5],"You've successfully created account on HMS.\r\n");

  char *fullname,*age,*sex,*email,*password,*re_password;

  
  
  fullname = (char*) gtk_entry_get_text(data->sign_up_fullname);
  age = (char*) gtk_entry_get_text(data->sign_up_age);
  email = (char*) gtk_entry_get_text(data->sign_up_email);
  password = (char*) gtk_entry_get_text(data->sign_up_password);
  re_password = (char*) gtk_entry_get_text(data->sign_up_re_password);

//  printf("%s %s %s %s %s %c\n",fullname,age,email,password,re_password, data->gender);

  if((strcmp(fullname,"") == 0) || (strcmp(age,"") == 0 )|| (strcmp(email,"") == 0) || (strcmp(password, "") == 0) || (strcmp(re_password, "") == 0)){

      gtk_label_set_text(data->sign_up_error_msg, "Login credentials cannot be EMPTY!!");
      return;
  }

  if(strcmp(password,re_password) != 0){
    gtk_label_set_text(data->sign_up_error_msg, "Passwords do not match!!");
    return;
  }

  if(check_new_user(data->sql_conn,fullname,email) == 1){
    gtk_label_set_text(data->sign_up_error_msg, "Account already exists");
    return;
  }
  
  if(send_email(email) == TRUE){
      
      gtk_label_set_text(data->sign_up_error_msg, "Enter valid email..");
      return;
  }

  sprintf(query,"INSERT INTO user_details(email,password,fullname,age,gender) VALUES('%s','%s','%s',%s,'%c')",email,password,fullname,age,data->gender);

  if(mysql_query(data->sql_conn,query)){
    fprintf(stderr, "%s\n", mysql_error(data->sql_conn));
    return;
  }
  
  gtk_entry_set_text(data->sign_up_fullname,"");
  gtk_entry_set_text(data->sign_up_age,"");
  gtk_entry_set_text(data->sign_up_email,"");
  gtk_entry_set_text(data->sign_up_password,"");
  gtk_entry_set_text(data->sign_up_re_password,"");
  gtk_label_set_text(data->sign_up_error_msg,"");
  
  strcpy(data->current_user_email,email);
  
  user_login(Button, user_data);
}


void gender_male(GtkToggleButton *togglebutton, gpointer user_data){
  p_data *data = user_data;

  data->gender = 'M';
  return;
}

void gender_female(GtkToggleButton *togglebutton, gpointer user_data){
  p_data *data = user_data;

  data->gender = 'F';
  return;
}

void login_user(GtkButton *Button, gpointer user_data){
    
    p_data *data = user_data;
    char *email, *password;
    int num;
    
    email = (char*)gtk_entry_get_text(data->user_login_email);
    password = (char*)gtk_entry_get_text(data->user_login_password);
    
    num = check_user(data->sql_conn, email, password);
    if(num > 0){
        if(num == 2){
            gtk_label_set_text(data->user_login_error_msg, "No Account Found..!");
            return;
        }
        if(num == 1){
            gtk_label_set_text(data->user_login_error_msg, "Incorrect Password..!");
            return;
        }
        
    }
    strcpy(data->current_user_email,email);
    sprintf(payload_text[0],"To: %s \r\n",email);
    gtk_label_set_text(data->user_login_error_msg,"");
    gtk_entry_set_text(data->user_login_password,"");
    gtk_entry_set_text(data->user_login_email,"");
    
    get_user_profile(user_data);
    
    user_workspace(Button, user_data);  
}

void check_appt(GtkButton *Button, gpointer user_data){
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    p_data *data = user_data;
    char *time, query[500],avail_temp[100];
    char email[300];
    int time_int, start_time;
    
    time =(char*) gtk_entry_get_text(data->appointment_time);
    
    if(strcmp(time,"") == 0){
      gtk_label_set_text(data->user_workspace_error_msg,"Fields cannot be Empty!!!");
      return;
    }
    
    if((atoi(time))%100 != 0 || (atoi(time) >2400 || atoi(time) <0000 )){
        
          gtk_label_set_text(data->user_workspace_error_msg,"Please enter time in 24 Hrs Format!!!");
          return;
    }
    time_int = atoi(time)/100;
    
    sprintf(query, "SELECT * FROM doctor WHERE start_time <= %s AND end_time > %s",time,time);
    
    if(mysql_query(data->sql_conn,query)){
        fprintf(stderr,"%s\n",mysql_error(data->sql_conn));
        return;
    }
    
    res = mysql_store_result(data->sql_conn);
    if((int) mysql_num_rows(res) == 0){
        g_print("No appts available\n");
        gtk_label_set_text(data->user_workspace_error_msg,"No Appointments Available !!");
        mysql_free_result(res);
        return;
    }
    
    while(row = mysql_fetch_row(res)){
        int temp;
        sprintf(avail_temp,"%s",row[4]);
        
        start_time = atoi(row[2])/100;
        
        temp = time_int - start_time;
        
        if(avail_temp[temp] == '0'){
            char query_temp[350],temp_msg[300];
            
            avail_temp[temp] = '1';
            sprintf(temp_msg,"Appointment Booked\nname : %s\ntime : %s\r\n",row[1],time);
            strcpy(payload_text[2],"Subject: Appointment Successfully Booked\r\n");
            strcpy(payload_text[5],temp_msg);
            printf("appt booked\n");
            send_email(data->current_user_email);
            popup_for_user(Button,user_data);
            gtk_label_set_text(data->appointment_status,temp_msg);
            printf("%s\n",row[1]);
            
            sprintf(query_temp,"UPDATE doctor SET avail='%s' WHERE name='%s'",avail_temp,row[1]);
            if(mysql_query(data->sql_conn,query_temp)){
                fprintf(stderr,"Query failed : %s\n",mysql_error(data->sql_conn));
                return;
            }
            //popup_for_user(GtkButton *button,gpointer );
            mysql_free_result(res);
            return;
        }
        
        
    }
    
    mysql_free_result(res);
    gtk_label_set_text(data->user_workspace_error_msg,"No Appointments Available");
    
    return;
    
    

}


void get_user_profile(gpointer user_data){
    
    p_data *data = user_data;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[500],u_data[500];
    
    sprintf(query,"SELECT * FROM user_details WHERE email='%s'",data->current_user_email);
    if(mysql_query(data->sql_conn,query)){
        fprintf(stderr,"Query Failed : %s",mysql_error(data->sql_conn));
        return;
    }
    res = mysql_store_result(data->sql_conn);
    row = mysql_fetch_row(res);
    
    sprintf(u_data,"Name : %s\n\nAge : %s\tGender : %s\n\nEmail : %s\n\n",row[2],row[3],row[4],row[0]);
    
    gtk_label_set_text(data->user_profile,u_data);
    mysql_free_result(res);
    
}


/*====================================================================================================================================================*/
//EMAIL

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  data = payload_text[upload_ctx->lines_read];

  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
  }

  return 0;
}

gboolean send_email(char *to){
  
  
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;

  upload_ctx.lines_read = 0;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, "hospitalforpmdsproject");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "hmshmshms");

    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, MY_EMAIL);

    recipients = curl_slist_append(recipients, to);

    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      return TRUE;
    }
    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    /* Always cleanup */
    curl_easy_cleanup(curl);
  }
  
  strcpy(payload_text[5],"\r\n");

//  return (int)res;
  return FALSE;
}

