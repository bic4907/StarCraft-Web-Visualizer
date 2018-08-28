#include <Windows.h>
#include <iostream>
#include <fstream>
#include <regex>
#include "DataManager.h"
#include "Config.h"
#include "md5.h"
#include "Util.h"

DataManager* DataManager::instance = NULL;
bool DataManager::isBrokenReplay = false;
bool DataManager::isFrameWrote = false;

void DataManager::initalize() {
	this->frame.clear();
}

DataManager::DataManager() {}
DataManager::~DataManager() {}

DataManager* DataManager::getInstance() {
	if (instance == NULL) {
		instance = new DataManager();
	}
	return instance;
}

//FRAME//
Frame* DataManager::getFrame() {
	return &(this->frame);
}


/* DEPARATED FROM 04.16 */
/*
void DataManager::toNextFrame() {
	frames.push_back(Frame());
}

Frame* DataManager::getCurrentFrame() {
	vector<Frame>::iterator iter = prev(frames.end());

	return &(*iter);
}

Frame* DataManager::getFrame(int index) {
	vector<Frame>::iterator iter = frames.begin() + index;
	return &(*iter);
}

unsigned int DataManager::getFrameSize() {
	return frames.size();
}
*/
//END//

//PLAYER//
vector<ExtracterPlayerInfo>* DataManager::getPlayers() {
	return &players;
}

ExtracterPlayerInfo* DataManager::getPlayerInfo(Player p) {

	vector<ExtracterPlayerInfo>* ep = getPlayers();

	for (auto& iter = ep->begin(); iter != ep->end(); iter++) {
		
		if (iter->player->getID() == p->getID()) {
		
			return &(*iter);
		}
	}
	return nullptr;
}

Playerset DataManager::getPlayerset() {
	Playerset ps;

	vector<ExtracterPlayerInfo>* ep = getPlayers();

	for (auto& iter = ep->begin(); iter != ep->end(); iter++) {
		ps.insert(iter->player);
	}

	return ps;
}
//END

void DataManager::setFileName(string s) {
	this->replayName = s;
}

void DataManager::setEnvironment(string k, int v) {
	environment[k] = v;
}

void DataManager::setMapHash() {
	string map_info = "";

	for (int i = 0; i < Broodwar->mapHeight(); i++) {
		for (int j = 0; j < Broodwar->mapWidth(); j++) {
			if (Broodwar->isWalkable(WalkPosition(j, i))) {
				map_info.append("1");
			}
			else {
				map_info.append("0");
			}
		}
	}
	this->mapHash = md5(map_info);

}
string DataManager::getMapHash() {
	return this->mapHash;
}

void DataManager::setMapSize(unsigned short width, unsigned short height) {
	this->map_width = width;
	this->map_height = height;
}
void DataManager::setMapName(string mapName) {
	this->mapName = mapName;
}
	
void DataManager::setPlayer(Player p) {
	ExtracterPlayerInfo ep = ExtracterPlayerInfo(p->getID(), p->getName(), p->getRace().getName(), p); //getRace().getName() returns "Terran", "Protoss", "Zerg"
	Broodwar << ep.player->getID() << endl;
	this->players.push_back(ep);
}

void DataManager::saveJSON(enum STATE s) {
	Config* cfg = Config::getInstance();
	
	stringstream raw_json;

	wstring output_text;
	DWORD number_of_characters_written;

	if (s == STATE::START) {
		//Console Open
		//AllocConsole();

		if (Util::isExist("C:\\StarData\\JSON\\" + Broodwar->mapFileName() + ".json")) {
			return;
		}

		//output_text = L"Writing Log\n";
		//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
		//	output_text.size(), &number_of_characters_written, nullptr);

		//ofstream of_log;

		//of_log.open("C:\\StarData\\Log\\" + Broodwar->mapFileName() + ".log");
		//of_log << "Replay File : " << Broodwar->mapFileName() << endl;
		//of_log << "Total Frame : " << Broodwar->getReplayFrameCount() << endl;
		//of_log.close();


		//output_text = L"Wrote Log\n";
		//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
		//	output_text.size(), &number_of_characters_written, nullptr);

		this->of_json.open("C:\\StarData\\JSON\\" + Broodwar->mapFileName() + ".json");

		output_text = L"Packing Game\n";
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
			output_text.size(), &number_of_characters_written, nullptr);

		raw_json << "{";
		raw_json << "\"map_name\":" << "\"" << this->mapName << "\",\n";
		raw_json << "\"map_width\":" << "\"" << this->map_width << "\",\n";
		raw_json << "\"map_height\":" << "\"" << this->map_height << "\",\n";
		//raw_json << "\"map_hash\":" << "\"" << this->getMapHash() << "\",\n";
		raw_json << "\"file_name\":" << "\"" << this->replayName << "\",\n";
		raw_json << "\"frame_count\":" << Broodwar->getReplayFrameCount() << ",\n";

		Playerset ps = this->getPlayerset();

		Player p1 = *(ps.begin());
		Player p2 = *(next(ps.begin()));

		raw_json << "\"player0\":" << "\"" << p1->getName() << "\",\n";
		raw_json << "\"player1\":" << "\"" << p2->getName() << "\",\n";

		stringstream ss_env;
		ss_env << "{";
		for (auto iter = this->environment.begin(); iter != this->environment.end(); iter++) {
			ss_env << "\"" + iter->first + "\":" << "\"" << iter->second << "\"";
			if (distance(iter, this->environment.end()) >= 2) { ss_env << ","; }
		}
		ss_env << "}";
		raw_json << "\"environment\":" << ss_env.rdbuf() << ",\n";
		ss_env.clear();
		this->of_json << raw_json.rdbuf();
		this->of_json << "\"frames\":[";
	}
	else if (s == STATE::FRAME) {
		this->isFrameWrote = true;

		stringstream ss_frames;
		//for (auto& f = frames.begin(); f != frames.end(); f++) {
		Frame* f = this->getFrame();
		stringstream ss_frame;
		//프레임 루프

		vector<ExtracterUnit>* units = f->getUnits();

		for (auto& u = units->begin(); u != units->end(); u++) {
			//각 플레이어 유닛돌면서 필요한 정보 JSON화
			stringstream ss_unit;

			ss_unit << "\"x\":" << u->pos.x << ",";
			ss_unit << "\"y\":" << u->pos.y << ",";
			ss_unit << "\"tp\":" << cfg->getUnitCode(u->type) << ",";
			ss_unit << "\"ow\":" << u->owner << ",";
			ss_unit << "\"hp\":" << u->health << ",";
			ss_unit << "\"mh\":" << u->max_health << ",";
			ss_unit << "\"sp\":" << u->shield << ",";
			ss_unit << "\"ms\":" << u->max_shield << ",";
			ss_unit << "\"sg\":" << u->sight << ",";
			ss_unit << "\"ve\":" << u->visibleToEnemy;

			if (u->target_pos != TilePosition(-1, -1)) {
				ss_unit << ",\"target_x\":" << u->target_pos.x << ",";
				ss_unit << "\"target_y\":" << u->target_pos.y;
			}
			if (ss_unit.str() == "") continue;
			ss_frame << "{" << ss_unit.str() << "}";
			if (distance(u, units->end()) >= 2) { ss_frame << ",\n"; }

		}

		//if (ss_frame.str() == "") continue;
		ss_frames << "[" << ss_frame.str() << "]";
		ss_frames << ",\n";
		//}
		this->of_json << ss_frames.rdbuf();
	}
	else if (s == STATE::END) {
		if (!this->of_json.is_open()) {
			FreeConsole();
			return;
		}

		if (this->isFrameWrote) {
			long pos_cursor = this->of_json.tellp();
			this->of_json.seekp(pos_cursor - 3);
		}
		raw_json << "]"; //END OF FRAMES

		// Update For CIG
		// Record infomation of base;
		raw_json << ","; //END OF FRAMES

		stringstream ss_base;
		ss_base << "[";
		for (auto iter = this->unitRecorder.begin(); iter != this->unitRecorder.end(); iter++) {
			stringstream ss_unit;

			ss_unit << "\"x\":" << iter->pos.x << ",";
			ss_unit << "\"y\":" << iter->pos.y << ",";
			ss_unit << "\"id\":" << iter->id << ",";
			ss_unit << "\"tp\":" << cfg->getUnitCode(iter->type) << ",";
			ss_unit << "\"ow\":" << iter->owner << ",";
			ss_unit << "\"fc\":" << iter->frameCount;
			
			//if (u->target_pos != TilePosition(-1, -1)) {
			//ss_unit << ",\"target_x\":" << u->target_pos.x << ",";
			//ss_unit << "\"target_y\":" << u->target_pos.y;
			//}
			if (ss_unit.str() == "") continue;
			ss_base << "{" << ss_unit.str() << "}";



			////ss_base << "\"" + iter->first + "\":" << "\"" << iter->second << "\"";
			//
			//
			
			
			if (distance(iter, this->unitRecorder.end()) >= 2) { ss_base << ",\n"; }
		}
		ss_base << "]";
		raw_json << "\n\"base_found\":" << ss_base.rdbuf() << "\n";


		raw_json << "}";
		this->of_json << raw_json.rdbuf();
		this->of_json.close();

		//FreeConsole();
	}

	//raw_json << "\"frames\":" << "[" << ss_frames.rdbuf() << "]";
	//raw_json << "}";
	//
	//output_text = L"Packed Game\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);

	//output_text = L"Writing JSON\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);

	//ofstream of_json;
	//of_json.open("C:\\StarData\\JSON\\" + Broodwar->mapFileName() + ".json");
	//of_json << raw_json.str() << endl;
	//of_json.close();

	//output_text = L"Wrote JSON\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);

	//output_text = L"Copying Replay\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);

	//Util::copyFile("C:\\Starcraft\\maps\\StarData\\" + Broodwar->mapFileName(), "C:\\StarData\\Done\\" + Broodwar->mapFileName());

	//output_text = L"Copied Replay\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);

	//output_text = L"Removing Replay\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);

	//remove(Broodwar->mapPathName().c_str());

	//output_text = L"Removed Replay\n";
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output_text.c_str(),
	//	output_text.size(), &number_of_characters_written, nullptr);
	//FreeConsole();
}



// Update For CIG
bool DataManager::isRecorded(int _id) {
	for (auto& iter = unitRecorder.begin(); iter != unitRecorder.end(); iter++) {
		if (iter->id == _id) {
			return true;
		}
	}
	return false;
}

void DataManager::recordUnit(Unit u, int frameCount) {
	unitRecorder.push_back(UnitFound(u, frameCount));
}

vector<UnitFound>* DataManager::getRecord() {
	return &unitRecorder;
}