#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

void remove_Spaces(string &str){

	while((str[0]==' ' || str[0] == '\t') || (str[str.size()-1]==' ' || str[str.size()-1] == '\t')){
		size_t first = str.find_first_not_of(' ');
	    size_t last = str.find_last_not_of(' ');
	    str = str.substr(first, (last-first+1));

	    first = str.find_first_not_of('\t');
	    last = str.find_last_not_of('\t');
	    str = str.substr(first, (last-first+1));
	}

}

void parseInput(string line,vector < string > &commands){

	int length = line.size();
	/*char ip_arr [length+1] ;
	//char 
	line.copy(ip_arr, length);*/

	char *ip_arr = new char[line.size()+1];
	strcpy(ip_arr,line.c_str());

	bool flag_dub_quote = false;
	bool flag_sing_quote = false;

//	printf("The input line passed here is :\n");

	int start_ind =0;
	string buffer="";
	//vector <string> v;



	for(int i=0;i<length;i++){		
		
		if(ip_arr[i] == '"'){
			if(flag_dub_quote == false)
				flag_dub_quote = true;
			else
				flag_dub_quote = false;
		//	buffer+= ip_arr[i];
		}

		if(ip_arr[i] == '\''){
			if(flag_sing_quote == false)
				flag_sing_quote = true;
			else
				flag_sing_quote = false;
			//buffer+= ip_arr[i];
		}

		if(!flag_sing_quote && !flag_dub_quote){							//none of the quotes have come
			/*if(ip_arr[i] ==' ' || ip_arr[i] =='\n' || ip_arr[i] =='\t'){
				ip_arr[i] = '\0';
			}*/
			if(ip_arr[i] == '|'){
				//to do
				remove_Spaces(buffer);
				//v.push_back(buffer);
				commands.push_back(buffer);
				//cout<<"\n"<<buffer<<"c"<<endl;
				buffer="";
			}
			else{
				buffer += ip_arr[i];				
			}	
		}else{
				buffer+= ip_arr[i];
		}


		//printf("%c",ip_arr[i]);

	}

	remove_Spaces(buffer);
	//v.push_back(buffer);
	commands.push_back(buffer);
	//cout<<"\n"<<buffer<<endl;

}