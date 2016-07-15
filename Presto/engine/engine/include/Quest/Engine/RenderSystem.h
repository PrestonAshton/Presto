#ifndef QUEST_ENGINE_RENDERSYSTEM_H
#define QUEST_ENGINE_RENDERSYSTEM_H

#include <Quest/Common.h>
#include <Quest/Containers/Hashmap.h>

typedef struct
{
	void(*RenderFunction)();
} RenderSystem;

void InitialiseRenderFactory(void);

#endif
