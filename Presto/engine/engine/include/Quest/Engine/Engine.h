#ifndef QUEST_ENGINE_ENGINE_H
#define QUEST_ENGINE_ENGINE_H

#include <Quest/Common/BasicDefinitions.h>
#include <Quest/Engine/RenderSystem.h>
//#include <Quest/Graphics/RenderSystem.h>

typedef struct
{
	vchar* name;
	vchar* pathname;
} GameInfo;

typedef struct
{
	// Render factory is a hashmap of string -> function ptrs for starting a renderer.
	Hashmap renderFactory;
	RenderSystem* renderSystem;
	GameInfo gameinfo;
	vchar* exePath;
	vchar* gamePath;
	//RenderEngine renderEngine;
	b8 isRunning;
} EngineGlobals;


DEFINE_EXTERNAL_INTERFACE_FUNCTION(ClientUpdate, void, void);
DEFINE_INTERFACE_FUNCTION(StartEngine, b8, const vchar*, const vchar*);

void RenderStub(void);

void EngineUpdate(void);

void SetRenderer(const a8* args);

EngineGlobals engineGlobals;

#endif
