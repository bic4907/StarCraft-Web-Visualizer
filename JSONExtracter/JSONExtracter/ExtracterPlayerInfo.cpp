#include "ExtracterPlayerInfo.h"

ExtracterPlayerInfo::ExtracterPlayerInfo() {}

ExtracterPlayerInfo::ExtracterPlayerInfo(int id, string name, string tribe, Player p) {
	this->id = id;
	this->name = name;
	this->tribe = tribe;
	this->player = p;
}