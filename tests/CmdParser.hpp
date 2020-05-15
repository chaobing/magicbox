#pragma once

#include "config.hpp"
#include "logmgr.hpp"

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

void CmdParser::parse_cmd() {
  int opt = 0;
  const char *optstring = "o:d:vh";
  while ((opt = getopt(argc_, argv_, optstring)) != -1) {
    switch (opt) {
    case 'o':
      MagicCfg::Instance()->set_output_dir(optarg);
      break;
    case 'd':
      MagicCfg::Instance()->parse_dump_flag(optarg);
      break;
    case 'v':
      cout << MagicCfg::Instance()->tag();
      cout << MagicCfg::Instance()->magic_version_string();
      exit(-1);
    case 'h':
    default:
      cmd_helper();
      exit(1);
    }
  }
}

void CmdParser::cmd_helper(){
  std::cout << argv_[0] << " usage: " << std::endl
            << "\t-o not provided" << std::endl
            << "\t-d set dump_flag, use commas as delimiter, [A, B, C, all]"
            << std::endl
            << "\t-v version" << std::endl
            << "\t-h help" << std::endl;
}
