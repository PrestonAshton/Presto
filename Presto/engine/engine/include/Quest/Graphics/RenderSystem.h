#ifndef QUEST_GRAPHICS_RENDERSYSTEM_H
#define QUEST_GRAPHICS_RENDERSYSTEM_H

#include <Quest/Common.h>
#include <Quest/Containers.h>
#include <Quest/Graphics/Entity.h>
#include <Quest/Graphics/Camera.h>
#include <Quest/Graphics/dimensions.h>
#include <Quest/Graphics/lighting.h>
#include <Quest/Modules/OpenGL/Texture.h>

typedef u32 Instance;
#define EmptyComponent (Instance)(-1)

DEFINE_HASHMAP(Instance);

//GeometryBuffer geometryBuffer;
//RenderTexture lightBuffer;
//RenderTexture outTexture;

#define DEFINE_RENDER_SYSTEM(type, componentname, globalname)\
\
typedef struct\
{\
	u32 length;\
	u32 capacity;\
	void* data;\
\
	EntityId* entityId;\
	componentname* component;\
} type##InstanceData;\
\
typedef struct\
{\
	type##InstanceData data;\
\
	Hashmap_Instance map;\
\
	BaseLight ambientLight;\
	Array_DirectionalLight directionalLights;\
	Array_PointLight pointLights;\
	Array_SpotLight spotLights;\
\
	Dimensions frameBufferSize;\
\
	Camera camera;\
	f32 gamma;\
} type;\
\
extern type globalname;\
\
forceinline void type##Allocate(u32 length)\
{\
	if (length <= globalname.data.length)\
		return;\
\
	const usize bytes = length * (sizeof(EntityId) + sizeof(componentname));\
\
	type##InstanceData newData;\
	newData.length = globalname.data.length;\
	newData.capacity = length;\
	newData.data = spawn(bytes);\
\
	newData.entityId = (EntityId*)(newData.data);\
	newData.component = (componentname*)(newData.entityId + length);\
\
	copyMemory(globalname.data.entityId, newData.entityId, globalname.data.length * sizeof(EntityId));\
	copyMemory(globalname.data.component, newData.component, globalname.data.length * sizeof( componentname ));\
\
	murder(globalname.data.data);\
	globalname.data = newData;\
}\
\
forceinline Instance type##CreateByPtr(EntityId id, const componentname* comp)\
{\
	if (globalname.data.capacity == globalname.data.length || globalname.data.capacity == 0)\
		type##Allocate(2 * globalname.data.length + 1);\
\
	const Instance firstFree = globalname.data.length;\
\
	globalname.data.entityId[firstFree] = id;\
	globalname.data.component[firstFree] = *comp;\
\
	Hashmap_InstanceSetByValue(&(globalname.map), id, firstFree);\
\
	globalname.data.length++;\
\
	return firstFree;\
}\
forceinline Instance type##CreateByValue(EntityId id, const componentname comp)\
{\
	if (globalname.data.capacity == globalname.data.length || globalname.data.capacity == 0)\
		type##Allocate(2 * globalname.data.length + 1);\
\
	const Instance firstFree = globalname.data.length;\
\
	globalname.data.entityId[firstFree] = id;\
	globalname.data.component[firstFree] = comp;\
\
	Hashmap_InstanceSetByValue(&(globalname.map), id, firstFree);\
\
	globalname.data.length++;\
\
	return firstFree;\
}\
forceinline void type##Destroy(Instance id)\
{\
	const Instance last = globalname.data.length - 1;\
	const EntityId entity = globalname.data.entityId[id];\
	const EntityId lastEntity = globalname.data.entityId[last];\
\
	globalname.data.entityId[id] = globalname.data.entityId[last];\
	globalname.data.component[id] = globalname.data.component[last];\
\
	Hashmap_InstanceSetByValue(&(globalname.map), lastEntity, id);\
	Hashmap_InstanceSetByValue(&(globalname.map), entity, EmptyComponent);\
\
	globalname.data.length--;\
}\
\
forceinline Instance type##GetInstance(EntityId id)\
{\
	return Hashmap_InstanceGetValueDefault(&(globalname.map), id, EmptyComponent);\
}\
forceinline b8 type##IsValid(Instance instance)\
{\
	return instance != EmptyComponent;\
}\
\
forceinline void type##Clean()\
{\
}\
\
void type##Init();\
void type##Render()

DEFINE_RENDER_SYSTEM(NullRenderSystem, u32, g_nullRenderSystem);

BLANK_FUNCTION(void NullRenderSystemInit)
BLANK_FUNCTION(void NullRenderSystemRender)

#endif
