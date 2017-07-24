#include <sys/types.h>          
#include <sys/socket.h>
#include <iostream>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <sstream>
#include "ip-test.cpp"
#include "hash.cpp"
#include <map>
//#include "structure.cpp"

using namespace std;

//int RoutingTable[8][4];
//int createRoutingTable[8][4];
//int LeftLeafSet[2];
//int RightLeafSet[2];
string server_ip = "";
char nodeId[9] = "";

struct packet{
	char ip[20];
	int port;
	char nodeid[9];
};

struct packet node;
struct packet next_hop;
struct packet LeftLeafSet[2];
struct packet RightLeafSet[2];
struct packet RoutingTable[8][4];
int leftLeafCnt,rightLeafCnt;
char client_ip[20];
char client_port[10];
char clientId[9];
bool hop=false;
bool leftSet=true;
bool inLeafSet=false;
bool routingForward=false;
int server_portno=20000;
int rowF,colF;
map <string,string> DHT;
//struct packet createRoutingTable[8][4];

int create_socket(){
	int option = 1;
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));	//Reuse socket address without waiting for address to get free
	if(sockfd<0){
		cout<<"Error opening socket\n";
		return -1;
	}
	return sockfd;
}

int bind(int sockfd, int portno,struct sockaddr_in server_addr){
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		//cout<<"Error binding\n";
		return -1;
	}
	return 0;
}


void print_route(){
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++){
			printf("%10s",RoutingTable[i][j].nodeid);
		}
		cout<<"\n";
	}
}


void sendTableEntries(int sockfd,char recvBuff[]){
	hop=false;
	char sendBuff[100],ch='a';
	int i,j;
	for(i=0;i<8;i++){
		if(nodeId[i]!=clientId[i])
			break;
	}
	int col = clientId[i] - '0';
	//cout<<"IN send table entries "<<i<<" "<<col<<endl;
	//cout<<"nodeid : "<<nodeId<<" cliend id : "<<clientId<<endl;
	int diff = abs(atoi(nodeId) - atoi(clientId));

	for(int j=0;j<4;j++){
		memset(sendBuff,'\0',sizeof(sendBuff));
		strcpy(sendBuff,RoutingTable[i][j].ip);
		strcat(sendBuff," ");
		ostringstream ss;
		ss << RoutingTable[i][j].port;
		strcat(sendBuff,ss.str().c_str());
		strcat(sendBuff," ");
		strcat(sendBuff,RoutingTable[i][j].nodeid);
		if(strlen(sendBuff)==0)
			strcpy(sendBuff,"---");
		write(sockfd,sendBuff,strlen(sendBuff));
		read(sockfd,&ch,1);
		//cout<<"write : "<<sendBuff<<endl;
	}
	if(strlen(RoutingTable[i][col].nodeid)==8 && diff>(abs(atoi(nodeId) - atoi(RoutingTable[i][col].nodeid)))){
		memset(next_hop.ip,'\0',sizeof(next_hop.ip));
		strcpy(next_hop.ip,RoutingTable[i][col].ip);
		memset(next_hop.nodeid,'\0',sizeof(next_hop.nodeid));
		strcpy(next_hop.nodeid,RoutingTable[i][col].nodeid);
		next_hop.port = RoutingTable[i][col].port;
		hop=true;
	}
	else{
	//******************Inserting join node into RoutingTable*************************
		memset(RoutingTable[i][col].ip,'\0',sizeof(RoutingTable[i][col].ip));
		strcpy(RoutingTable[i][col].ip,client_ip);
		RoutingTable[i][col].port = atoi(client_port);
		memset(RoutingTable[i][col].nodeid,'\0',sizeof(RoutingTable[i][col].nodeid));
		strcpy(RoutingTable[i][col].nodeid,clientId);
	//********************************************************************************
	}
	//print_route();
}

void checkInLeafSet(char recvBuff[],bool add=true){
	leftSet=true;
	inLeafSet=false;
	int check_id;
	int i=0,k=0;
	struct packet received_packet;
	//cout<<"in leaf set : "<<recvBuff<<endl;
	//cout<<"in leaf set : "<<recvBuff<<endl;
	if(add){
		memset(client_ip,'\0',sizeof(client_ip));
		memset(client_port,'\0',sizeof(client_port));
		memset(clientId,'\0',sizeof(clientId));
		while(recvBuff[i]!=' ')
			client_ip[k++] = recvBuff[i++];
		i++;
		k=0;
		while(recvBuff[i]!=' ')
			client_port[k++] = recvBuff[i++];
		i++;
		k=0;
		while(recvBuff[i]!='\0')
			clientId[k++] = recvBuff[i++];
		check_id = atoi(clientId);
		strcpy(received_packet.ip,client_ip);
		strcpy(received_packet.nodeid,clientId);
		received_packet.port = atoi(client_port);
	}
	else{
		check_id = atoi(recvBuff);
	}
	//Create received packet
	if (check_id>atoi(node.nodeid))
		leftSet=false;
	if(leftSet){
		for(i=0;i<2;i++){
			if(atoi(LeftLeafSet[i].nodeid)==check_id){
				inLeafSet=true;
			}
		}
	}
	else{
		for(i=0;i<2;i++){
			if(atoi(RightLeafSet[i].nodeid)==check_id){
				inLeafSet=true;
			}
		}	
	}
	if(add){
		//cout<<"Add in leaf set : "<<received_packet.nodeid;
		bool added=false;
		if(leftSet){
			if(strlen(LeftLeafSet[0].nodeid)==8 && strlen(LeftLeafSet[1].nodeid)==8){
				for(i=0;i<2;i++){
					if(strlen(LeftLeafSet[i].nodeid)==8){
						if( (atoi(node.nodeid)-atoi(LeftLeafSet[i].nodeid)) > (atoi(node.nodeid)-atoi(received_packet.nodeid)) ){
							LeftLeafSet[i] = received_packet;
							break;
						}
					}
				}
			}
			else{
				if(strlen(LeftLeafSet[0].nodeid)!=8)
					LeftLeafSet[0] = received_packet;
				else if(strlen(LeftLeafSet[1].nodeid)!=8)
					LeftLeafSet[1] = received_packet;
			}
		}
		else if(!leftSet){
			if(strlen(RightLeafSet[0].nodeid)==8 && strlen(RightLeafSet[1].nodeid)==8){
				for(i=0;i<2;i++){
					if(strlen(RightLeafSet[i].nodeid)==8){
						if( (atoi(RightLeafSet[i].nodeid) - atoi(node.nodeid)) > (atoi(received_packet.nodeid)-atoi(node.nodeid)) ){
							RightLeafSet[i] = received_packet;
							break;
						}
					}
				}
			}
			else{
				if(strlen(RightLeafSet[0].nodeid)!=8)
					RightLeafSet[0] = received_packet;
				else if(strlen(RightLeafSet[1].nodeid)!=8)
					RightLeafSet[1] = received_packet;
			}
		}
	}
}

int connect_to_next_hop(char ip[],int portno){
	int sockfd,n;
	struct sockaddr_in server_addr;
	sockfd = create_socket();		
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(portno);
	if(sockfd<0){
		cout<<"socket error in connect_to_next_hop\n";
		return -1;
	}
	//cout<<"socket success for connect_to_next_hop\n";
	n = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(n<0){
		cout<<"Connection error\n";
		return -1;
	}
	return sockfd;
}

void checkInRoutingTable(char hash[]){
	int row=0,col=0;
	routingForward = false;
	for(row=0;row<8;row++){
		if(nodeId[row]!=hash[row])
			break;
	}
	col = hash[row] - '0';
	/*cout<<"In chkInRoutingTable"<<endl;
	cout<<row<<" "<<col<<endl;
	cout<<"nodeId : "<<nodeId<<" hash : "<<hash<<endl;*/
	if(strlen(RoutingTable[row][col].nodeid)==8 && strcmp(RoutingTable[row][col].nodeid,node.nodeid)!=0){
		routingForward = true;
		rowF = row;
		colF = col;
	}
}

void response_join(int newsockfd,char recvBuff[]){
	char sendBuff[100];
	checkInLeafSet(recvBuff);
	sendTableEntries(newsockfd,recvBuff);
	memset(sendBuff,'\0',sizeof(sendBuff));
	if(hop){
		//Copy hop node data
		ostringstream ss;
		ss<<next_hop.port;
		strcpy(sendBuff,next_hop.ip);
		strcat(sendBuff," ");
		strcat(sendBuff,ss.str().c_str());
		strcat(sendBuff," ");
		strcat(sendBuff,next_hop.nodeid);
		//cout<<"hopping"<<endl;
		hop=false;
		write(newsockfd,sendBuff,strlen(sendBuff));
	}
	else{
		strcpy(sendBuff,"noHop");
		write(newsockfd,sendBuff,strlen(sendBuff));
		//send leaf set
		int i=0;
		memset(sendBuff,'\0',sizeof(sendBuff));
		for(i=0;i<2;i++){
			if(strlen(LeftLeafSet[i].nodeid)!=8)
				continue;
			ostringstream ss;
			ss<<LeftLeafSet[i].port;
			strcat(sendBuff,LeftLeafSet[i].ip);
			strcat(sendBuff," ");
			strcat(sendBuff,ss.str().c_str());
			strcat(sendBuff," ");
			strcat(sendBuff,LeftLeafSet[i].nodeid);
			strcat(sendBuff,"#");
		}
		ostringstream ss;
		ss<<node.port;
		strcat(sendBuff,"#");
		strcat(sendBuff,node.ip);
		strcat(sendBuff," ");
		strcat(sendBuff,ss.str().c_str());
		strcat(sendBuff," ");
		strcat(sendBuff,node.nodeid);
		strcat(sendBuff,"#");
		write(newsockfd,sendBuff,strlen(sendBuff));
		memset(sendBuff,'\0',sizeof(sendBuff));
		for(i=0;i<2;i++){
			if(strlen(RightLeafSet[i].nodeid)!=8)
				continue;
			ostringstream ss;
			ss<<RightLeafSet[i].port;
			strcat(sendBuff,RightLeafSet[i].ip);
			strcat(sendBuff," ");
			strcat(sendBuff,ss.str().c_str());
			strcat(sendBuff," ");
			strcat(sendBuff,RightLeafSet[i].nodeid);
			strcat(sendBuff,"#");
		}
		write(newsockfd,sendBuff,strlen(sendBuff));
	}
}

void response_put(char recvBuff[]){
	char put_hash[9],value[100],ch='a';
	int sockfd=-1;
	memset(put_hash,'\0',sizeof(put_hash));
	memset(value,'\0',sizeof(value));
	int i=0;
	while(recvBuff[i]!=' '){
		put_hash[i] = recvBuff[i];
		i++;
	}
	i++;
	strcpy(value,&recvBuff[i]);
	checkInLeafSet(put_hash,false);
	if(inLeafSet && leftSet){
		//cout<<"inLeafSet && leftSet"<<endl;
		for(int i=0;i<2;i++){
			if(strcmp(LeftLeafSet[i].nodeid,put_hash)==0){
				//cout<<"call connect 1"<<endl;
				sockfd = connect_to_next_hop(LeftLeafSet[i].ip,LeftLeafSet[i].port);
				break;
			}
		}
	}
	else if(inLeafSet && !leftSet){
		//cout<<"inLeafSet && !leftSet"<<endl;
		for(int i=0;i<2;i++){
			if(strcmp(RightLeafSet[i].nodeid,put_hash)==0){
				//cout<<"call connect 2"<<endl;
				sockfd = connect_to_next_hop(RightLeafSet[i].ip,RightLeafSet[i].port);
				break;
			}
		}
	}
	else{
		//cout<<"call chkInRoutingTable"<<endl;
		checkInRoutingTable(put_hash);
		if(routingForward){
		//	cout<<"call connect 3"<<endl;
		//	cout<<"put to ip : "<<RoutingTable[rowF][colF].ip<<endl;
		//	cout<<"put to port : "<<RoutingTable[rowF][colF].port<<endl;
		//	cout<<"put to node : "<<RoutingTable[rowF][colF].nodeid<<endl;
			sockfd = connect_to_next_hop(RoutingTable[rowF][colF].ip,RoutingTable[rowF][colF].port);
		}
		else{
			//PUT key value in this node DHT
			DHT[string(put_hash)] = string(value);
			/*cout<<"***DHT***"<<endl;
	   		for(map <string,string>::iterator it=DHT.begin();it!=DHT.end();it++){
	   			cout<<it->first<<" : "<<it->second<<endl;
	   		}*/
		}
	}
	if(sockfd>=0){
	//	cout<<"creating put sockfd"<<endl;
		char sendBuff[100];
		memset(sendBuff,'\0',sizeof(sendBuff));
		strcpy(sendBuff,"1");
		strcat(sendBuff,recvBuff);
		write(sockfd,sendBuff,strlen(sendBuff));
	}
}

void response_get(char key[]){
	char value[100],ch='a';
	int sockfd=-1;
	memset(value,'\0',sizeof(value));
	//cout<<"get key : "<<key<<endl;
	checkInLeafSet(key,false);
	if(inLeafSet && leftSet){
	//	cout<<"inLeafSet && leftSet"<<endl;
		for(int i=0;i<2;i++){
			if(strcmp(LeftLeafSet[i].nodeid,key)==0){
			//	cout<<"call connect 1"<<endl;
				sockfd = connect_to_next_hop(LeftLeafSet[i].ip,LeftLeafSet[i].port);
				break;
			}
		}
	}
	else if(inLeafSet && !leftSet){
		//cout<<"inLeafSet && !leftSet"<<endl;
		for(int i=0;i<2;i++){
			if(strcmp(RightLeafSet[i].nodeid,key)==0){
				//cout<<"call connect 2"<<endl;
				sockfd = connect_to_next_hop(RightLeafSet[i].ip,RightLeafSet[i].port);
				break;
			}
		}
	}
	else{
		//cout<<"call chkInRoutingTable"<<endl;
		checkInRoutingTable(key);
		if(routingForward){
		//	cout<<"call connect 3"<<endl;
		//	cout<<"put to ip : "<<RoutingTable[rowF][colF].ip<<endl;
		//	cout<<"put to port : "<<RoutingTable[rowF][colF].port<<endl;
		//	cout<<"put to node : "<<RoutingTable[rowF][colF].nodeid<<endl;
			sockfd = connect_to_next_hop(RoutingTable[rowF][colF].ip,RoutingTable[rowF][colF].port);
		}
		else{
			//GET key value in this node DHT
			//DHT[string(&put_hash[1])] = string(value);
			//cout<<DHT[string(key)]<<endl;
		//	cout<<"get key"<<endl;
			for(map <string,string>::iterator it=DHT.begin();it!=DHT.end();it++){
				if(strcmp(it->first.c_str(),key)==0)
   					cout<<it->second<<endl;
   			}
		}
	}
	if(sockfd>=0){
		//cout<<"creating put sockfd"<<endl;
		char sendBuff[100];
		memset(sendBuff,'\0',sizeof(sendBuff));
		strcpy(sendBuff,"2");
		strcat(sendBuff,key);
		strcat(sendBuff,"#");
		strcat(sendBuff,node.ip);
		ostringstream ss;
		ss<<node.port;
		strcat(sendBuff," ");
		strcat(sendBuff,ss.str().c_str());
		write(sockfd,sendBuff,strlen(sendBuff));
		read(sockfd,value,sizeof(value));
		cout<<value<<endl;
	}
}

// '0' - JOIN
// '1' - PUT
// '2' - GET
void ServeClient(int newsockfd){
	//Call this on JOIN, and update routing table here
	hop=false;
	leftSet=true;
	inLeafSet=false;
	routingForward=false;
	char recvBuff[100];
	memset(recvBuff,'\0',sizeof(recvBuff));
	//cout<<"Serve client"<<endl;
	read(newsockfd,recvBuff,sizeof(recvBuff));
	//cout<<endl<<"buff ..."<<recvBuff<<endl;
	if(recvBuff[0]=='0'){
		response_join(newsockfd,&recvBuff[1]);	
	}
	else if(recvBuff[0]=='1'){
		//response_put(&recvBuff[1]);
		//*****************************************************************************
		char put_hash[20],value[100],temp[100],ch='a';
		int sockfd=-1;
		memset(put_hash,'\0',sizeof(put_hash));
		memset(value,'\0',sizeof(value));
		memset(temp,'\0',sizeof(temp));
		strcpy(temp,&recvBuff[1]);
		int i=0;
		while(temp[i]!=' '){
			put_hash[i] = temp[i];
			i++;
		}
		i++;
		strcpy(value,&recvBuff[i]);
	//	cout<<"put : "<<put_hash<<" buff : "<<recvBuff<<" temp : "<<temp<<endl;
		checkInLeafSet(put_hash,false);
		if(inLeafSet && leftSet){
		//	cout<<"inLeafSet && leftSet"<<endl;
			for(int i=0;i<2;i++){
				if(strcmp(LeftLeafSet[i].nodeid,put_hash)==0){
				//	cout<<"call connect 1"<<endl;
					sockfd = connect_to_next_hop(LeftLeafSet[i].ip,LeftLeafSet[i].port);
					break;
				}
			}
		}
		else if(inLeafSet && !leftSet){
			//cout<<"inLeafSet && !leftSet"<<endl;
			for(int i=0;i<2;i++){
				if(strcmp(RightLeafSet[i].nodeid,put_hash)==0){
				//	cout<<"call connect 2"<<endl;
					sockfd = connect_to_next_hop(RightLeafSet[i].ip,RightLeafSet[i].port);
					break;
				}
			}
		}
		else{
			//cout<<"call chkInRoutingTable"<<endl;
			checkInRoutingTable(put_hash);
			if(routingForward){
				//cout<<"call connect 3"<<endl;
				//cout<<"put to ip : "<<RoutingTable[rowF][colF].ip<<endl;
				//cout<<"put to port : "<<RoutingTable[rowF][colF].port<<endl;
				//cout<<"put to node : "<<RoutingTable[rowF][colF].nodeid<<endl;
				sockfd = connect_to_next_hop(RoutingTable[rowF][colF].ip,RoutingTable[rowF][colF].port);
				routingForward=false;
			}
			else{
				//PUT key value in this node DHT
				//DHT[string(put_hash)] = 
				//cout<<"put hash server: "<<put_hash<<endl;
				DHT[string(put_hash)] = string(value);
			}
		}
		if(sockfd>=0){
			//cout<<"creating put sockfd"<<endl;
			char sendBuff[100];
			memset(sendBuff,'\0',sizeof(sendBuff));
			strcpy(sendBuff,"1");
			strcat(sendBuff,temp);
			write(sockfd,sendBuff,strlen(sendBuff));
		}
		/*cout<<"***DHT***"<<endl;
   		for(map <string,string>::iterator it=DHT.begin();it!=DHT.end();it++){
   			cout<<it->first<<" : "<<it->second<<endl;
   		}*/
		//*****************************************************************************
	}
	else if(recvBuff[0]=='2'){
		char value[100],key[100],ch='a';
		int sockfd=-1;
		memset(value,'\0',sizeof(value));
		memset(key,'\0',sizeof(key));
		strcpy(key,&recvBuff[1]);
		//cout<<"get key : "<<key<<endl;
		checkInLeafSet(key,false);
		if(inLeafSet && leftSet){
			//cout<<"inLeafSet && leftSet"<<endl;
			for(int i=0;i<2;i++){
				if(strcmp(LeftLeafSet[i].nodeid,key)==0){
					//cout<<"call connect 1"<<endl;
					sockfd = connect_to_next_hop(LeftLeafSet[i].ip,LeftLeafSet[i].port);
					break;
				}
			}
		}
		else if(inLeafSet && !leftSet){
		//	cout<<"inLeafSet && !leftSet"<<endl;
			for(int i=0;i<2;i++){
				if(strcmp(RightLeafSet[i].nodeid,key)==0){
				//	cout<<"call connect 2"<<endl;
					sockfd = connect_to_next_hop(RightLeafSet[i].ip,RightLeafSet[i].port);
					break;
				}
			}
		}
		else{
			//cout<<"call chkInRoutingTable"<<endl;
			checkInRoutingTable(key);
			if(routingForward){
				//cout<<"call connect 3"<<endl;
				//cout<<"put to ip : "<<RoutingTable[rowF][colF].ip<<endl;
				//cout<<"put to port : "<<RoutingTable[rowF][colF].port<<endl;
				//cout<<"put to node : "<<RoutingTable[rowF][colF].nodeid<<endl;
				sockfd = connect_to_next_hop(RoutingTable[rowF][colF].ip,RoutingTable[rowF][colF].port);
			}
			else{
				//GET key value in this node DHT
				int i=0,k=0;
				char chk_key[10];
				char src_ip[20],port[20];
				memset(chk_key,'\0',sizeof(chk_key));
				memset(src_ip,'\0',sizeof(src_ip));
				memset(port,'\0',sizeof(port));
				for(i=0;key[i]!='#';i++)
					chk_key[i] = key[i];
				i++;
				while(key[i]!=' ')
					src_ip[k++] = key[i++];
				i++;
				k=0;
				while(key[i]!='\0')
					port[k++] = key[i++];
			//	cout<<"chk_key : "<<chk_key<<" ip : "<<src_ip<<" port : "<<port<<endl;
				for(map <string,string>::iterator it=DHT.begin();it!=DHT.end();it++){
					/*cout<<"it->first.c_str() :"<<it->first.c_str()<<"."<<endl;
					cout<<"chk_key :"<<chk_key<<"."<<endl;*/
					if(strcmp(it->first.c_str(),chk_key)==0){
	   					//cout<<it->first<<" : "<<it->second<<endl;
	   					sockfd = connect_to_next_hop(src_ip,atoi(port));
	   					strcpy(value,"3");
	   					strcat(value,it->second.c_str());
	   					write(sockfd,value,strlen(value));
	   					close(sockfd);
	   					return;
	   				}
	   			}
	   			//cout<<"value : "<<value<<endl;
			}
		}
		if(sockfd>=0){
			//cout<<"creating put sockfd"<<endl;
			char sendBuff[100];
			memset(sendBuff,'\0',sizeof(sendBuff));
			strcpy(sendBuff,"2");
			strcat(sendBuff,key);
			write(sockfd,sendBuff,strlen(sendBuff));
		}
	}
	else if(recvBuff[0]=='3')
		cout<<&recvBuff[1]<<endl;
}

void *Server(void *threadid) {
   pthread_t client_thread;
   int i,rc;
   int sockfd, newsockfd,clilen;
   struct sockaddr_in server_addr,client_addr;
   if((sockfd=create_socket())<0){
		pthread_exit(NULL);
	}
	if(bind(sockfd,server_portno,server_addr)<0){
		pthread_exit(NULL);
	}
	listen(sockfd,5);
    clilen = sizeof(client_addr);	
	while(1){
		newsockfd = accept(sockfd,(struct sockaddr*)&client_addr, (socklen_t *)&clilen);
		if(newsockfd<0){
			cout<<"Error on connection accept\n";
			pthread_exit(NULL);
		}
	//	cout<<"\nConnection accepted for client "<<inet_ntoa(client_addr.sin_addr)<<endl;;
		//rc = pthread_create(&client_thread, NULL, ServeClient, (void *)newsockfd);
		ServeClient(newsockfd);
		close(newsockfd);
		/*if (rc)
			cout<<"ERROR on ServeClient thread\n";*/
	}
}

void getTableEntries(int sockfd){
	char recvBuff[100],sendBuff[100],ch='a';
	int row;
	//cout<<"Node Id:"<<nodeId<<endl;
	//cout<<"Client Id:"<<clientId<<endl;
	for(row=0;row<8;row++){
		if(nodeId[row]!=clientId[row]){
			break;
		}
			
	}
	while(1){
		for(int j=0;j<4;j++){
			char port[20];
			memset(recvBuff,'\0',sizeof(recvBuff));
			memset(port,'\0',sizeof(port));
			read(sockfd,recvBuff,sizeof(recvBuff));
			write(sockfd,&ch,1);
			//cout<<"read : "<<recvBuff<<endl;
			if(strlen(recvBuff)>8){
				struct packet rt;
				int k=0,i=0;
				memset(rt.ip,'\0',sizeof(rt.ip));
				memset(rt.nodeid,'\0',sizeof(rt.nodeid));
				while(i<strlen(recvBuff) && recvBuff[i]!=' '){
					rt.ip[k]=recvBuff[i];
					RoutingTable[row][j].ip[k++] = recvBuff[i++];
				}
					
				k=0;
				i++;
				while(i<strlen(recvBuff) && recvBuff[i]!=' ')
					port[k++] = recvBuff[i++];

				RoutingTable[row][j].port = atoi(port);		
				rt.port = RoutingTable[row][j].port;


				i++;
				k=0;
				while(i<strlen(recvBuff) && recvBuff[i]!='\0'){
					rt.nodeid[k]=clientId[k];
					RoutingTable[row][j].nodeid[k++] = recvBuff[i++];
				}

				if(row < 8)
					RoutingTable[row][clientId[row]-'0'] = rt;				
			}

		}
		memset(recvBuff,'\0',sizeof(recvBuff));
		read(sockfd,recvBuff,sizeof(recvBuff));
		if(strcmp(recvBuff,"noHop")==0){
			//get leaf set
			for(int i=0;i<2;i++){
				memset(recvBuff,'\0',sizeof(recvBuff));
				read(sockfd,recvBuff,sizeof(recvBuff));
				cout<<"got leaf : "<<recvBuff<<endl;
				if(strlen(recvBuff)==0)
					continue;
				int k=0;
				for(int p=0;p<4;p++){
					int j=0;
					char leaf_ip[20],leaf_id[10],leaf_port[20];
					memset(leaf_ip,'\0',sizeof(leaf_ip));
					memset(leaf_id,'\0',sizeof(leaf_id));
					memset(leaf_port,'\0',sizeof(leaf_port));
					while(recvBuff[k]=='#') k++;
					while(k<strlen(recvBuff) && recvBuff[k]!=' '){
						leaf_ip[j++] = recvBuff[k++];
					}
					k++;
					j=0;
					while(k<strlen(recvBuff) && recvBuff[k]!=' '){
						leaf_port[j++] = recvBuff[k++];
					}
					k++;
					j=0;
					while(k<strlen(recvBuff) && recvBuff[k]!='#')
						leaf_id[j++] = recvBuff[k++];
					k++;
					cout<<leaf_ip<<"..."<<leaf_port<<"..."<<leaf_id<<endl;
					char sendBuff[100];
					memset(sendBuff,'\0',sizeof(sendBuff));
					if(strcmp(leaf_id,node.nodeid)!=0){
						strcat(sendBuff,leaf_ip);
						strcat(sendBuff," ");
						strcat(sendBuff,leaf_port);
						strcat(sendBuff," ");
						strcat(sendBuff,leaf_id);
						checkInLeafSet(sendBuff);
					}
				}
				/*
				while(k<strlen(recvBuff) && recvBuff[k]!='#')
					sendBuff[j++] = recvBuff[k++];
				k++;
				j=0;
				checkInLeafSet(sendBuff);
				memset(sendBuff,'\0',sizeof(sendBuff));
				while(k<strlen(recvBuff) && recvBuff[k]!='\0')
					sendBuff[j++] = recvBuff[k++];*/
			}
			break;
		}
		if(strlen(recvBuff)>8){
			char ip[20];
			char port[10];
			memset(ip,'\0',sizeof(ip));
			memset(port,'\0',sizeof(port));
			int k=0,i=0;
			while(i<strlen(recvBuff) && recvBuff[i]!=' ')
				ip[k++] = recvBuff[i++];
			k=0;
			i++;
			while(i<strlen(recvBuff) && recvBuff[i]!=' ')
				port[k++] = recvBuff[i++];
			i++;
			row=0;	
			while(recvBuff[i]!='\0'){
				if(node.nodeid[row]!=recvBuff[i])
					break;
				row++;
				i++;
			}
			string hash = hash_value(string(ip)+":"+string(port));
			strcpy(clientId,hash.c_str());
		//	cout<<"call connect hop getTable"<<endl;
			sockfd = connect_to_next_hop(ip,atoi(port));
			memset(sendBuff,'\0',sizeof(sendBuff));
			strcpy(sendBuff,"0");
			strcat(sendBuff,node.ip);
			strcat(sendBuff," ");
			ostringstream ss;
			ss<<node.port;
			strcat(sendBuff,ss.str().c_str());
			strcat(sendBuff," ");
			strcat(sendBuff,node.nodeid);
			write(sockfd,sendBuff,strlen(sendBuff));
			if(sockfd<0) 
				break;
		}
		else 
			break;
	}
	//cout<<"hop while loop end\n";
	//print_route();
}

void call_put(char key[],string value){
	strcat(key," ");
	strcat(key,value.c_str());
	response_put(key);
}

void call_get(char key[]){
	response_get(key);
}

void join(char join_ip[],int portno){
	ostringstream ss; //to convert int to string
	int sockfd, n,choice;
	struct sockaddr_in server_addr;
	char sendBuff[1024],recvBuff[1024],ch='a';
	sockfd = create_socket();		
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(join_ip);
	server_addr.sin_port = htons(portno);
	if(sockfd<0){
		cout<<"socket error in join\n";
		return;
	}
//	cout<<"socket success for join\n";
	n = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(n<0){
		cout<<"Connection error\n";
		return;
	}
	ss << node.port;
	memset(sendBuff,'\0',sizeof(sendBuff));
	strcpy(sendBuff,"0");
	strcat(sendBuff,node.ip);
	strcat(sendBuff," ");
	strcat(sendBuff,ss.str().c_str());
	strcat(sendBuff," ");
	strcat(sendBuff,node.nodeid);
	//cout<<"sendbuff.."<<sendBuff<<endl;
	write(sockfd,sendBuff,strlen(sendBuff));
	getTableEntries(sockfd);
	close(sockfd);
}

void create(){
	memset(node.ip,'\0',sizeof(node.ip));
	memset(node.nodeid,'\0',sizeof(node.nodeid));
	strcpy(node.ip,server_ip.c_str());
	node.port = server_portno;
	strcpy(node.nodeid,nodeId);
}

void intialize_route(){
	struct packet rt;
	strcpy(rt.ip,server_ip.c_str());
	rt.port = server_portno;
	strcpy(rt.nodeid,nodeId);
	
	for(int i=0;i<8;i++){
		RoutingTable[i][nodeId[i]-'0'] =rt ;
	}

	char dump[3] = {'-','-','-'};
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++){
			if(strlen(RoutingTable[i][j].nodeid)==0)
				strcpy(RoutingTable[i][j].nodeid,dump);
		}
	}
}

void print_lset(){
	cout<<"Left leaf set"<<endl;
	for(int i=0;i<2;i++){
		cout<<LeftLeafSet[i].ip<<" "<<LeftLeafSet[i].port<<" "<<LeftLeafSet[i].nodeid<<endl;
	}
	cout<<"Right leaf set"<<endl;
	for(int i=0;i<2;i++){
		cout<<RightLeafSet[i].ip<<" "<<RightLeafSet[i].port<<" "<<RightLeafSet[i].nodeid<<endl;
	}
}

void print_dht(){
	cout<<"DHT"<<endl;
	for(map <string,string>::iterator it=DHT.begin();it!=DHT.end();it++)
		cout<<it->first<<" : "<<it->second<<endl;
}

int main () {
   pthread_t server_thread;
   int i,rc;
   bool create_set=false;
   //Create thread to start server
   while(1){
   		//Get client queries
	   	char query[5]={'\0'};
	   	cout<<"\nEnter query : ";
	   	cin>>query;
	   	if(strcmp(query,"join")==0){
	   		if(!create_set){
	   			cout<<"Server not created"<<endl;
	   			continue;
	   		}
	   		char join_ip[20];
	   		int join_port;
	   		memset(join_ip,'\0',sizeof(join_ip));
	   		cin>>join_ip;
	   		cin>>join_port;
	   		ostringstream ss;
	   		ss << join_port;
	   		string hash = hash_value(string(join_ip) + ":"+ss.str())	;
	   		strcpy(clientId,hash.c_str());
	   		join(join_ip,join_port);
	   	}
	   	else if (strcmp(query,"create")==0){
	   		rc = pthread_create(&server_thread, NULL, Server, (void *)i);
	   		//cout<<"Printing the strlen RT[5][0]"<<strlen(RoutingTable[5][0].nodeid)<<endl;
	   		intialize_route();
	   		create();
	   		create_set = true;
	   		//print_route();
	   	}
	   	else if(strcmp(query,"port")==0){
	   		server_ip = find_ip_addr();
	   		cin>>server_portno;
	   		ostringstream ss;
	   		ss<<server_portno;
	   		string hash = hash_value(server_ip + ":"+ss.str());
	   		strcpy(nodeId,hash.c_str());
	   		//cout<<"nodeid : "<<nodeId<<endl;
	   	}
	   	else if(strcmp(query,"put")==0){
	   		string var,value;
	   		cin>>var>>value;
	   		string hash = hash_value(var);
	   		cout<<"var hash : "<<hash<<endl;
	   		char key[9];
	   		memset(key,'\0',sizeof(key));
	   		strcpy(key,hash.c_str());
	   		call_put(key,value);
	   		/*cout<<"***DHT***"<<endl;
	   		for(map <string,string>::iterator it=DHT.begin();it!=DHT.end();it++){
	   			cout<<it->first<<" : "<<it->second<<endl;
	   		}*/
	   	}
	   	else if(strcmp(query,"get")==0){
	   		string var;
	   		char key[10];
	   		cin>>var;
	   		string hash = hash_value(var);
	   		memset(key,'\0',sizeof(key));
	   		strcpy(key,hash.c_str());
	   		//cout<<"hash : "<<key<<endl;
	   		call_get(key);
	   	}
	   	else if(strcmp(query,"lset")==0){
	   		print_lset();
	   	}
	   	else if(strcmp(query,"routetable")==0){
	   		print_route();
	   	}
	   	else if(strcmp(query,"dht")==0){
	   		print_dht();
	   	}
	   	else
	   		cout<<"Wrong command"<<endl;
   }
   return 0;
}