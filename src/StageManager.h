#pragma once

#include "Stage.h"
#include "framework.h"
#include <map>

enum StageType : uint8 { START,PLAY,EDITOR,LEVELS, END};

class StageManager
{
private:
	std::map<StageType, Stage*> stages_cache;

public:
	static StageManager* instance;

	Stage* getStage(StageType name);

	StageManager();
	
	void LoadAll();

};

