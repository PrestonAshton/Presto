#ifndef PROPITIOUS_ENGINE_ENGINE_H
#define PROPITIOUS_ENGINE_ENGINE_H

#include <Presto/Common/BasicDefinitions.h>

typedef struct
{
  vchar* name;
  vchar* pathname;
} GameInfo;

typedef struct
{
  GameInfo gameinfo;
  vchar* exePath;
  vchar* gamePath;
  b8 isRunning;
} EngineGlobals;

DEFINE_EXTERNAL_INTERFACE_FUNCTION(ClientUpdate, void, void);
DEFINE_INTERFACE_FUNCTION(StartEngine, b8, const vchar*, const vchar*);

extern EngineGlobals engineGlobals;

#endif
