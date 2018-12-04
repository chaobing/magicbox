#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <string>
#include <glog/logging.h>

using std::string;
using std::endl;

class DirHelper{
	private:
		DirHelper() {}
		~DirHelper() {}
	public:	
		static void checkFolder(const string &name, bool del_exists = false);
	private:
		static void deleteDir(const char * dirname);
};

void DirHelper::checkFolder(const string &name, bool del_exists){
	// log folder exists, return
	if(access(name.c_str(), R_OK | W_OK | X_OK) == 0) {
		if(del_exists)
			deleteDir(name.c_str());
		else
			return;
	}
	// log folder doesn't exist, create it
	if(mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
		LOG(ERROR) << "mkdir error: " << name << endl;
			abort();
	}
	LOG(INFO) << "Create folder: " << name << endl;
}
		
void DirHelper::deleteDir(const char *fname){
	struct stat buf;
	if(lstat(fname, &buf) == -1) {
		LOG(ERROR) << fname << " stat error: " << strerror(errno) << endl;
		abort();
	}
	// handle symbol link
	if(S_ISLNK(buf.st_mode)) {
		unlink(fname);
		return;
	}
	// handle common file
	if(S_ISREG(buf.st_mode)) {
		remove(fname);
		return;
	}
	// handle not directory
	if(!S_ISDIR(buf.st_mode)) {
		remove(fname);
		return;
	}
	// handle directory
	DIR *dir = NULL;
	char next_fname[256];
	struct dirent *ptr;
	// open directory
	if((dir = opendir(fname)) == NULL) {
		LOG(ERROR) << fname << " opendir error: " << strerror(errno) << endl;
		abort();
	}
	while((ptr = readdir(dir))) {
		if((strcmp(ptr->d_name, ".") == 0)|| (strcmp(ptr->d_name, "..") == 0))
			continue;
		snprintf(next_fname, 256, "%s/%s", fname, ptr->d_name);
		deleteDir(next_fname);
	}
	if(closedir(dir) == -1) {
		LOG(ERROR) << fname << " closedir error: " << strerror(errno) << endl;
		abort();
	}
	if(rmdir(fname) == -1) {
		LOG(ERROR) << fname << " rmdir error: " << strerror(errno) << endl;
		abort();
	}
}

