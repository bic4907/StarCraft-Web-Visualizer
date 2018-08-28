#include "Config.h"

using namespace UnitTypes;

Config* Config::instance = NULL;

Config::Config() {}
Config::~Config() {}



Config* Config::getInstance() {
	if (instance == NULL) {
		instance = new Config();
		instance->SETUP();
	}
	return instance;
}

void Config::SETUP() {

	saveType.push_back(Terran_Firebat);
	saveType.push_back(Terran_Ghost);
	saveType.push_back(Terran_Goliath);
	saveType.push_back(Terran_Marine);
	saveType.push_back(Terran_Medic);
	saveType.push_back(Terran_SCV);
	saveType.push_back(Terran_Siege_Tank_Siege_Mode);
	saveType.push_back(Terran_Siege_Tank_Tank_Mode);
	saveType.push_back(Terran_Vulture);
	saveType.push_back(Terran_Vulture_Spider_Mine);

	saveType.push_back(Terran_Battlecruiser);
	saveType.push_back(Terran_Dropship);
	saveType.push_back(Terran_Nuclear_Missile);
	saveType.push_back(Terran_Science_Vessel);
	saveType.push_back(Terran_Valkyrie);
	saveType.push_back(Terran_Wraith);

	saveType.push_back(Terran_Academy);
	saveType.push_back(Terran_Armory);
	saveType.push_back(Terran_Barracks);
	saveType.push_back(Terran_Bunker);
	saveType.push_back(Terran_Command_Center);
	saveType.push_back(Terran_Engineering_Bay);
	saveType.push_back(Terran_Factory);
	saveType.push_back(Terran_Missile_Turret);
	saveType.push_back(Terran_Refinery);
	saveType.push_back(Terran_Science_Facility);
	saveType.push_back(Terran_Starport);
	saveType.push_back(Terran_Supply_Depot);

	saveType.push_back(Terran_Comsat_Station);
	saveType.push_back(Terran_Control_Tower);
	saveType.push_back(Terran_Covert_Ops);
	saveType.push_back(Terran_Machine_Shop);
	saveType.push_back(Terran_Nuclear_Silo);
	saveType.push_back(Terran_Physics_Lab);

	saveType.push_back(Protoss_Archon);
	saveType.push_back(Protoss_Dark_Archon);
	saveType.push_back(Protoss_Dark_Templar);
	saveType.push_back(Protoss_Dragoon);
	saveType.push_back(Protoss_High_Templar);
	saveType.push_back(Protoss_Probe);
	saveType.push_back(Protoss_Reaver);
	saveType.push_back(Protoss_Scarab);
	saveType.push_back(Protoss_Zealot);

	saveType.push_back(Protoss_Arbiter);
	saveType.push_back(Protoss_Carrier);
	saveType.push_back(Protoss_Corsair);
	saveType.push_back(Protoss_Interceptor);
	saveType.push_back(Protoss_Observer);
	saveType.push_back(Protoss_Scout);
	saveType.push_back(Protoss_Shuttle);

	saveType.push_back(Protoss_Arbiter_Tribunal);
	saveType.push_back(Protoss_Assimilator);
	saveType.push_back(Protoss_Citadel_of_Adun);
	saveType.push_back(Protoss_Cybernetics_Core);
	saveType.push_back(Protoss_Fleet_Beacon);
	saveType.push_back(Protoss_Forge);
	saveType.push_back(Protoss_Gateway);
	saveType.push_back(Protoss_Nexus);
	saveType.push_back(Protoss_Observatory);
	saveType.push_back(Protoss_Photon_Cannon);
	saveType.push_back(Protoss_Pylon);
	saveType.push_back(Protoss_Robotics_Facility);
	saveType.push_back(Protoss_Robotics_Support_Bay);
	saveType.push_back(Protoss_Shield_Battery);
	saveType.push_back(Protoss_Stargate);
	saveType.push_back(Protoss_Templar_Archives);

	saveType.push_back(Zerg_Broodling);
	saveType.push_back(Zerg_Defiler);
	saveType.push_back(Zerg_Drone);
	saveType.push_back(Zerg_Egg);
	saveType.push_back(Zerg_Hydralisk);
	saveType.push_back(Zerg_Infested_Terran);
	saveType.push_back(Zerg_Larva);
	saveType.push_back(Zerg_Lurker);
	saveType.push_back(Zerg_Lurker_Egg);
	saveType.push_back(Zerg_Ultralisk);
	saveType.push_back(Zerg_Zergling);

	saveType.push_back(Zerg_Cocoon);
	saveType.push_back(Zerg_Devourer);
	saveType.push_back(Zerg_Guardian);
	saveType.push_back(Zerg_Mutalisk);
	saveType.push_back(Zerg_Overlord);
	saveType.push_back(Zerg_Queen);
	saveType.push_back(Zerg_Scourge);

	saveType.push_back(Zerg_Creep_Colony);
	saveType.push_back(Zerg_Defiler_Mound);
	saveType.push_back(Zerg_Evolution_Chamber);
	saveType.push_back(Zerg_Extractor);
	saveType.push_back(Zerg_Greater_Spire);
	saveType.push_back(Zerg_Hatchery);
	saveType.push_back(Zerg_Hive);
	saveType.push_back(Zerg_Hydralisk_Den);
	saveType.push_back(Zerg_Infested_Command_Center);
	saveType.push_back(Zerg_Lair);
	saveType.push_back(Zerg_Nydus_Canal);
	saveType.push_back(Zerg_Queens_Nest);
	saveType.push_back(Zerg_Spawning_Pool);
	saveType.push_back(Zerg_Spire);
	saveType.push_back(Zerg_Spore_Colony);
	saveType.push_back(Zerg_Sunken_Colony);
	saveType.push_back(Zerg_Ultralisk_Cavern);


	unitCode[Terran_Marine] = 0;
	unitCode[Terran_Ghost] = 1;
	unitCode[Terran_Vulture] = 2;
	unitCode[Terran_Goliath] = 3;
	unitCode[Terran_Siege_Tank_Tank_Mode] = 5;
	unitCode[Terran_SCV] = 7;
	unitCode[Terran_Wraith] = 8;
	unitCode[Terran_Science_Vessel] = 9;
	unitCode[Terran_Dropship] = 11;
	unitCode[Terran_Battlecruiser] = 12;
	unitCode[Terran_Vulture_Spider_Mine] = 13;
	unitCode[Terran_Nuclear_Missile] = 14;
	unitCode[Terran_Civilian] = 15;
	unitCode[Terran_Siege_Tank_Siege_Mode] = 30;
	unitCode[Terran_Firebat] = 32;

	unitCode[Terran_Medic] = 34;
	unitCode[Zerg_Larva] = 35;
	unitCode[Zerg_Egg] = 36;
	unitCode[Zerg_Zergling] = 37;
	unitCode[Zerg_Hydralisk] = 38;
	unitCode[Zerg_Ultralisk] = 39;
	unitCode[Zerg_Broodling] = 40;
	unitCode[Zerg_Drone] = 41;
	unitCode[Zerg_Overlord] = 42;
	unitCode[Zerg_Mutalisk] = 43;
	unitCode[Zerg_Guardian] = 44;
	unitCode[Zerg_Queen] = 45;
	unitCode[Zerg_Defiler] = 46;
	unitCode[Zerg_Scourge] = 47;
	unitCode[Zerg_Infested_Terran] = 50;
	unitCode[Terran_Valkyrie] = 58;
	unitCode[Zerg_Cocoon] = 59;
	unitCode[Protoss_Corsair] = 60;
	unitCode[Protoss_Dark_Templar] = 61;
	unitCode[Zerg_Devourer] = 62;
	unitCode[Protoss_Dark_Archon] = 63;
	unitCode[Protoss_Probe] = 64;
	unitCode[Protoss_Zealot] = 65;
	unitCode[Protoss_Dragoon] = 66;
	unitCode[Protoss_High_Templar] = 67;
	unitCode[Protoss_Archon] = 68;
	unitCode[Protoss_Shuttle] = 69;
	unitCode[Protoss_Scout] = 70;
	unitCode[Protoss_Arbiter] = 71;
	unitCode[Protoss_Carrier] = 72;
	unitCode[Protoss_Interceptor] = 73;
	unitCode[Protoss_Reaver] = 83;
	unitCode[Protoss_Observer] = 84;
	unitCode[Protoss_Scarab] = 85;
	unitCode[Critter_Rhynadon] = 89;
	unitCode[Critter_Bengalaas] = 90;
	unitCode[Critter_Scantid] = 93;
	unitCode[Critter_Kakaru] = 94;
	unitCode[Critter_Ragnasaur] = 95;
	unitCode[Critter_Ursadon] = 96;
	unitCode[Zerg_Lurker_Egg] = 97;
	unitCode[Zerg_Lurker] = 103;
													   
	unitCode[Terran_Command_Center] = 106;
	unitCode[Terran_Comsat_Station] = 107;
	unitCode[Terran_Nuclear_Silo] = 108;
	unitCode[Terran_Supply_Depot] = 109;
	unitCode[Terran_Refinery] = 110;
	unitCode[Terran_Barracks] = 111;
	unitCode[Terran_Academy] = 112;
	unitCode[Terran_Factory] = 113;
	unitCode[Terran_Starport] = 114;
	unitCode[Terran_Control_Tower] = 115;
	unitCode[Terran_Science_Facility] = 116;
	unitCode[Terran_Covert_Ops] = 117;
	unitCode[Terran_Physics_Lab] = 118;
	unitCode[Terran_Machine_Shop] = 120;
	unitCode[Terran_Engineering_Bay] = 122;
	unitCode[Terran_Armory] = 123;
	unitCode[Terran_Missile_Turret] = 124;
	unitCode[Terran_Bunker] = 125;
	unitCode[Zerg_Infested_Command_Center] = 130;
	unitCode[Zerg_Hatchery] = 131;
	unitCode[Zerg_Lair] = 132;
	unitCode[Zerg_Hive] = 133;
	unitCode[Zerg_Nydus_Canal] = 134;
	unitCode[Zerg_Hydralisk_Den] = 135;
	unitCode[Zerg_Defiler_Mound] = 136;
	unitCode[Zerg_Greater_Spire] = 137;
	unitCode[Zerg_Queens_Nest] = 138;
	unitCode[Zerg_Evolution_Chamber] = 139;
	unitCode[Zerg_Ultralisk_Cavern] = 140;
	unitCode[Zerg_Spire] = 141;
	unitCode[Zerg_Spawning_Pool] = 142;
	unitCode[Zerg_Creep_Colony] = 143;
	unitCode[Zerg_Spore_Colony] = 144;
	unitCode[Zerg_Sunken_Colony] = 146;
	unitCode[Zerg_Extractor] = 149;
	unitCode[Protoss_Nexus] = 154;
	unitCode[Protoss_Robotics_Facility] = 155;
	unitCode[Protoss_Pylon] = 156;
	unitCode[Protoss_Assimilator] = 157;
	unitCode[Protoss_Observatory] = 159;
	unitCode[Protoss_Gateway] = 160;
	unitCode[Protoss_Photon_Cannon] = 162;
	unitCode[Protoss_Citadel_of_Adun] = 163;
	unitCode[Protoss_Cybernetics_Core] = 164;
	unitCode[Protoss_Templar_Archives] = 165;
	unitCode[Protoss_Forge] = 166;
	unitCode[Protoss_Stargate] = 167;
	unitCode[Protoss_Fleet_Beacon] = 169;
	unitCode[Protoss_Arbiter_Tribunal] = 170;
	unitCode[Protoss_Robotics_Support_Bay] = 171;
	unitCode[Protoss_Shield_Battery] = 172;

}



bool Config::isSaveType(UnitType ut) {
	auto& iter = find(saveType.begin(), saveType.end(), ut);
	if (iter != saveType.end()) {
		return true;
	}
	else {
		return false;
	}
}

string Config::getFilename(UnitType ut) {
	return ut.c_str();
}

int Config::getUnitCode(UnitType ut) {
	return unitCode.find(ut)->second;
}