#pragma once
#include "BWAPI.h"
#include <string>
#include <algorithm>
#include <map>

using namespace std;
using namespace BWAPI;


class Config {
	
public:
	static Config* getInstance();

	bool isSaveType(UnitType ut);
	string getFilename(UnitType ut);
	int getUnitCode(UnitType ut);

private:

	Config(); 
	~Config();

	static Config* instance;

	vector<UnitType> saveType;
	map<UnitType, int> unitCode;

	void SETUP();

};
