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
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

/*void log_client(string req_type,string ip){					//code to print the client log

	fstream cli_log;
	cli_log.open("client.log",ios::app);
	time_t curr_Time;
	struct tm * loc_time;
	//cout<<"Inside the client log\n";

	time(&curr_Time);
	loc_time = localtime(&curr_Time);

	int Day    = loc_time->tm_mday;
    int Month  = loc_time->tm_mon + 1;
  	int Year   = loc_time->tm_year + 1900;
   	int Hour   = loc_time->tm_hour;
  	int Min    = loc_time->tm_min;
  	int Sec    = loc_time->tm_sec;

  	if(req_type.compare("down_req")==0){
  		cli_log<<Day<<"-"<<Month<<"-"<<Year<<" "<<Hour<<"-"<<Min<<"-"<<Sec<<":"<<"Download request from "<<ip<<endl;
  	}
  	else{
  	  	cli_log<<Day<<"-"<<Month<<"-"<<Year<<" "<<Hour<<"-"<<Min<<"-"<<Sec<<":"<<"File sent to "<<ip<<endl;	
  	}
  	
  	cli_log.close();
}
*/
void bind_sock(int sockfd, struct sockaddr_in server_add,int port_no){				//user defined bind function
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

/*void response_cient(int newsockfd,string ip){
	
	//log_client("down_req",ip);
	cout.flush();
	//cout<<"Down Req";
	int bufsize = 256;
    char buffer[bufsize];//,ch='a';
    int num;
    pid_t pid = getpid();
    //cout <<"Inisde the Download server process :"<<pid<<endl;
    bzero(buffer,bufsize);

    num = read(newsockfd,buffer,bufsize);
    if(num > 0){
    	string req_file(buffer);
    	//cout<<"The path requested is :"<<req_file<<endl;
    	
    	if(access(req_file.c_str(),F_OK) == -1){
    		///file doesnt exist suitable error
		perror("The file you are looking for doesnt exist here.!!\n");//;<<endl;
			//more error handling to come
   		}
    	else{ 
    			//log_client(ip,"done");    
    		//cout<<"Download logging request"<<endl;
    		cout.flush();
    		char buffer_cpy[256];
    		int read_len ;
    		int openfd = open(req_file.c_str(),O_RDONLY);
    		
    		while((read_len = read(openfd,buffer_cpy,256))){
    			write(newsockfd,buffer_cpy,read_len);
    			bzero(buffer_cpy,sizeof(buffer_cpy));
    		}    		
    		//cout<<"Sent for logging\n";
    		close(openfd);
    		}
    	}

    close(newsockfd);
}*/


// void dwnld_server(){					//download server, this handles all the download file requests in the client

// 	int sockfd,newsockfd;
// 	int port_no = 65001;
// 	socklen_t clilen;
// 	struct sockaddr_in server_add,client_add;


// 	sockfd = socket(AF_INET,SOCK_STREAM,0);

// 	if(sockfd < 0){
// 		perror("Error creating the socket");
// 		_exit(1);
// 	}

// 	bind_sock(sockfd,server_add,port_no);

// 	if(listen(sockfd,5) == -1)
// 	{
// 		//cout<<"Marr gya\nListening error";
// 		perror("Listening error\n");
// 		cout.flush();
// 	}

// 	clilen = sizeof(client_add);

// 	while(1){
// 		newsockfd = accept(sockfd, (struct sockaddr *) &client_add,(socklen_t *) &clilen);
		
// 		if (newsockfd < 0) 
// 		{
//         	perror("=> Error on accepting...\n");// << endl;
//         	cout.flush();
//         }
		
// 		pid_t pid = fork();

// 		if(pid == 0){
// 			//child process		
// 			string ip = inet_ntoa(client_add.sin_addr);
// 			//log_client(ip,"done");
// 			/*cout<<"The ip of client is "<<ip<<endl;
// 			cout<<"The pid of the client is: "<<getpid()<<endl;*/
// 			cout.flush();
// 			response_cient(newsockfd,ip);
// 		}else
// 		{
// 			close(newsockfd);
// 		}
// 	}
// 	close(sockfd);

// }

/*void download_file(char *buffer,string file_p){			//this function sends the path name to the download server and recieves data from it

	int sockfd;
	int port_no ;
	struct sockaddr_in server_add;
	struct hostent *server;



	int read_len;
	
	string mirrors(buffer);
	size_t found = mirrors.find("No mirrors available now");

	if((found) == string::npos){

		//cout<<"Inside the mirrors of else\n";
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
		log_client("down_req",ip);

		//cout <<"\nSocket ke pehle\n";
		port_no = 65001;

		sockfd = socket(AF_INET,SOCK_STREAM,0);	

		if (sockfd < 0){
			perror ("Error opening socket\n");
			_exit(1);
		}
		server = gethostbyname(ip.c_str());

		if(server == NULL){
			perror("ERROR, no such host found\n");//<<endl;
			cout.flush();
			exit(0);
		}
		//cout<<"Ip for the download server from file to b dwnloaded is "<<ip<<endl;

	    bzero((char *) &server_add, sizeof(server_add));
	    server_add.sin_family = AF_INET;
	    bcopy((char *)server->h_addr, 
	         (char *)&server_add.sin_addr.s_addr,
	         server->h_length);
	    server_add.sin_port = htons(port_no);

		if(connect(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
			perror("Server offline!  Canonot connect to the server\n");//<< endl;
			cout.flush();
			_exit(1);
		}

		write(sockfd,path.c_str(),path.length());
		//cout<<"path to be sent for retrieval "<<path<<endl;

		 //read_len;
		char buffer1[256];//,ch='a';
		bzero(buffer1,sizeof(buffer1));
		int output_fd = open(file_p.c_str(), O_RDWR | O_CREAT, 0777);  //create file for writing

		while((read_len = read(sockfd,buffer1,256))){
			write(output_fd,buffer1,read_len);
			bzero(buffer1,sizeof(buffer1));
		}

		log_client("done",ip);
		close(output_fd);

		close(sockfd);
	}
	else{
		cout<<mirrors<<endl;
		cout<<"Please choose another option"<<endl;
	}


}
*/
int q,Ya,Alpha;

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

void generate_public_key(char* buffer){
	//get_random_prime()
	q = 97;
	int Xa = rand() % q;
	Alpha=23;
	//Alpha = primitive_root();
	Ya = power(Alpha,Xa,q);

	int n = sprintf(buffer,"%d#%d#%d",Ya,q,Alpha);
}

int main(int argc,char *argv[]){
	int sockfd;
	int port_no ;
	struct sockaddr_in server_add;

	int read_len;
	char buffer[256];

	if (argc < 3){
		printf("Use it as %s hostname port",argv[0]);
		_exit(1);
	}
	port_no = atoi(argv[2]);

	sockfd = socket(AF_INET,SOCK_STREAM,0);	

	if (sockfd < 0){
		perror("Error opening socket\n");
		_exit(1);
	}

	bzero((char *)&server_add,sizeof(server_add));

	server_add.sin_family = AF_INET;
	server_add.sin_addr.s_addr = inet_addr(argv[1]);
	server_add.sin_port = htons(port_no);

	if(connect(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		perror("Error Connecting to the server");
		_exit(1);
	}

	bzero(buffer,256);
	fflush(stdout);

	generate_public_key(buffer);						//generating the public key of A
	read_len = write(sockfd,buffer,sizeof(buffer));		// sending the public key along with Alpha and q
	if (read_len < 0){ 
        perror("ERROR writing to socket\n");//<<endl;
    }

    bzero(buffer,256);
	read_len = read(sockfd,buffer,sizeof(buffer));		//reading the public key of B
	
	if (read_len < 0){ 
        perror("ERROR reading from socket\n");//<<endl;
    }
    fflush(stdout);

	while(1){

		bzero(buffer,256);
		fflush(stdout);
		//cout <<"\nPlease enter some text  to be sent : ";//
		//read_len = read(STDIN_FILENO,buffer,6);
		
		printf("Choose\n");
		printf("1.Send\n2.Share\n3.Exit\n");
		int choice;
		scanf("%d",&choice);
		switch(choice){												
			case 1 :																	//logic if search request comes
					/*cout<<"Type a string to search :";
					cin >>buffer;
					file_p = buffer;
					strcat(srch,buffer);
					strcpy(buffer,srch);*/
					read_len = write(sockfd,buffer,sizeof(buffer));
					if (read_len < 0){ 
			            perror("ERROR writing to socket\n");//<<endl;
			        }

					bzero(buffer,256);
					read_len = read(sockfd,buffer,sizeof(buffer));
					
					if (read_len < 0){ 
			            perror("ERROR reading from socket\n");//<<endl;
			        }
			        fflush(stdout);
					//cout <<"\n"<<buffer<<endl;
					//cout<<"Aagya bhai main yahan\n";
					// download_file(buffer,file_p);
					break;

			case 2 :																//logic if share request comes
					/*cout<<"Path :";
					cin >>buffer;
					strcat(share,buffer);
					strcpy(buffer,share);*/
					read_len = write(sockfd,buffer,sizeof(buffer));

					if (read_len < 0){ 
			            perror("ERROR writing to socket\n");//<<endl;
			        }

					bzero(buffer,256);
					read_len = read(sockfd,buffer,sizeof(buffer));
					
					if (read_len < 0){ 
			            perror("ERROR reading from socket\n");//<<endl;
			        }
			        fflush(stdout);
					//cout <<"\nThe message is :"<<buffer<<endl;
					break;

			case 3 :
					_exit(1);

			default: printf("Please enter a valid option\n");
		}
		///fgets(buffer,255,stdin);

		//read_len = write(sockfd,str,sizeof(str));
	}


	return 0;
}