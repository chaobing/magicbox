#pragma once

#include <iostream>
#include <unistd.h>
#include "LogMgr.hpp"

class CmdParser{
	public:
		CmdParser(int argc, char **argv):
			argc_(argc),
			argv_(argv),
			log_mgr_(argv_[0], "./log/")
		{
			parse_cmd();
		}
		~CmdParser()	{ }
	public:
		void parse_cmd();
		void cmd_helper();

	private:
		int argc_;
		char **argv_;
		LogMgr log_mgr_;
};

void CmdParser::parse_cmd(){
	int opt = 0;
	const char *optstring = "a:vh";
	while((opt = getopt(argc_, argv_, optstring)) != -1){
		switch(opt){
			case 'a':
				std::cout <<"not provided"<<std::endl;
				break;
			case 'v':
				std::cout <<"cmake sample 0.0"<<std::endl;
				exit(-1);
			case 'h':
			default:
				cmd_helper();
				exit(1);
		}
	}
}

void CmdParser::cmd_helper(){
	std::cout<< argv_[0] << "usage: " <<std::endl
		<<"\t-a not provided" <<std::endl
		<<"\t-v version"<<std::endl
		<<"\t-h help"<<std::endl;
}
