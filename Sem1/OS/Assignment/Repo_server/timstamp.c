#include <iostream>
#include <ctime>

int main()
{
  time_t currentTime;
  struct tm *localTime;

  time( &currentTime );                   // Get the current time
  localTime = localtime( &currentTime );  // Convert the current time to the local time

  int Day    = localTime->tm_mday;
  int Month  = localTime->tm_mon + 1;
  int Year   = localTime->tm_year + 1900;
  int Hour   = localTime->tm_hour;
  int Min    = localTime->tm_min;
  int Sec    = localTime->tm_sec;

  std::cout << "This program was exectued at: " << Hour << ":" << Min << ":" << Sec << std::endl;
  std::cout << "And the current date is: " << Day << "/" << Month << "/" << Year << std::endl;
  return 0;
}
 
/*

void log(char code, char *addr_buf)

{

	ofstream log;
	log.open ("repo.log",std::ofstream::app);

	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	log <<now->tm_mday << '-' << (now->tm_mon + 1) << '-' <<  (now->tm_year+1900)<<' '<< now->tm_hour <<'-'<<now->tm_min<<'-'<<now->tm_sec;
	
	if(code=='1')
		log<<"	Search request from: "<<addr_buf<<endl;

	if(code=='2')
		log<<"	Share request from: "<<addr_buf<<endl;

	log.close();
}*/

