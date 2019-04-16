#ifndef _FUNC_DECL_H_
#define _FUNC_DECL_H_

void show_data(GtkButton *Button, gpointer user_data);

void book_again(GtkButton *Button, gpointer user_data);

void create_table(MYSQL *conn,char *details);

char* show_details(MYSQL *conn,int print_on_terminal,char *t_name);

void update(MYSQL *conn,char *t_name,char *from,char *to);

void add_data(MYSQL *conn,char *t_name,char *params,char *values);

int table_exist(MYSQL *conn,char *t_name);

int create_database(MYSQL *conn,char *name);

void append_item(GtkButton *button, gpointer user_data);

void refersh_list(gpointer user_data, int tree_flag);

void remove_item(GtkButton *widget, gpointer user_data);

void remove_all(GtkButton *widget, gpointer user_data);

void init_list(GtkTreeView *list);

int check_new_user(MYSQL *conn, char *fullname, char *email);

void new_user(GtkButton *Button, gpointer user_data);

int check_user(MYSQL *conn, char *email, char *password);

gboolean send_email(char *to);

void get_user_profile(gpointer user_data);

int upper(char string[],int size);

int removespaces(char string[],int size);

int check_input(char data[],gpointer user_data);

void hide_chatbot(GtkButton *Button,gpointer user_data);


#endif