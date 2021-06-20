#include "StageManager.h"
#include <cassert>
#include <iostream>
#include "StartStage.h"
#include "PlayStage.h"
#include "EditorStage.h"
#include "LevelStage.h"
#include "StartStage.h"


StageManager* StageManager::instance = NULL;

StageManager::StageManager()
{
	assert(instance == NULL);

	instance = this;

	this->LoadAll();
}

void StageManager::LoadAll()
{
	StartStage* start_stage = new StartStage();
	stages_cache[START] = start_stage;

	PlayStage* play_stage = new PlayStage();
	stages_cache[PLAY] = play_stage;

	EditorStage* editor_stage = new EditorStage();
	stages_cache[EDITOR] = editor_stage;

	LevelStage* level_stage = new LevelStage();
	stages_cache[LEVELS] = level_stage;
}

Stage* StageManager::getStage(StageType name)
{
	//search stage in cache

	auto it = stages_cache.find(name);

	//if found, return it
	if (it != stages_cache.end()) {
		return it->second;
	}

	//not found, then throw error
	std::cout << "Error, stage not found" << std::endl;

	return nullptr;
}

