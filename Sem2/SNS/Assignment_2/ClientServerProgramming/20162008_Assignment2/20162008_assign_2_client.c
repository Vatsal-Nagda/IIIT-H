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
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#define true 1
#define false 0
char mapping [] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ,.?0123456789!";
int Kab;


void bind_sock(int sockfd, struct sockaddr_in server_add,int port_no){				//user defined bind function
	bzero((char *)&server_add,sizeof(server_add));
	
	server_add.sin_family = AF_INET;
	server_add.sin_port = htons(port_no);
	server_add.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		port_no+=1;
		bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add));

		 //cout << "=> Error binding connection, the socket has already been established..." << endl;
		fflush(stdout);
        //return 0;
	}
}

int q,Xa,Ya,Alpha;

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


int primitive_root(int p){
	int n = p-1, index = 0, i, j;
	int s = p-1;
	int prime_factors[100];

	while (n%2 == 0)
	{
		n = n/2;
		prime_factors[index++] = 2;
	}

	for (i = 3; i*i <= n; i = i+2)
	{
		// While i divides n, print i and divide n
		while (n%i == 0)
		{
			prime_factors[index++] = i;
			n = n/i;
		}
	}

	if (n > 2)
		prime_factors[index++] = n;

	for(j=2; j<p; j++){
		int flag = 0;
		int prev = 0;

		for(i=0; i<index; i++){
			int factor = prime_factors[i];

			if(factor == prev){
				continue;
			}

			int pwr = s/factor;
			int res = power(j, pwr, p);

			if(res == 1){
				flag = 1;
				break;
			}

			prev = factor;
		}

		if(!flag){
			return j;	
		}
	}
}


int miillerTest(int d, int n)
{
    int a = 2 + rand() % (n - 4);
    int x = power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;

    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
    return false;
}

int isPrime(int n, int k)
{
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    for (int i = 0; i < k; i++)
         if (miillerTest(d, n) == false)
              return false;
    return true;
}

int get_random_prime(){
	while (true){
		int x = rand()%1000;
		if(isPrime(x,10) == true){
			return x;
		}
	}
}

void encrypt(char * plaintext, char * ciphertext){
	int len = (int)strlen(plaintext); 
		printf("%s\t len : %d\n",plaintext,len);

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

void decrypt(char * buffer, char * plaintext){
	int len = (int)strlen(buffer); 

			for( int i=0;i<len;i++){
				char * e;
				e = strchr(mapping,buffer[i]);
				int index = (int)(e - mapping);
				int final = (index + 41 - Kab)%41;
				plaintext[i] = mapping[final];
			}
}

void generate_public_key(char* buffer){
	q = get_random_prime();
	// q = 97;
	Xa = rand() % q;
	// Alpha=23;
	Alpha = primitive_root(q);
	Ya = power(Alpha,Xa,q);

	// printf("q : %d\n",q );
	// printf("Xa : %d\n",Xa);
	// printf("Ya : %d\n",Ya);

	int n = sprintf(buffer,"%d#%d#%d",Ya,q,Alpha);
}



void writeToFile(char * plaintext){
	int fd = open("output.txt", O_CREAT | O_WRONLY,0777);

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

int main(int argc,char *argv[]){
	srand(time(NULL));
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
	// printf("obtained from server : %s\n",buffer);

   	char * token;
   	token = strtok(buffer,"#");		//Ya obtained
	int Yb = atoi(token);
    // printf("Yb : %d\n",Yb ); 
	Kab = power(Yb,Xa,q) % 41 ;
	printf("KEY : %d\n",Kab );

	if (read_len < 0){ 
        perror("ERROR reading from socket\n");//<<endl;
    }
    fflush(stdout);

    int choice;
	while(choice){

		bzero(buffer,256);
		fflush(stdout);
		//cout <<"\nPlease enter some text  to be sent : ";//
		//read_len = read(STDIN_FILENO,buffer,6);
		
		printf("Enter the FIle NAME\n");
		char fileName[50];		
		char plaintext[256];
		char ciphertext[256];
		bzero(plaintext,256);
		bzero(ciphertext,256);

		scanf (" %[^\n]%*c", fileName);
		readFile( fileName, plaintext);

		int len = (int)strlen(plaintext); 
		printf("%s\t len : %d\n",plaintext,len);

		encrypt(plaintext,ciphertext);
		printf("Cipher : %s\n",ciphertext );

		read_len = write(sockfd,ciphertext,sizeof(ciphertext));		// sending the public key along with Alpha and q
		if (read_len < 0){ 
	        perror("ERROR writing to socket\n");//<<endl;
	    }

	 //    int choice;
		// printf("TO exit press 0 else 1");
		// scanf(" %d",&choice);
		// switch(choice){												
			
		// 	case 0 :
		// 			_exit(1);
		// }
		// fflush(stdin);

    	bzero(buffer,256);
     	read_len = read(sockfd,buffer,sizeof(buffer));		//read cipher text
     	if (read_len < 0){ 
        	perror("ERROR reading from socket\n");//<<endl;
    	}

			// char plaintext[256];
			// char ciphertext[256];
    		bzero(plaintext,256);
			bzero(ciphertext,256);

			decrypt(buffer,plaintext);

		printf("plaintext : %s\n", plaintext);


			writeToFile(plaintext);

		
		printf("TO exit press 0 else 1\n");
		scanf("%d",&choice);
		switch(choice){												
			
			case 0 :
					_exit(1);		
		}
		fflush(stdin);
		///fgets(buffer,255,stdin);

		//read_len = write(sockfd,str,sizeof(str));
	}


	return 0;
}