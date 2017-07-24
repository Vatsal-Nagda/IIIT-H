/***************************************************************************************

			NAME    : VATSAL MANOJ NAGDA
			ROLL NO : 20162008

***************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define IN 1
#define OUT 0
char options[6] = "";
int l_line=0,w_word=0,m_char=0,c_byte=0,L_maxline=0;

int parseCommand(int argcount, char* arg[]){				//RETURNS AN INTEGER WHICH IS FILE INDEX OR A NEGATIVE VALUE
															//IF THERE IS AN ERROR
	int flag = -1;
	int i=1,k=0,f=0;

	while(f <6)
		options[f++] = '0';

	while(i < argcount){
		k=0;												//LOGIC FOR EXTRACTION OF OPTIONS FROM PASSED ARGUMENT
		if(arg[i][k++]=='-'){
			while(arg[i][k]!='\0'){

				switch(arg[i][k]){

					case 'l' :	l_line = 1;
								break;
					case 'w' :	w_word = 1;
								break;
					case 'm' :	m_char = 1;
								break;
					case 'L' :	L_maxline = 1;
								break;
					case 'c' :	c_byte = 1;
								break;

					default  :	printf("wc :invalid option -- '%c'\nTry 'wc --help' for more information.\n", arg[i][k]); //-7 denotes invalid options
								return -7;

				}
				k++;
			}
		}
		else{
			//files[f++] = argv[i];
			flag = i;
		}

		i++;
	}

	return flag;


}

int main(int argc, char* argv[]){
	int ip_f,i,state = OUT;
	unsigned long int nc=0,nb=0,nw=0,nl=0,Max_len=0;				//FREQUENCY COUNTER FOR EACH CASE
	
	char buffer [16];
	
	if(argc == 2){
		l_line = w_word = m_char =1;
		ip_f = 1;
	}	
	else
		ip_f = parseCommand(argc,argv);							//EXTRACT THE OPTIONS AND INPUT FILE

	int file_des = open(argv[ip_f],O_RDONLY);

	if(ip_f < 0)
		return 0;

	i=0;
	ssize_t len =0;

	if(file_des == -1){
		printf("%s : No such file or directory\n",argv[ip_f] );			//IF INVALID PATH NAME
		return 0;
		
	}
	else{
		int temp=0;
		Max_len=0;
		while((len = read(file_des,buffer,16)) != 0){		//READ THE INPUT FILE
			i=0;
			while(i<len){
				
				temp++;
				if(buffer[i] == '\t')
					temp +=3;
				nb++;
				if(buffer[i] == '\n'){
					nl++;
					if(temp > Max_len)
						Max_len = temp;
					temp =0;
				}
				if(buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t'){
					state = OUT;
				}
				else if(state == OUT){
					state = IN;
					++nw;
				}
				i++;				
			}
				
		}

		if(temp > Max_len)
			Max_len = temp;
	}
	nc=nb;
	

	if(l_line == 1){								//FLAGS FOR THE OPTIONS
		printf("%lu  ",nl);				
	}
	if(w_word == 1){
		printf("%lu  ",nw);
	}
	if(m_char == 1){
		printf("%lu  ",nc);
	}
	if(c_byte == 1){
		printf("%lu  ",nb);
	}
	if(L_maxline == 1){
		printf("%lu  ",Max_len-1);
	}
			

	printf("%s\n",argv[ip_f]);
	

	return 0;

}
