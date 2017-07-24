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
}