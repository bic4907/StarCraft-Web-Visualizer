#pragma once
#include "BWAPI.h"
#include "ExtracterUnit.h"
#include "ExtracterPlayerInfo.h"

#include <vector>

using namespace BWAPI;
using namespace std;

class Frame {
public:
	Frame();

	void addUnit(ExtracterUnit u);
	vector<ExtracterUnit>* getUnits();

	void clear();
private:


	vector<ExtracterUnit> units;
};