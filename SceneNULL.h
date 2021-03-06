#pragma once
#include "BaseScene.h"

class SceneNULL : public CBaseScene
{
public:
	SceneNULL();
	~SceneNULL();

	bool Initialize();
	void Terminate();
	bool Pulse();
	void ApiRender();
};