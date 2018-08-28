#pragma once

#include <string>
#include <fstream>
#include <direct.h>
#include <io.h>
using namespace std;


class Util {
public:

	static bool isExist(string path);
	static bool makeDir(string path);
	static bool copyFile(string src, string dest);

	static bool isExist(const char* path);
	static bool makeDir(const char* path);
	static bool copyFile(const char* src, const char* dest);
};
