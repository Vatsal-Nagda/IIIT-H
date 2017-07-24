if(strcmp(arr,"pwd")==0) //Internal command pwd
{
		gpwd();
		return 0;
}

if(strstr(arr,"export")!=NULL)
		{

			int len = strlen(arr);
			for(i=0;i<len;i++){

				if(arr[i]==' '){
					pos = i;
					break;
				}
			}

			arr=arr+(pos+1);
			
			char *name = strtok(arr,"=");
			char *val = strtok(NULL,"=");
			int ret = setenv(name,val,1);
			if(ret==-1)
				perror("Error: ");
			return 0;
		}


if(strcmp(start,"echo")==0)
		{
			//Print Envt Variable
			//printf("start = %s\n ", start);
			//printf("arr = %s\n ", arr);
			//printf("com = %s\n ", com);
			//printf("Name = %s",name);
			char *name=strtok(NULL," ");
			//printf("Name is: %s\n",name);
			if(name[0]=='$')
			{
				name=name+1;
				char *val = getenv(name);
				//printf("\nVal is : %s",val);
				printf("%s",val);          //new line removed  =======================================================
			}
			else
			{

				//printf("In else\n");
				//printf("\n");
				int len = strlen(com);
				for(i=0;i<len;i++){

					if(com[i] == '"'){
						flag = 1;
						cnt_first = i;
						break;
					}

				}



				for(i=0;i<len;i++){

					if(com[i]=='"'){
						cnt++;
					}
				}

				if((cnt %2 == 0) && (cnt > 0)){

					for(i=cnt_first+1;i<len;i++){

						if(com[i]!='"'){
							echoString[k]=com[i];
							k++;
						}
					}
					echoString[k]=0;
					printf("%s\n", echoString);

				}
				
				else{
					while(name!=NULL)
					{
						printf("%s ",name);
						name = strtok(NULL," ");
					}

					printf("\n");    //newline added   ===============================
				}
			}
			return 0;
		}


void showHistory(int val)
{

	//printf("calling print history\n");
	//printf("val = %d\n",val);

	ifstream in ("history.txt");
	int n=0, count;
	string s;   

	if (in.is_open())
	{
		while (! in.eof() )
		{
			getline (in,s);
			n++;
			
		}

		in.close();
	}

	//printf("n = %d\n",n);

	if((val == 0) || (val>n)){

		//printf("general case\n");

		ifstream in ("history.txt");
		int n=1;
			
		string s;   
		if (in.is_open())
		{
			while (! in.eof() )
			{
				getline (in,s);
				cout<<n<<"   "<<s<<"\n";
				n++;
				
			}

			in.close();
		}
	}

	else{

		//printf("special case\n");

		count = n - val;
		
		ifstream in ("history.txt");
		int n=1;
			
		string s;   
		if (in.is_open())
		{
			while (! in.eof() )
			{
				getline (in,s);
				if(n>=count)
					cout<<n<<"   "<<s<<"\n";
				n++;
				
			}

			in.close();
		}
	}


}


void createHistoryFile(char arr[])
{
	
	
	ifstream in ("history.txt");
	vector<string> v;
	int ch,n=0;
	string check;
	int flag = 0;
		
	string s;   
	if (in.is_open())
	{
		while (! in.eof() )
		{
			getline (in,s);

			//printf("In while for pushing the data\n");
			//cout<<" s = "<<s<<endl;
	
			v.push_back(s);
			n++;
			
		}

		in.close();
	}
	
	//printf("n is : %d",n);

	check = arr;
	//cout<<"the new string is :"<<check<<endl;
	
	//printf("n is : %d\n",n);

	if(n==0){
		//printf("In if\n");
		v.push_back(arr);
			//n++;
	}
	else{
		if(check.compare(v[n-2])!=0){
			//printf("diffeeerrrr\n");
			v.push_back(arr);
		}

		else{
			flag = 1;
			//printf("same\n");
		}
	}

	ofstream out("history.txt",std::fstream::out | std::fstream::app);

		if (out.is_open())
		{
			if(flag == 0){
				out << v[n];
				out << "\n";
				out.close();
			}
		}

	}