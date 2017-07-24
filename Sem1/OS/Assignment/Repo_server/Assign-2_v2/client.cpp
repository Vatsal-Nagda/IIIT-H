#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <sstream>

using namespace std;

void bind_sock(int sockfd, struct sockaddr_in server_add,int port_no){
	bzero((char *)&server_add,sizeof(server_add));
	
	server_add.sin_family = AF_INET;
	server_add.sin_port = htons(port_no);
	server_add.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		port_no+=1;
		bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add));

		 //cout << "=> Error binding connection, the socket has already been established..." << endl;
		 cout.flush();
        //return 0;
	}
}

void response_cient(int newsockfd,string ip){
	
	int bufsize = 256;
    char buffer[bufsize];//,ch='a';
    int num;
    pid_t pid = getpid();
    cout <<"Inisde the Download server process :"<<pid<<endl;
    bzero(buffer,bufsize);

    num = read(newsockfd,buffer,bufsize);
    if(num > 0){
    	string req_file(buffer);
    	cout<<"The path requested is :"<<req_file<<endl;
    	
    	if(access(req_file.c_str(),F_OK) == -1){
    		///file doesnt exist suitable error
		cout <<"The file you are looking for doesnt exist here.!!"<<endl;
			//more error handling to come
   		}
    	else{
    		char cpy[256];
    		fstream file_out ;
    		string line;
    		file_out.open(req_file.c_str(),ios::in)	;
    		cout<<"Printing the file"<<endl;
    		while(getline(file_out,line)){
    			/*if(file_out.eof()) break;*/
    			line = line+"\n";
    			send(newsockfd,line.c_str(),strlen(line.c_str()),0);
    			line ="";
    			/*write(newsockfd,cpy,strlen(cpy));
    			bzero(cpy,256);*/
    			//read(newsockfd,&ch,1);
    			//cout<<line<<endl;
    		}
    		//write(newsockfd,"exit",strlen("exit"));
    	}
    }

    close(newsockfd);

}


void dwnld_server(){

	int sockfd,newsockfd;
	int port_no = 65001;
	socklen_t clilen;
	struct sockaddr_in server_add,client_add;


	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd < 0){
		cout << "Error creating the socket";
		_exit(1);
	}

	bind_sock(sockfd,server_add,port_no);

	if(listen(sockfd,5) == -1)
	{
		cout<<"Marr gya\nListening error";
		cout.flush();
	}

	clilen = sizeof(client_add);

	while(1){
		newsockfd = accept(sockfd, (struct sockaddr *) &client_add,(socklen_t *) &clilen);
		
		if (newsockfd < 0) 
		{
        	cout << "=> Error on accepting..." << endl;
        	cout.flush();
        }
		
		pid_t pid = fork();

		if(pid == 0){
			//child process		
			string ip = inet_ntoa(client_add.sin_addr);
			cout<<"The ip of client is "<<ip<<endl;
			cout<<"The pid of the client is: "<<getpid()<<endl;
			cout.flush();
			response_cient(newsockfd,ip);
		}else
		{
			close(newsockfd);
		}
	}
	close(sockfd);

}

void download_file(char *buffer,string file_p){

	int sockfd;
	int port_no ;
	struct sockaddr_in server_add;
	struct hostent *server;


	int read_len;
	
	string mirrors(buffer);
	cout <<"Select amongst the mirrors"	<<endl;
	int choice;
	cout<<mirrors<<endl;
	cin >>choice;

	istringstream options(mirrors);
	string ans;
	int i=1;
	while(getline(options,ans)){
		
		if( i == choice){
			cout << ans<<endl;
			break;
		}
		i++;
	}

	istringstream opt(ans);

	string path;
	string ip;

	opt >>ip;
	opt >>ip;
	opt >> path;

	cout<<ip<<" 	"<<path<<endl;

	cout <<"\nSocket ke pehle\n";
	port_no = 65001;

	sockfd = socket(AF_INET,SOCK_STREAM,0);	

	if (sockfd < 0){
		cout <<"Error opening socket";
		_exit(1);
	}
	server = gethostbyname(ip.c_str());

	if(server == NULL){
		cout<<"ERROR, no such host found"<<endl;
		cout.flush();
		exit(0);
	}
	cout<<"Ip for the download server from file to b dwnloaded is "<<ip<<endl;

    bzero((char *) &server_add, sizeof(server_add));
    server_add.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&server_add.sin_addr.s_addr,
         server->h_length);
    server_add.sin_port = htons(port_no);

	if(connect(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		cout <<"Error Connecting"<< endl;
		cout.flush();
		_exit(1);
	}

	write(sockfd,path.c_str(),path.length());
	//cout<<"path to be sent for retrieval "<<path<<endl;

	 //read_len;
	char buffer1[256];//,ch='a';
	bzero(buffer1,sizeof(buffer1));

	fstream opFile;
	opFile.open(file_p.c_str(),ios::in|ios::app);
	
	while(read(sockfd,buffer1,sizeof(buffer1))){
		
		opFile<<buffer1;
		memset(buffer1,'\0',sizeof(buffer1));
		//cout<<buffer1;
		//write(sockfd,&ch,1);
	}

	close(sockfd);
}



int main(int argc,char *argv[]){
	int sockfd;
	int port_no ;
	struct sockaddr_in server_add;

	int read_len;
	char buffer[256];

	if (argc < 3){
		cout <<"Use it as "<< argv[0] <<" hostname port"<< endl;
		_exit(1);
	}
	port_no = atoi(argv[2]);

	sockfd = socket(AF_INET,SOCK_STREAM,0);	

	if (sockfd < 0){
		cout <<"Error opening socket";
		_exit(1);
	}

	bzero((char *)&server_add,sizeof(server_add));

	server_add.sin_family = AF_INET;
	server_add.sin_addr.s_addr = inet_addr(argv[1]);
	server_add.sin_port = htons(port_no);

	if(connect(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		cout <<"Error Connecting"<< endl;
		_exit(1);
	}

	pid_t pid = fork();

	if(pid ==0 ){
		//download server
		dwnld_server();
	}

	while(1){

		bzero(buffer,256);
		fflush(stdout);
		//cout <<"\nPlease enter some text  to be sent : ";//
		//read_len = read(STDIN_FILENO,buffer,6);
		char srch [256] = "search#121#";
		char share [256] = "share#121#";
		string file_p;

		cout<<"Select :"<<endl;
		cout<<"1.Search\n2.Share\n3.Exit\n";
		int choice;
		cin >> choice;
		switch(choice){
			case 1 :
					cout<<"Type a string to search :";
					cin >>buffer;
					file_p = buffer;
					strcat(srch,buffer);
					strcpy(buffer,srch);
					read_len = write(sockfd,buffer,sizeof(buffer));
					if (read_len < 0){ 
			            cout <<"ERROR writing to socket"<<endl;
			        }

					bzero(buffer,256);
					read_len = read(sockfd,buffer,sizeof(buffer));
					
					if (read_len < 0){ 
			            cout <<"ERROR reading from socket"<<endl;
			        }
			        fflush(stdout);
					//cout <<"\n"<<buffer<<endl;
					cout<<"Aagya bhai main yahan\n";
					download_file(buffer,file_p);
					break;

			case 2 :
					cout<<"Path :";
					cin >>buffer;
					strcat(share,buffer);
					strcpy(buffer,share);
					read_len = write(sockfd,buffer,sizeof(buffer));

					if (read_len < 0){ 
			            cout <<"ERROR writing to socket"<<endl;
			        }

					bzero(buffer,256);
					read_len = read(sockfd,buffer,sizeof(buffer));
					
					if (read_len < 0){ 
			            cout <<"ERROR reading from socket"<<endl;
			        }
			        fflush(stdout);
					//cout <<"\nThe message is :"<<buffer<<endl;
					break;

			case 3 :
					_exit(1);
		}
		///fgets(buffer,255,stdin);

		//read_len = write(sockfd,str,sizeof(str));
	}


	return 0;
}