#include <string>
#include <iostream>

using namespace std;

void echo(string line){

//	cout<<"Echo called\n";
	line = line.substr(4);
	int i=0;

	bool flag_dub_quote = false;
	bool flag_sing_quote = false;

	char *ip_arr = new char[line.length()+1];
	strcpy(ip_arr,line.c_str());

	string buffer="";

	while(ip_arr[i]!= '\0'){
		if(ip_arr[i] == '"'){
			i++;
			while(ip_arr[i] != '\0'){
				if(ip_arr[i] == '"')
					break;
				buffer += ip_arr[i];
				i++;
			}
		}

		else if(ip_arr[i] == '\''){
			i++;
			while(ip_arr[i] != '\0'){
				if(ip_arr[i] == '\'')
					break;
				buffer += ip_arr[i];
				i++;
			}
		}
		else{

			if(ip_arr[i] ==' ' && ip_arr[i+1]==' ')
				ip_arr[i] = '\0';
			else
				buffer += ip_arr[i];

		}

		i++;
	}

	//cout<<"\nThe string is";
	cout << buffer<<endl;
	/*for(i=0;i<line.length()-1;i++){

		if(ip_arr[i] == '"'){
			if(flag_dub_quote == false)
				flag_dub_quote = true;
			else
				flag_dub_quote = false;
		//	buffer+= ip_arr[i];
		}

		else if(ip_arr[i] == '\''){
			if(flag_sing_quote == false)
				flag_sing_quote = true;
			else
				flag_sing_quote = false;
			//buffer+= ip_arr[i];
		}

		if(flag_dub_quote){
			buffer+= ip_arr[i];
		}

		if(flag_sing_quote){
			buffer+= ip_arr[i];
		}

		if(!flag_sing_quote && !flag_dub_quote){		//no quotes
			if(ip_arr[i] ==' ' && ip_arr[i+1]==' ')
				ip_arr[i] = '\0';
		}
	}*/

	//cout<<"The string after chck is :"<<buffer<<endl;
	
}