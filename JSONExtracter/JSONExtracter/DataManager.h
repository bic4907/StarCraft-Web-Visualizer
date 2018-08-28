#pragma once
#include<string>
#include<fstream>
#include<algorithm>
#include "BWAPI.h"
#include "Frame.h"
#include "ExtracterPlayerInfo.h"
#include "UnitFound.h"

using namespace std;
using namespace BWAPI;

class ExtractPlayerInfo;
class UnitFound;

class DataManager {
	


private:
	DataManager();
	~DataManager();

	static DataManager* instance;

	/* DEPARATED FROM 04.16 */
	/*
	vector<Frame> frames;
	*/

	Frame frame;
	

	vector<ExtracterPlayerInfo> players;
	string mapName;
	string mapHash;
	unsigned short map_width;
	unsigned short map_height;
	string replayName;
	map<string, int> environment;

	ofstream of_json;
	bool isFirstFrame = false;

	vector<UnitFound> unitRecorder;

public:


	static DataManager* getInstance();

	static bool isBrokenReplay;
	static bool isFrameWrote;

	void initalize();
	

	/* DEPARATED FROM 04.16 */
	/*
	void toNextFrame();
	Frame* getCurrentFrame();
	Frame* getFrame(int index);
	unsigned int getFrameSize();
	*/

	Frame* getFrame();

	vector<ExtracterPlayerInfo>* getPlayers();
	ExtracterPlayerInfo* getPlayerInfo(Player p);
	Playerset getPlayerset();

	void setMapSize(unsigned short width, unsigned short height);
	void setMapName(string s);
	void setPlayer(Player p);
	void setMapHash();
	void setFileName(string s);
	string getMapHash();
	void setEnvironment(string k, int v);
	
	bool isRecorded(int id);
	void recordUnit(Unit u, int frameCount);
	vector<UnitFound>* getRecord();


	enum STATE {
		START,
		FRAME,
		END
	};

	void saveJSON(enum STATE s);
};

