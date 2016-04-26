#ifndef PROPITIOUS_ENGINE_ENGINE_H
#define PROPITIOUS_ENGINE_ENGINE_H

#include <Presto/Common/BasicDefinitions.h>

typedef struct
{
  vchar* name;
  vchar* pathname;
} GameInfo;

typedef enum
{
	OpenGL = 0,
	DirectX9 = 1,
	DirectX10 = 1,
	DirectX11,
	DirectX12,
	Vulkan,
} RenderEngine;

typedef struct
{
  GameInfo gameinfo;
  vchar* exePath;
  vchar* gamePath;
  RenderEngine renderEngine;
  b8 isRunning;
} EngineGlobals;


DEFINE_EXTERNAL_INTERFACE_FUNCTION(ClientUpdate, void, void);
DEFINE_INTERFACE_FUNCTION(StartEngine, b8, const vchar*, const vchar*);

extern EngineGlobals engineGlobals;

#endif
