#pragma once

#include "common.hpp"
#include "util.hpp"

class LogMgr {
public:
  LogMgr(const string &program, const string &debug_path) {
    FLAGS_log_dir = debug_path;
    google::InitGoogleLogging(program.data());
    FLAGS_stderrthreshold = google::WARNING;
    FLAGS_colorlogtostderr = true;
    FLAGS_logbufsecs = 0;
    FLAGS_v = 0;

    Util::checkFolder(debug_path, true);
    LOG(INFO) << "create log directory success!" << endl;
  }
  ~LogMgr() { google::ShutdownGoogleLogging(); }
};
