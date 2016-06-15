#ifndef QUEST_ENGINE_ENGINE_H
#define QUEST_ENGINE_ENGINE_H

#include <Quest/Common/BasicDefinitions.h>
//#include <Quest/Graphics/RenderSystem.h>

typedef struct
{
  vchar* name;
  vchar* pathname;
} GameInfo;

typedef struct
{
  //RenderSystem renderSystem;
  GameInfo gameinfo;
  vchar* exePath;
  vchar* gamePath;
  //RenderEngine renderEngine;
  b8 isRunning;
} EngineGlobals;


DEFINE_EXTERNAL_INTERFACE_FUNCTION(ClientUpdate, void, void);
DEFINE_INTERFACE_FUNCTION(StartEngine, b8, const vchar*, const vchar*);

void SetRenderer(const vchar* targs);

extern EngineGlobals engineGlobals;

#endif
