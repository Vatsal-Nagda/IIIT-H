#include <iostream>
#include <sys/types.h>
#include <netinet/.inh>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

using namespace std;

int main(){

	int client,server;
	int port_no = atoi(argv[1]);
	bool ifexists = false;
	int buffsize = 1024;
	char buffer[buffsize];

	struct sockaddr_in server_address;
	socklen_t size;

	client = socket(AF_INET,SOCK_STREAM,0);

	if(client < 0){
		cout << "\nError establishing socket..." << endl;
        exit(1);
	}

	cout<< "Connection established"<< endl;


	sever_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port_no);

	if((bind(client,(struct sockaddr*)&server_addr,sizeof(server_addr))) < 0){
		cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
	}

	size = sizeof(sever_addr);

	listen(client,1);


}