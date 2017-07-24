#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *set1=NULL,*set2=NULL;

void separateSets(int argc,char *arg[]){			//this function separates the sets from input arguments
	int i,j=0;//,k=0;
	for(i=1;i<argc;i++){
		if(arg[i][0] != '-'){
			if(arg[i-1][1] != 'I' || arg[i-1][1] != 'O'){
				set1 = (char*)malloc(sizeof(arg[i]));
				//for(k=0;k<sizeof(arg[i]);k++)*/
					set1 = arg[i];
			//	printf("Inside separateSets: %s\t%s\n",arg[i],set1 );
				j=i;
				break;
			}
		}
	}set2 = (char*)malloc(sizeof(arg[j+1]));
	set2 = arg[j+1];
				//printf("Inside separateSets: %s\t%s\n",arg[j+1],set2 );

}

void parseCommand(char options[],int argcount, char *arg[]){	//this function is used to obtain all the options entered
	int i=0,j=0,k=0;
	while(i < argcount){
		k=0;
		if(arg[i][k++]=='-'){
			while(arg[i][k]!='\0'){
				if(arg[i][k] == 'I')
					options[6] = i+1;		//saving the index of the input file
				else if(arg[i][k] == 'O')
					options[7] = i+1;			//saving the index of the output file
				//options[j++] = arg[i][k];
				if(arg[i][k] == 'd')		// save the options in options[] array in specific order so retrieval will be easy
					options[0] = 'd';
				else if(arg[i][k] == 's')
					options[1] = 's';
				else if(arg[i][k] == 'c')
					options[2] = 'c';
				//printf("%c   ",options[j-1] );
				k++;
			}
		}
		i++;
	}
	//printf("options array after parsing is : %s\n",options );
	if(k>0)
		options[5] = '1';
}

void toUpper(){
	int c;
	while((c=getchar())!= EOF){
		if(c >= 'a' && c <= 'z')
			c = c -('a'-'A');
		printf("%c", c);
	}
}


void toLower(){
	int c;
	while((c=getchar())!= EOF){
		if(c >= 'A' && c <= 'Z')
			c = c +('a'-'A');
		printf("%c", c);
	}
}

void noFile(char mapping[]){			//cases when no File is

	if(set1[0] == '['){
		switch(set1[2]){
			case 'u' :	if(strcmp(set1,"[:upper:]") == 0){
							if(strcmp(set2,"[:lower:]") == 0)
								toLower();
							else if(set2[1] == '-'){ //it means some range query is there
								int start = set2[0]-0;
								int end = set2[2]-0;
								int i,j=start;
								for(i=65;i<=90 && j<=end;i++){
									mapping[i] = j++;
								}
								i--;
								while(i<=90)
									mapping[i++] = end;

								int c=0; // for reading the character
								while((c= getchar())!= EOF){
									printf("%c",mapping[c]);
								}
							}
							else{
								int len2 = strlen(set2);
								int i=65,j=0;
								while(i<= 90 && j< len2){
									mapping[i++] = set2[j++];
								}
								j--;
								while(i<=122)
									mapping[i++] = set2[j];
								/*for(i=0;i<256;i++)
									printf("%d ",mapping[i] );*/
								int c=0; // for reading the character
								while((c= getchar())!= EOF)
									printf("%c",mapping[c]);
							}
						}
						else{
							//something other than [:upper:]
						}
						break;

			case 'l' :	if(strcmp(set1,"[:lower:]") == 0){
							if(strcmp(set2,"[:upper:]") == 0)
								toLower();
							else if(set2[1] == '-'){ //it means some range query is there
								int start = set2[0]-0;
								int end = set2[2]-0;
								int i,j=start;
								for(i=97;i<=122 && j<=end;i++){
									mapping[i] = j++;
									//printf("Mapping of %c is : %c\n",i,j-1 );
								}
								i--;
								while(i<=122)
									mapping[i++] = end;

								int c=0; // for reading the character
								while((c= getchar())!= EOF){
									printf("%c",mapping[c]);
								}
							}
							else{
								int len2 = strlen(set2);
								int i=97,j=0;
								while(i<= 122 && j< len2){
									mapping[i++] = set2[j++];
								}
								j--;
								while(i<=122)
									mapping[i++] = set2[j];
								/*for(i=0;i<256;i++)
									printf("%d ",mapping[i] );*/
								int c=0; // for reading the character
								while((c= getchar())!= EOF)
									printf("%c",mapping[c]);
							}
						}
						else{
							//something other than [:lower:]
						}
						break;
		}
			
	}
	/*if(strcmp(set1,"[:upper:]") == 0){
		switch(set2[2]){
			case 'u' :	printf("Inside switch after upper\n");
						if(strcmp(set2,"[:upper:]") == 0)
							toUpper();
							break;

			case 'l' :	if(strcmp(set2,"[:lower:]") == 0)
							toLower();
							break;				
		}
	}
	else if(strcmp(set1,"[:lower:]") == 0){
		switch(set2[2]){
			case 'u' :	printf("Inside switch after lower\n");
						if(strcmp(set2,"[:upper:]") == 0)
							toUpper();
							break;

			case 'l' :	if(strcmp(set2,"[:lower:]") == 0)
							toLower();
							break;				
		}
	}
	else if(strcmp(set1,"[:digits:]") == 0){
		//remaining like [:space:] or [:digit:] etc


	}*/
	else{		//when just characters are to be replaced character wise
		int c=0; // for reading the character
		while((c= getchar())!= EOF){
			printf("%c",mapping[c]);
		}	

	}
}  

void intializeHash(char mapping[]){
	int i=0;
	for(i=0;i<256;i++)
		mapping[i] = i;
}

void hash(char mapping[]){
	intializeHash(mapping);
	int i=0,j=0;
	int len1 = strlen(set1);
	int len2 = strlen(set2);
		//printf("This is mapping before Hash :%s\n",mapping );


	while(i< len1 && j<len2){
		mapping[set1[i]-0] = set2[j];
		i++;
		j++;
	}
	j--;

	while(i<len1)
		mapping[set1[i++]-0] = set2[j];

	/*printf("This is mapping after Hash :\n");
	for(i=0;i<256;i++)
		printf("%d ",mapping[i] );*/
}

int main(int argc, char*argv[]){
	
	//int i=0;
	char opt [8] = ""; //first 5 for options,, 6th for checking whether flags exist. 7th is index of i/p file 8th is for o/p file	
	separateSets(argc,argv);
	parseCommand(opt,argc,argv);
	char mapping [256]; // maps every charcter to other like hashing
	hash(mapping);
	/*printf("%s\n",opt );
	printf("opt[5] : %c   %c\n",opt[5],opt[6] );
	//printf("Set1 :%s \tSet2 :%s",set1,set2);*/
	int temp = opt[6];
//	printf("%d\n",temp);
	if(temp == 0){
		//No input file passed as arguments
		//printf("***** IF ******");
		noFile(mapping);
	}
	else{

	}


	return 0;
}