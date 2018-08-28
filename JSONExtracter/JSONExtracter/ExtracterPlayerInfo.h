#pragma once
#include <BWAPI.h>
#include <string>

using namespace std;
using namespace BWAPI;

class ExtracterPlayerInfo {
public:
	int id;
	string name;
	string tribe;

	Player player;

	ExtracterPlayerInfo();
	ExtracterPlayerInfo(int id, string name, string tribe, Player p);
};