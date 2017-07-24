#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct process{
	int pid;
	int arrival,burst;
	int Run;
	int priority;
	int response;
	int completion;
};

bool mycomparator(const struct process &a, const struct process &b)
{
    if(a.arrival < b.arrival)
    	return true;
    else if((a.arrival == b.arrival) && (a.priority < b.priority))
    	return true;
    else if((a.arrival == b.arrival) && (a.priority == b.priority) && (a.pid < b.pid))
    	return true;

    return false;
}

bool finalComp(const struct process &a, const struct process &b){
	return a.pid < b.pid;
}

vector<process> check_process(vector<process> &input_processes,int curr_time){
	vector<process>  temp;
	
	vector<process> ::iterator it;
	if(!input_processes.empty())
		for( it = input_processes.begin();it!=input_processes.end();it++){
			if(it->arrival == curr_time){
				temp.push_back(*it);
			}
		}
	return temp;
}

bool FPS_comp(const struct process &a, const struct process &b){
	return a.priority < b.priority;
}

int find_next_arrival(vector<process> &input_processes,int curr_time){
	vector<process> ::iterator it;
	if(!input_processes.empty()){
		for(it = input_processes.begin();it!=input_processes.end();it++){
			if(it->arrival >= curr_time){
				return it->arrival;
			}
		}
	}
}

int main(int argc, char *argv[]){

	/* File I/O */
	fstream fin,fout;
	fin.open(argv[1],fstream::in);
	fout.open(argv[2],fstream::out);

	int num_process;
	fin>>num_process;
	int count=0;

	vector<struct process> input_processes (num_process);

	for(int i=0;i<num_process;i++){
		struct process p;
		fin>>p.pid>>p.arrival>>p.burst>>p.priority;		
		p.Run=p.burst;
		input_processes[i] = p;
	}

	sort(input_processes.begin(),input_processes.end(),mycomparator);

	vector<struct process> FPS;
	queue<struct process> RR;
	vector<struct process> final;

	input_processes[0].response=0;
	FPS.push_back(input_processes[0]);		//inserted the first process to be processed
	input_processes.erase(input_processes.begin());

	int curr_time=FPS.begin()->arrival,quantum_FPS=0,quantum_RR=0;
	
	struct process temp_process=*FPS.begin();

	vector <process>t1=check_process(input_processes,curr_time);
	while(!t1.empty()){
		FPS.push_back(*t1.begin());
		t1.erase(t1.begin());
	}

	while((!FPS.empty() || !RR.empty()) || count!=num_process){
		struct process temp_process=*FPS.begin();

		while(!FPS.empty()){
			sort(FPS.begin(),FPS.end(),FPS_comp);				//sort the FPS queue based on the priority of the process

			curr_time++;
			quantum_FPS ++;			
			temp_process.burst--;
			vector<process> temp = check_process(input_processes,curr_time);		//check whichc process come at this curr_time
	//merge existing queue and received vector at this curr_time
				if(!temp.empty()){

					if(temp[0].priority <  temp_process.priority){		//a high priority process has arrived
						if(temp_process.burst<=0){
							temp_process.completion=curr_time;
							final.push_back(temp_process);
							count++;
						}
						else
							RR.push(temp_process);					//send current process to 2nd level Queue
						temp_process = temp[0];					//make new process as current process
						temp_process.response=0;				
						quantum_FPS=0;							// reset the curr_time quanta for new process
						FPS.push_back(temp_process);
						temp.erase(temp.begin());				//erase both the process from their vectors
						FPS.erase(FPS.begin());	
					}

					if(FPS.empty()){	//queue is empty so add the received vector as is 
						while(!temp.empty()){
							FPS.push_back(*temp.begin());
							temp.erase(temp.begin());
						}
					}
					else{		//have to merge both 
						FPS.insert(FPS.end(),temp.begin(),temp.end());
						sort(FPS.begin(),FPS.end(),FPS_comp);
					}
					
				}
			//}

			if(quantum_FPS == 4 || temp_process.burst<=0){

				if(temp_process.burst<=0){
					temp_process.completion=curr_time;
					final.push_back(temp_process);
					count++;
				}
				else if(quantum_FPS == 4){
					RR.push(temp_process);
				}
				FPS.erase(FPS.begin());	
				if(!FPS.empty()){
					temp_process = *FPS.begin();
					temp_process.response=(curr_time - temp_process.arrival);
				}
				quantum_FPS=0;
			}
		}

		quantum_RR=0;
		struct process RR_process;
		if(!RR.empty())
			RR_process = RR.front();
		while(!RR.empty()){
			curr_time++;
			quantum_RR++;
			RR_process.burst--;

			vector<process> temp = check_process(input_processes,curr_time);		//check whichc process come at this curr_time

			if(!temp.empty()){		//new processes arrive
				FPS.clear();
				quantum_RR=0;
				if(RR_process.burst <= 0){		//if some process in RR just cocmpletes
					RR_process.completion=curr_time;
					final.push_back(RR_process);
					count++;
				}
				else
					RR.push(RR_process);
				RR.pop();
				while(!temp.empty()){	
					FPS.push_back(*temp.begin());
					temp.erase(temp.begin());
				}
				break;
			}

			if(quantum_RR == 4 || RR_process.burst <= 0){
				if(RR_process.burst <= 0){
					RR_process.completion=curr_time;
					final.push_back(RR_process);
					count++;
				}
				else if(quantum_RR ==  4)
					RR.push(RR_process);

				RR.pop();
				if(!RR.empty())
					RR_process = RR.front();
				quantum_RR=0;
			}
		}

		if(FPS.empty() && RR.empty()){
			curr_time = find_next_arrival(input_processes,curr_time);
			vector<process> temp = check_process(input_processes,curr_time);		//check whichc process come at this curr_time
			while(!temp.empty()){
				FPS.push_back(*temp.begin());
				temp.erase(temp.begin());
			}
		}
	}

	vector<process> ::iterator fin_itr;
	sort(final.begin(),final.end(),finalComp);
	for(fin_itr = final.begin();fin_itr!=final.end();fin_itr++)
		fout<<fin_itr->pid<<" "<<fin_itr->response<<" "<<fin_itr->completion<<" "<<(fin_itr->completion-(fin_itr->arrival+fin_itr->Run))<<endl;
	return 0;
}