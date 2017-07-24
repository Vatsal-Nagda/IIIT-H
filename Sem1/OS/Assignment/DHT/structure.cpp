#include <bits/stdc++.h>

using namespace std;

struct Cell_Entry{
	string ip_addr;
	int port;
	int NodeId;
};

struct Node_data{
	Cell_Entry Leafset[4];
	Cell_Entry Routing_Table[8][4];
};

struct Packet{
	enum message_type { 'JOIN','PUT','GET' };
	string ip_addr;
	int port;
	pair <int,string> message;
};

struct Dist_Hash_Tbl{
	map < int , string > DHT;
};



int main(){


	return 0;
}