
#include "CmdParser.hpp"
#include "LogMgr.hpp"
#include "Point.hpp"

int main(int argc, char** argv){
	CmdParser cp(argc, argv);

	LOG(INFO)<<" construct point 0"<<endl;
	Point p0;
	p0.show();

	LOG(INFO)<<" construct point 1"<<endl;
	Point p1(10, 20);
	p1.show();

	return 0;
}
