#pragma once
#include "DataManager.h"

using namespace std;
using namespace BWAPI;


class UnitFound {

private:


public:
	int id;
	UnitType type;
	Position pos;
	int owner;

	int frameCount;

	UnitFound();
	UnitFound(Unit u, int frameCount);
	~UnitFound();
};
