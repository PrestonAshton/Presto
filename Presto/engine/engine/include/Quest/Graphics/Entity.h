#ifndef QUEST_GRAPHICS_ENTITY_H
#define QUEST_GRAPHICS_ENTITY_H

typedef u32 EntityId;
#define MaxEntityCount (u16)(-1)

enum ComponentId
{
	ComponentNone = 0x0000000000,
	ComponentName = 0x0000000001,
};

typedef struct
{
	vchar* name;
} NameComponent;

#endif