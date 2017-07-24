#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <malloc.h>

using namespace std;
char * home;

vector < string > history_data;

void load_history(){

	history_data.clear();
	home = (char *)malloc(sizeof(char)*250);
	home = getenv("HOME");
	strcat(home,"history.txt");
	
	ifstream history("history.txt");
	string line;

	if (history.is_open())
	  {
	    while(getline(history,line))
	    	history_data.push_back(line);
	  }

	 history.close();

}

void send_to_history(string str){
		
	load_history();

	//cout<<"The size of Vector is"<<history_data.size()<<endl;

	fstream history ("history.txt",ios::app);

	if(history_data.empty()){
		history << str<<endl;
		history_data.push_back(str);
	}
	else if(str.compare(history_data.back()) != 0){		
		history_data.push_back(str);
		history << str<<endl;
	}
	

	history.close();

}

void print_history(){

	for(int i=0;i<history_data.size();i++){
		cout<<i<<" "<<history_data.at(i)<<endl;
	}
}

void parse_history(string str){

	if(str.compare("history") == 0){
		print_history();
	}
	else {

		char *buffer = new char[str.length()];
		strcpy(buffer,str.c_str());

		printf("String :%s\n",buffer );
		string len="";

		//not shebang character
		int i=0;
		while(buffer[i]!='\0'){
		
			if((buffer[i] >='0' && buffer[i]<='9') || buffer[i] == '-'){
				len += buffer[i];
			}

			i++;
		}


		int length = atoi(len.c_str());
		//int length = stoi(str,10);
		cout<<"the length reuired is "<<length<<endl;

		if(length < 0){
			//to do
			cout<<"Error"<<endl;
		}
		else{
			if(length >= history_data.size())
				print_history();
			else{
				for(int i = history_data.size()-length; i<history_data.size();i++)
					cout<<i<<" "<<history_data.at(i)<<endl;
			}
		}

	}

}


