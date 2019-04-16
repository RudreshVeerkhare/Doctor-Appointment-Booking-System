
CC = gcc

CFLAGS = -c -g

libs_gtk = `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` -lcurl

libs_sql = `mysql_config --libs --cflags`

all : compile

compile : main.o sql_func.o gtk_func.o
	$(CC) main.o sql_func.o gtk_func.o -o Hospital\ Management\ System $(libs_sql) $(libs_gtk) -rdynamic && ./Hospital\ Management\ System && make clean

main.o : main.c
	$(CC) $(CFLAGS) main.c $(libs_sql) $(libs_gtk)

sql_func.o : sql_func.c
	$(CC) $(CFLAGS) sql_func.c $(libs_sql) $(libs_gtk)

gtk_func.o : gtk_func.c
	$(CC) $(CFLAGS) gtk_func.c $(libs_gtk) $(libs_sql)

install :
	sudo apt-get install mysql-server && sudo apt-get install gtk+3.0 && sudo apt-get install libcurl4-openssl-dev && sudo apt-get install espeak

debug : compile_debug

compile_debug : main.o sql_func.o gtk_func.o
	$(CC) main.o sql_func.o gtk_func.o -o hello $(libs_sql) $(libs_gtk) -rdynamic && gdb hello && make clean
	
clean :
	rm -rf *.o hello