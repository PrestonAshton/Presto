#ifndef QUEST_GRAPHICS_ENTITYWORLD_H
#define QUEST_GRAPHICS_ENTITYWORLD_H

#include <Quest/Common.h>
#include <Quest/Graphics/Entity.h>

typedef struct
{
	u32 components[MaxEntityCount];
	NameComponent names[MaxEntityCount];
} EntityWorld;

extern EntityWorld g_entityWorld;

forceinline EntityId EntityWorldCreateEntity()
{
	EntityId id;
	for (id = 0; id < MaxEntityCount; id++)
	{
		if (g_entityWorld.components[id] == ComponentNone)
			return id;
	}

	return MaxEntityCount;
}

forceinline b8 EntityWorldIsAlive(EntityId id)
{
	return g_entityWorld.components[id] != ComponentNone;
}

forceinline void EntityWorldDestroy(EntityId id)
{
	g_entityWorld.components[id] = ComponentNone;
}

#endif
