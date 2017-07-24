/************

	NAME    : VATSAL NAGDA
	ROLL NO : 20162008

**************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


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

int power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result
 
    x = x % p;  // Update x if it is more than or 
                // equal to p
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;  
    }
    return res;
}

int Kab;
char mapping [] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ,.?0123456789!";

void decrypt(char * buffer, char * plaintext){
	int len = (int)strlen(buffer); 

  			for( int i=0;i<len;i++){
				char * e;
				e = strchr(mapping,buffer[i]);
				int index = (int)(e - mapping);
				int final = (index + 41 - Kab)%41;
				plaintext[i] = mapping[final];
			}
			plaintext[len]='\0';
}

void encrypt(char * plaintext, char * ciphertext){
	int len = (int)strlen(plaintext); 
		// printf("%s\t len : %d\n",plaintext,len);

		for(int i=0;i<len;i++)
			plaintext[i] = toupper(plaintext[i]);

		for( int i=0;i<len;i++){
			char * e;
			e = strchr(mapping,plaintext[i]);
			int index = (int)(e - mapping);
			int final = (index + Kab)%41;
			ciphertext[i] = mapping[final];
		}
			ciphertext[len]='\0';
}


void writeToFile(char * plaintext){
	int fd = open("output.txt",'r');

	if(fd)
		remove("output.txt");
	
	fd = open("output.txt", O_CREAT | O_WRONLY,0777);	

	write(fd,plaintext,strlen(plaintext));
	close(fd);

}

void readFile(char * fileName, char * plaintext){

	int fd = open(fileName,'r');
	if(fd < 0){
		printf("ERROR FILE NOT THERE\n");
		_exit(1);
	}

	int n = read(fd,plaintext,256);
	close(fd);
}

void response_cient(int newsockfd,char  *ip){
	int bufsize = 256;
    char buffer[bufsize];
    int num;
   
    pid_t pid = getpid();
    bzero(buffer,bufsize);

     	num = read(newsockfd,buffer,bufsize);
     	if (num < 0){ 
        	perror("ERROR reading from socket\n");//<<endl;
    	}

     	fflush(stdout);
     	//string input(buffer);
     	// printf("serviced by the process : %d\n",pid);
     	// printf("%s\n",buffer);
     	fflush(stdout);

     	char * token;
     	token = strtok(buffer,"#");		//Ya obtained
     	// printf("%s\n",token );
     	int Ya = atoi(token);
     	// printf("Ya : %d\n",Ya );
     	token = strtok(NULL,"#");		//Q obtained
     	int q = atoi(token);
     	// printf("q : %d\n",q );
     	token = strtok(NULL,"#");		//Alpha obtained
     	int Alpha = atoi(token);
     	// printf("Alpha : %d\n",Alpha );
     	
     	srand(time(NULL));
     	int Xb = rand()%q;	
     	int Yb = power(Alpha,Xb,q);
     	// printf("Xb %d\n",Xb );
     	// printf("Yb %d\n",Yb );

     	bzero(buffer,256);
		fflush(stdout);
     	int n = sprintf(buffer,"%d#",Yb);
     	
		int read_len = write(newsockfd,buffer,sizeof(buffer));		// sending the public key 
		bzero(buffer,bufsize);     	

		Kab = power(Ya,Xb,q)%41;
		printf("KEY : %d\n",Kab );

		int choice;

		while(choice){
			// printf("Inside WHILE LOOP\n");
			bzero(buffer,bufsize);
	     	num = read(newsockfd,buffer,bufsize);		//read cipher text
	     	if (num < 0){ 
	        	perror("ERROR reading from socket\n");//<<endl;
	    	}

  			char plaintext[256];
			char ciphertext[256];
  			decrypt(buffer,plaintext);
			printf("plaintext : %s\n", plaintext);

			writeToFile(plaintext);

			//  int choice;
			// printf("TO exit press 0 else 1");
			// scanf(" %d",&choice);
			// switch(choice){												
				
			// 	case 0 :
			// 			_exit(1);
			// }
			// fflush(stdin);

			printf("Enter the FIle NAME\n");
			bzero(plaintext,256);
			bzero(ciphertext,256);
			char fileName [50];
			scanf (" %[^\n]%*c", fileName);
			readFile( fileName, plaintext);

			encrypt(plaintext,ciphertext);
			printf("Cipher : %s\n",ciphertext );

			read_len = write(newsockfd,ciphertext,sizeof(ciphertext));		// sending the public key along with Alpha and q
			if (read_len < 0){ 
		        perror("ERROR writing to socket\n");//<<endl;
		    }

		    // fflush(stdin);
 	    	printf("TO exit press 0 else 1\n");
			scanf("%d",&choice);
			switch(choice){												
				
				case 0 :
						_exit(1);		
			}
			fflush(stdin);
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

			char * ip = inet_ntoa(client_add.sin_addr);

			response_cient(newsockfd,ip);
		}else
		{
			close(newsockfd);
		}	
	}
	close(sockfd);

	return 0;
}