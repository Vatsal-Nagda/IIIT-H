#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>

using namespace std;

int main(){
	fstream repoFile;
	string first,second,third;

	string str ="This is vatsal\n he is doing OS\n";

	std::istringstream f(str);
    std::string line;    
    while (std::getline(f, line)) {
        std::cout << line << std::endl;
    }
	/*repoFile.open("repo.txt",ios::app );
	first = "d.mp3";
	second = "172.17.12.17";
	third = "./home/usr/abc/pqr";
	repoFile<<"\n"+first+" "+second+" "+third;
	repoFile.close();
*/
	if(access("repo123.txt",F_OK) == -1){
    		///file doesnt exist suitable error
		cout <<"The file you are looking for doesnt exist here.!!"<<endl;

   	}
	else{
		repoFile.open("repo123.txt",ios::in );
		cout <<"Reading the first line from file\n";
		string line;
		//getline(repoFile,line,'#');
		while(!(repoFile.eof())){
			/*cout<<line<<endl;	*/
			repoFile >>first>>second>>third;
		cout << "The lines are\n"<<first<<" "<<second<<" "<<third<<endl;
		}
		/*repoFile >>first>>second>>third;
		cout << "The lines are\n"<<first<<" "<<second<<" "<<third<<endl;
		repoFile >>first>>second>>third;
		cout << "The lines are\n"<<first<<" "<<second<<" "<<third<<endl;
		repoFile >>first>>second>>third;
		cout << "The lines are\n"<<first<<" "<<second<<" "<<third<<endl;
		repoFile >>first>>second>>third;
		cout << "The lines are\n"<<first<<" "<<second<<" "<<third<<endl;
		*/repoFile.close();
	}

	return 0;
}