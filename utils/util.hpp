#pragma once
#include "common.hpp"

class Util {
private:
  Util() {}
  ~Util() {}

public:
  static void checkFolder(const string &name, bool del_exists = false);
  static string Trim(const string &str);
  static vector<string> Split(const string &str, const string &delim,
                              bool trim_flag = true);

private:
  static void deleteDir(const char *dirname);
};

string Util::Trim(const string &str) {
  auto tmp = str;

  // erase whitespace before the string
  string::iterator it1;
  for (it1 = tmp.begin(); it1 < tmp.end(); it1++) {
    if (!isspace(*it1))
      break;
  }
  tmp.erase(0, it1 - tmp.begin());

  // erase whitespace after the string
  string::reverse_iterator it2;
  for (it2 = tmp.rbegin(); it2 < tmp.rend(); it2++) {
    if (!isspace(*it2))
      break;
  }
  tmp.erase(tmp.rend() - it2, it2 - tmp.rbegin());

  return tmp;
}

vector<string> Util::Split(const string &str, const string &delim,
                           bool trim_flag) {
  vector<string> result;

  string::size_type start = 0;
  string::size_type pos = 0;
  do {
    pos = str.find_first_of(delim, start);

    int len = (pos == string::npos) ? (str.size() - start) : (pos - start);
    if (len) {
      string substring = str.substr(start, len);
      string substr = trim_flag ? Util::Trim(substring) : substring;
      if (!substr.empty()) {
        result.emplace_back(substr);
      }
    }
    start = pos + 1;
  } while (pos != string::npos);

  return result;
}
void Util::checkFolder(const string &name, bool del_exists) {
  // log folder exists, return
  if (access(name.c_str(), R_OK | W_OK | X_OK) == 0) {
    if (del_exists)
      deleteDir(name.c_str());
    else
      return;
  }
  // log folder doesn't exist, create it
  if (mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
    LOG(ERROR) << "mkdir error: " << name << endl;
    abort();
  }
  LOG(INFO) << "Create folder: " << name << endl;
}

void Util::deleteDir(const char *fname) {
  struct stat buf;
  if (lstat(fname, &buf) == -1) {
    LOG(ERROR) << fname << " stat error: " << strerror(errno) << endl;
    abort();
  }
  // handle symbol link
  if (S_ISLNK(buf.st_mode)) {
    unlink(fname);
    return;
  }
  // handle common file
  if (S_ISREG(buf.st_mode)) {
    remove(fname);
    return;
  }
  // handle not directory
  if (!S_ISDIR(buf.st_mode)) {
    remove(fname);
    return;
  }
  // handle directory
  DIR *dir = NULL;
  char next_fname[256];
  struct dirent *ptr;
  // open directory
  if ((dir = opendir(fname)) == NULL) {
    LOG(ERROR) << fname << " opendir error: " << strerror(errno) << endl;
    abort();
  }
  while ((ptr = readdir(dir))) {
    if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
      continue;
    snprintf(next_fname, 256, "%s/%s", fname, ptr->d_name);
    deleteDir(next_fname);
  }
  if (closedir(dir) == -1) {
    LOG(ERROR) << fname << " closedir error: " << strerror(errno) << endl;
    abort();
  }
  if (rmdir(fname) == -1) {
    LOG(ERROR) << fname << " rmdir error: " << strerror(errno) << endl;
    abort();
  }
}
