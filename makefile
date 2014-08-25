all: lab9_pipe.c
	gcc -o lab9_pipe lab9_pipe.c
	gcc -o test_socket test_socket.c
	gcc -o my_echo_server my_echo_server.c 
	gcc -o my_client my_client.c
	gcc -o server server.c -lnsl
	gcc -o string_client string_client.c -lnsl
clean: 
	rm lab9_pipe.c
