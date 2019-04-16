#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "struct.h"

// char *message;
void create_table(MYSQL *conn,char *details){

	char query[600];
	sprintf(query,"CREATE TABLE IF NOT EXISTS %s",details);
	if(mysql_query(conn,query)){
		printf("Query failed : %s\n",mysql_error(conn));
		return;
	}

	printf("%ld rows affected\nTable created\n\n",(long ) mysql_affected_rows(conn));
	// example : 
	// create_table(connection,"name_1(id int(3) not null auto_increment primary key,name text not null)");
}

char* show_details(MYSQL *conn,int print_on_terminal,char *t_name){

	int num;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *buffer = (char*) calloc(300 ,sizeof(char));
	char temp[10];
	if(t_name != NULL){
		char query[50];
		sprintf(query, "SELECT * FROM %s",t_name);
		mysql_query(conn,query);
	}


	res = mysql_store_result(conn);
	num = (int) mysql_field_count(conn);
	
	while(row = mysql_fetch_row(res)){
		for(int i=0;i<num;i++){
			sprintf(temp,"%s\t",row[i]);
			strcat(buffer,temp);
		}
		strcat(buffer,"\n");
	}

	if(print_on_terminal)
		printf("%s\n", buffer);


	mysql_free_result(res);
	return buffer;
}

void update(MYSQL *conn,char *t_name,char *from,char *to){

	char query[200];
	sprintf(query,"UPDATE %s SET %s WHERE %s",t_name,to,from);
	if(mysql_query(conn,query)){
		fprintf(stderr, "Failed to update!\n");
		return;
	}

	printf("%ld rows are affected\n",(long) mysql_affected_rows(conn));

}

void add_data(MYSQL *conn,char *t_name,char *params,char *values){

	char query[200];
	sprintf(query,"INSERT INTO %s(%s) VALUES(%s)",t_name,params,values);
	if(mysql_query(conn,query)){
		printf("Row insertion failed!\n");
		return;
	}
	printf("%ld rows are affected\n\n",(long) mysql_affected_rows(conn));
}

int table_exist(MYSQL *conn,char *t_name){
	MYSQL_RES *res;
	char query[50];
	sprintf(query,"SHOW TABLES LIKE '%s'",t_name);
	mysql_query(conn,query);
	res = mysql_store_result(conn);
	if(mysql_num_rows(res)==0)
		return 0;
	return 1;
}

int create_database(MYSQL *conn,char *name){

	char query_1[50],query_3[50] = "USE ";
	MYSQL_RES *res;

	sprintf(query_1,"CREATE DATABASE IF NOT EXISTS %s",name);

	if(mysql_query(conn, query_1)){
		fprintf(stderr, "Query failed\n");
		return 1;
	}

	
	strcat(query_3,name);
	if(mysql_query(conn,query_3)){
		fprintf(stderr, "Changing Database %s to current failed!\n",name);
		return 1;
	}
	

	return 0;
}

int check_new_user(MYSQL *conn, char *fullname, char *email){
	MYSQL_RES *res;
	char query[500],*temp;
        int num;
	sprintf(query,"SELECT email,fullname FROM user_details WHERE email='%s' OR  fullname='%s'",email,fullname);
        temp = query;
	if(mysql_query(conn,query)){
		fprintf(stderr, "%s\n",mysql_error(conn));
		return -1;
	}
        
	res = mysql_store_result(conn);
        num =  mysql_num_rows(res);
	if( num > 0 ){
		mysql_free_result(res);
		return 1;//account dosen't exist so create new account
	}

	mysql_free_result(res);
	return 0;//account exits so don't create new account
}

int check_user(MYSQL *conn, char *email, char *password){
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[500],*temp = password;
    
    sprintf(query,"SELECT password FROM user_details WHERE email='%s'",email);
    if(mysql_query(conn,query)){
        fprintf(stderr,"%s\n",mysql_error(conn));
        return -1;
    }
    
    res = mysql_store_result(conn);
    if(mysql_num_rows(res) == 0){
        mysql_free_result(res);
        return 2;
    }

    row = mysql_fetch_row(res);
    
    if(strcmp(row[0],temp) == 0){
        mysql_free_result(res);
        return 0;
    }
    
    mysql_free_result(res);
    return 1;
}

