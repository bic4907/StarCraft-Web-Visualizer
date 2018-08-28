#include "Frame.h"
#include "DataManager.h"

Frame::Frame() {
	this->units.clear();
}

void Frame::addUnit(ExtracterUnit u) {
	units.push_back(u);
}

vector<ExtracterUnit>* Frame::getUnits() {
	return &units;
}

void Frame::clear() {
	units.clear();
}