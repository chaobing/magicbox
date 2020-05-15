
#include "cmdParser.hpp"
#include "logmgr.hpp"
#include "point.hpp"

int main(int argc, char **argv) {
  CmdParser cp(argc, argv);

  cout << "output_dir " << MagicCfg::Instance()->output_dir() << endl;
  LOG(INFO) << " construct point 0" << endl;
  Point p0;
  if (MagicCfg::Instance()->dump_flag() & DumpA) {
    cout << "do dump A" << endl;
  }
  p0.show();

  LOG(INFO) << " construct point 1" << endl;
  Point p1(10, 20);
  if (MagicCfg::Instance()->dump_flag() & DumpC) {
    cout << "do dump C" << endl;
  }
  p1.show();

  return 0;
}
