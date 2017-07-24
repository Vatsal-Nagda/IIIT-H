/************

	NAME    : VATSAL NAGDA
	ROLL NO : 20162008

**************/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctime>

void bind_sock(int sockfd, struct sockaddr_in server_add,int port_no){
	bzero((char *)&server_add,sizeof(server_add));
	
	server_add.sin_family = AF_INET;
	server_add.sin_port = htons(port_no);
	server_add.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		
		 perror("=> Error binding connection, the socket has already been established...\n");// << endl;
        //return 0;
	}
}

void response_cient(int newsockfd,string ip){
	int bufsize = 256;
    char buffer[bufsize];
    int num;
   
    pid_t pid = getpid();
    bzero(buffer,bufsize);

     while((num = read(newsockfd,buffer,bufsize)) > 0){

     	fflush(stdout);
     	//string input(buffer);
     	printf("serviced by the process : %d\n",pid);
     	printf("%s\n",buffer);
     	fflush(stdout);
     	
     	if(input.find("search#121#") != string::npos){
     		// repo_search(newsockfd,input,ip);
     		cout.flush();
     		//write(newsockfd,"\n Your Search Request\n",22);
     	}	
     	else if(input.find("share#121#") != string::npos){
     		// repo_share(newsockfd,input,ip);
     		cout.flush();
     		//write(newsockfd,"\n Your Share Request\n",21);
     	}
     	else{
     		//cout<<"\nThe message received is :\n"<<buffer<<endl;
     		cout.flush();
     		//write(newsockfd,"\nGot your normal message\n",25);
     	}

		bzero(buffer,bufsize);     	
     }
     close(newsockfd);
     exit(0);
}




int main(int argc, char* argv[]){

	int sockfd,newsockfd;
	int port_no = atoi(argv[1]);
	socklen_t clilen;
	struct sockaddr_in server_add,client_add;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd < 0){
		perror("Error creating the socket\n");
		_exit(1);
	}

	bind_sock(sockfd,server_add,port_no);

	listen(sockfd,5);

	clilen = sizeof(client_add);

	while(1){
		newsockfd = accept(sockfd, (struct sockaddr *) &client_add,(socklen_t *) &clilen);
		
		// 	repo_load();

		if (newsockfd < 0) 
        	perror("=> Error on accepting...\n");// << endl;
		
		pid_t pid = fork();

		if(pid == 0){

			string ip = inet_ntoa(client_add.sin_addr);

			response_cient(newsockfd,ip);
		}else
		{
			close(newsockfd);
		}
	}
	close(sockfd);

	return 0;
}