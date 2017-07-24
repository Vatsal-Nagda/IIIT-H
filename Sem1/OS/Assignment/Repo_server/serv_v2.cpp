#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
#include <ctime>

using namespace std;

void log_server(string ip,string req_type){

	fstream ser_log;
	ser_log.open("server_log.log",ios::app);

	time_t curr_Time;
	struct tm * loc_time;

	time(&curr_Time);
	loc_time = localtime(&curr_Time);

	int Day    = loc_time->tm_mday;
    int Month  = loc_time->tm_mon + 1;
  	int Year   = loc_time->tm_year + 1900;
   	int Hour   = loc_time->tm_hour;
  	int Min    = loc_time->tm_min;
  	int Sec    = loc_time->tm_sec;

  	if(req_type.compare("search")){
  		ser_log<<Day<<"-"<<Month<<"-"<<Year<<" "<<Hour<<"-"<<Min<<"-"<<Sec<<":"<<"Search request from "<<ip<<endl;
  	}
  	else{
  	  	ser_log<<Day<<"-"<<Month<<"-"<<Year<<" "<<Hour<<"-"<<Min<<"-"<<Sec<<":"<<"Share request from "<<ip<<endl;	
  	}
  	
  	ser_log.close();
}

map<string, vector< pair <string,string> > > repoData;


void bind_sock(int sockfd, struct sockaddr_in server_add,int port_no){
	bzero((char *)&server_add,sizeof(server_add));
	
	server_add.sin_family = AF_INET;
	server_add.sin_port = htons(port_no);
	server_add.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd,(struct sockaddr *)&server_add,sizeof(server_add)) < 0){
		
		 cout << "=> Error binding connection, the socket has already been established..." << endl;
        //return 0;
	}
}



void repo_load(){

	repoData.clear();
	fstream repoFile ;
	repoFile.open("repo.txt",ios::in|ios::app);
	string fileName,ip,path;

	vector< pair <string,string> > v;
	pair <string,string> p;

	
	while(!(repoFile.eof())){
		
		repoFile >>fileName>>ip>>path;
		

		repoData[fileName].push_back(make_pair(ip,path));

	}

	repoFile.close();
}

void displayMap(){

	vector< pair <string,string> > v;
	pair <string,string> p;

	cout<<"printing the map"<<endl;
	for(map<string, vector< pair <string,string> > > :: iterator map_itr= repoData.begin();map_itr != repoData.end();map_itr++){
		cout<<map_itr->first<<endl;
		v = map_itr->second;
		cout<<"Corresponding vectors :";
		for(vector< pair <string,string> > :: iterator vec_itr =v.begin();vec_itr != v.end();vec_itr++){
			cout<<vec_itr->first<<" ";
			cout<<vec_itr->second<<endl;
		}

	}
}


void repo_share(int newsockfd,string input,string ip){
	fflush(stdout);
	log_server(ip,"share");
	//cout<<"Input file is :"<<input<<endl;
	size_t start = input.find("share#121#");
	cout.flush();
	unsigned int i,index=0;

	for(i=10;i<input.length();i++){
		if(input[i] == '/')
			index = i;
	}
	
	if(index == 0)	
		index = 9;
	//cout<<"The last index of / is"<<index<<endl;
	string file = input.substr(index+1);
	string path = input.substr(start+10);
		//cout<<"The index of share#121# is :"<< start<<endl;

	cout<<"Filename "<<file<<endl;
	cout << "Ip "<<ip<<endl;
	cout<<"Path "<<path<<endl;

	vector< pair <string,string> > v;
	v.push_back(make_pair(ip,path));

	//if(repoData.find(file) == repoData.end()){
		//file doesnt exist
		map<string, vector< pair <string,string> > > :: iterator map_itr= repoData.find(file);

		if(map_itr!= repoData.end()){
			//already there in map
			map_itr->second.push_back(make_pair(ip,path));
		}
		else
			repoData.insert( std::pair<string,vector< pair <string,string> > >(file,v) );

		ofstream repoFile ;
		repoFile.open("repo.txt",ios::in|ios::app);

		repoFile<<"\n"<<file<<" "<<ip<<" "<<path;
		repoFile.close();

		displayMap();
	

	write(newsockfd,"\nFile shared successfully on the repo server\n",45);

}

void repo_search(int newsockfd,string input,string ip){

	repo_load();
	log_server(ip,"search");
	fflush(stdout);
	//cout<<"Input file is :"<<input<<endl;
	size_t start = input.find("search#121#");
	string file = input.substr(start+11);
	//string path = input.substr(start+10);

	vector< pair <string,string> > v;
	pair <string,string> p;

	string vectors="";
	int count=1;
	map<string, vector< pair <string,string> > > :: iterator map_itr= repoData.find(file);
	if(map_itr != repoData.end()){
		cout<<map_itr->first<<endl;
		v = map_itr->second;
	//	cout<<"Corresponding vectors :";
		for(vector< pair <string,string> > :: iterator vec_itr =v.begin();vec_itr != v.end();vec_itr++){
			cout<<vec_itr->first<<" ";
			cout<<vec_itr->second<<endl;
			vectors += to_string(count)+". "+vec_itr->first+" "+vec_itr->second+"\n";
			count++;

		}
	}

	if(count == 1)
		vectors ="No mirrors available now\n";
	char * vect = new char[vectors.length()+1];
	//char vect[1024];
	strcpy(vect, vectors.c_str());
	write(newsockfd,vect,strlen(vect));

}


void response_cient(int newsockfd,string ip){
	int bufsize = 256;
    char buffer[bufsize];
    int num;
   
    pid_t pid = getpid();
    bzero(buffer,bufsize);

     while((num = read(newsockfd,buffer,bufsize)) > 0){

     	fflush(stdout);
     	string input(buffer);
     	cout<<"serviced by the process : "<<pid<<endl;
     	cout.flush();
     	
     	if(input.find("search#121#") != string::npos){
     		repo_search(newsockfd,input,ip);
     		cout.flush();
     		write(newsockfd,"\n Your Search Request\n",22);
     	}	
     	else if(input.find("share#121#") != string::npos){
     		repo_share(newsockfd,input,ip);
     		cout.flush();
     		write(newsockfd,"\n Your Share Request\n",21);
     	}
     	else{
     		cout<<"\nThe message received is :\n"<<buffer<<endl;
     		cout.flush();
     		write(newsockfd,"\nGot your normal message\n",25);
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
		cout << "Error creating the socket";
		_exit(1);
	}

	bind_sock(sockfd,server_add,port_no);

	listen(sockfd,5);

	clilen = sizeof(client_add);

	while(1){
		newsockfd = accept(sockfd, (struct sockaddr *) &client_add,(socklen_t *) &clilen);
		
		repo_load();

		if (newsockfd < 0) 
        	cout << "=> Error on accepting..." << endl;
		
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