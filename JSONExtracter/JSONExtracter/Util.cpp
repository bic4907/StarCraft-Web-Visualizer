#include "Util.h"

bool Util::isExist(const char* path) {
	return !_access(path, 0);
}

bool Util::makeDir(const char* path) {
	return _mkdir(path);
}

bool Util::copyFile(const char* _src, const char* _dest) {
	ifstream src(_src, ios::binary);
	ofstream dest(_dest, ios::binary);
	dest << src.rdbuf();

	return true;
}

bool Util::isExist(string path) { return Util::isExist(path.c_str()); }
bool Util::makeDir(string path) { return Util::makeDir(path.c_str()); }
bool Util::copyFile(string _src, string _dest) { return Util::copyFile(_src.c_str(), _dest.c_str()); }