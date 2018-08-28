#pragma once
#include "BWAPI.h"

using namespace BWAPI;

class ExtracterPlayerInfo;

class ExtracterUnit {


	public:
		ExtracterUnit();
		ExtracterUnit(Unit u, bool visibleToEnemy);

		TilePosition pos;
		TilePosition target_pos;

		int shield;
		int max_shield;

		int health;
		int max_health;

		bool visibleToEnemy;

		int sight;

		UnitType type;

		int owner;

	private:
		



};
