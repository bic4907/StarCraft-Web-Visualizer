#include <iostream>
#include <fstream>
#include "JSONExtracter.h"
#include "DataManager.h"
#include "Config.h"
#include "Util.h"


//Edit this (Config)
#define CAPTURE_SECOND_INTERVAL 1
#define INITIAL_SKIP_SECONDS 180
#define MAX_GAME_SECONDS 1500
#define PREVIEW_SECONDS 180
////////////


//Do Not Edit (Const)
#define FRAME_PER_SECOND		24
#define CAPTURE_FRAME_INTERVAL	CAPTURE_SECOND_INTERVAL * FRAME_PER_SECOND
#define INITIAL_SKIP_FRAME		INITIAL_SKIP_SECONDS * FRAME_PER_SECOND
#define MAX_GAME_SECONDS_FRAME	MAX_GAME_SECONDS * FRAME_PER_SECOND
#define CAPTURE_START_FRAME		(INITIAL_SKIP_SECONDS - PREVIEW_SECONDS) * FRAME_PER_SECOND
////////////

using namespace BWAPI;
using namespace std;


void JSONExtracter::onStart()
{
	string filePath = Broodwar->mapPathName();
	string fileDir = filePath.erase(filePath.length() - Broodwar->mapFileName().length(), Broodwar->mapFileName().length());
	
	if (!Util::isExist("C:\\StarData")) {
		Util::makeDir("C:\\StarData");
	}
	if (!Util::isExist("C:\\StarData\\Done")) {
		Util::makeDir("C:\\StarData\\Done");
	}
	if (!Util::isExist("C:\\StarData\\JSON")) {
		Util::makeDir("C:\\StarData\\JSON");
	}
	//if (!Util::isExist("C:\\StarData\\Log")) {
	//	Util::makeDir("C:\\StarData\\Log");
	//}


	if (Util::isExist("C:\\StarData\\Done\\" + Broodwar->mapFileName()) || Broodwar->getReplayFrameCount() < CAPTURE_START_FRAME) {
		DataManager::isBrokenReplay = true;
		Broodwar->leaveGame();
	}

	Util::copyFile("C:\\Starcraft\\maps\\StarData\\" + Broodwar->mapFileName(), "C:\\StarData\\Done\\" + Broodwar->mapFileName());


	if (Broodwar->isReplay())
	{
		Broodwar->setGUI(true);
		Broodwar->setLocalSpeed(0);
	}

	Playerset players = Broodwar->getPlayers();

	DataManager* dm = DataManager::getInstance();
	dm->initalize();

	dm->setMapName(Broodwar->mapName());
	dm->setMapSize(Broodwar->mapWidth(), Broodwar->mapHeight());
	dm->setMapHash();
	dm->setFileName(Broodwar->mapFileName());

	dm->setEnvironment("CAPTURE_SECOND_INTERVAL", CAPTURE_SECOND_INTERVAL);
	dm->setEnvironment("INITIAL_SKIP_SECONDS", INITIAL_SKIP_SECONDS);
	dm->setEnvironment("PREVIEW_SECONDS", PREVIEW_SECONDS);

	for (Player p : players) {
		if (p->isObserver()) continue;
		dm->setPlayer(p);
	}
	Broodwar->setFrameSkip(50000);

	dm->saveJSON(DataManager::STATE::START);
}

void JSONExtracter::onFrame()
{
	if ((Broodwar->getFrameCount() % 24) != 0) return;
	if (Broodwar->getFrameCount() <= CAPTURE_START_FRAME) return;
	if (Broodwar->getFrameCount() > MAX_GAME_SECONDS_FRAME) Broodwar->leaveGame();



	DataManager* dm = DataManager::getInstance();
	Config* cfg = Config::getInstance();

	Playerset ps = dm->getPlayerset();

	Player p1 = *(ps.begin());
	Player p2 = *(next(ps.begin())); 

	Unitset units;
	ExtracterPlayerInfo* epi1 = dm->getPlayerInfo(p1);
	ExtracterPlayerInfo* epi2 = dm->getPlayerInfo(p2);


	if (p1->getUnits().size() == 0 || p2->getUnits().size() == 0) return;

	units = p1->getUnits();

	for (Unit u : units) {
		//if(cfg->isSaveType(u->getType())) {
		{
			ExtracterUnit eu = ExtracterUnit(u, u->isVisible(p2));

			//Player1ÀÇ À¯´ÖÀúÀå
			dm->getFrame()->addUnit(eu);
			
			// Update For CIG
			if (u->isVisible(p2)) {
				if (!(dm->isRecorded(u->getID())) && (
						u->getType() == UnitTypes::Terran_Command_Center ||
						u->getType() == UnitTypes::Protoss_Nexus ||
						u->getType() == UnitTypes::Zerg_Hatchery
				)) {
					Broodwar << "Catched By p2" << endl;
					dm->recordUnit(u, Broodwar->getFrameCount());
				}
			}
		}
	}

	units = p2->getUnits();

	for (Unit u : units) {
		//if (cfg->isSaveType(u->getType())) {
		{
			ExtracterUnit eu = ExtracterUnit(u, u->isVisible(p1));

			//Player2ÀÇ À¯´ÖÀúÀå
			dm->getFrame()->addUnit(eu);

			// Update For CIG
			if (u->isVisible(p1)) {
				if (!(dm->isRecorded(u->getID())) && (
					u->getType() == UnitTypes::Terran_Command_Center ||
					u->getType() == UnitTypes::Protoss_Nexus ||
					u->getType() == UnitTypes::Zerg_Hatchery
				)) {
					Broodwar << "Catched By p1" << endl;
					dm->recordUnit(u, Broodwar->getFrameCount());
				}
			}
		}
	}
	dm->saveJSON(DataManager::STATE::FRAME);
	dm->getFrame()->clear();
}


void JSONExtracter::onEnd(bool isWinner)
{
	DataManager::getInstance()->saveJSON(DataManager::STATE::END);
	//thread t = thread(&DataManager::saveJSON, DataManager::getInstance(), "temp2.json");
	//thread t = thread(&DataManager::saveJSON, DataManager::getInstance());
	//t.join();
}


