#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

string hash_value(string ip_addr){
  char buffer [1024];
  string final_hash_val;

  FILE *hash_val=popen(("echo "+ip_addr+"|md5sum").c_str(),"r");
	fgets(buffer,1024,hash_val);
	final_hash_val = string(buffer);
	final_hash_val = final_hash_val.substr(0,4);
    string ans="";
    /*unsigned int x;   
    std::stringstream ss;
    ss << std::hex << final_hash_val;
    ss >> x;

    int num = static_cast<int>(x);
    vector<int > rem;*/


    for (int i=0;i<4;i++){
        switch(final_hash_val[i]){
            case '0': ans+="00";break;
            case '1': ans+="01";break;
            case '2': ans+="02";break;
            case '3': ans+="03";break;
            case '4': ans+="10";break;
            case '5': ans+="11";break;
            case '6': ans+="12";break;
            case '7': ans+="13";break;
            case '8': ans+="20";break;
            case '9': ans+="21";break;
            case 'a': ans+="22";break;
            case 'b': ans+="23";break;
            case 'c': ans+="30";break;
            case 'd': ans+="31";break;
            case 'e': ans+="32";break;
            case 'f': ans+="33";break;
        }

    }

    return ans;
}