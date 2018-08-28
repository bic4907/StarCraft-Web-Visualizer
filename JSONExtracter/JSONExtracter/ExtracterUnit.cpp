#include "ExtracterUnit.h"

ExtracterUnit::ExtracterUnit(Unit u, bool visibleToEnemy) {

	type = u->getType();
	
	pos = u->getTilePosition();

	health = u->getHitPoints();
	max_health = u->getType().maxHitPoints();

	shield = u->getShields();
	max_shield = u->getType().maxShields();

	owner = u->getPlayer()->getID();
	sight = u->getType().sightRange();

	this->visibleToEnemy = visibleToEnemy;

	if (u->getTarget()) {
		target_pos = u->getTarget()->getTilePosition();
	}
	else if (u->getOrderTarget()) {
		target_pos = u->getOrderTarget()->getTilePosition();
	}
	else {
		target_pos = TilePosition(-1, -1);
	}

	
	
}
