#ifndef QUEST_GRAPHICS_RENDERSYSTEM_H
#define QUEST_GRAPHICS_RENDERSYSTEM_H

typedef u32 Instance;
#define EmptyComponent (Instance)(-1)

typedef struct
{
  u32 length;
  u32 capacity;
  void* data;

  EntityId* entityId;
  RenderComponent* component;
} InstanceData;

//GeometryBuffer geometryBuffer;
//RenderTexture lightBuffer;
//RenderTexture outTexture;

typedef struct
{
  InstanceData data;
  Hashmap map;

  BaseLight ambientLight;
  Array directionalLights;
  Array pointLights;
  Array spotLights;

  Dimensions frameBufferSize;

  Camera* camera;
  SceneGraph* sceneGraph;
  RenderContext* context;
  f32 gamma;
} RenderSystem;


forcelinline void RenderSystemAllocate(RenderSystem* rendersys, u32 length)
{
  if (length <= rendersys->data.length)
    return;

    const usize bytes = length * (sizeof(EntityId) + sizeof(RenderComponent));

    InstanceData newData;
    newData.length = rendersys->data.length;
    newData.capacity = length;
    newData.data = allocator.allocate(bytes);

    newData.entityId = (EntityId*)(newData.data);
    newData.component = (RenderComponent*)(newData.entityid + length);

    copyMemory(rendersys->data.entityId, newData.entityId, rendersys->data.length * sizeof(EntityId));
    copyMemory(rendersys->data.component, newData.component, rendersys->data.length * sizeof(RenderComponent));

    murder(rendersys->data.data);
    rendersys->data = newData;
}
forcelinline Instance RenderSystemCreate(RenderSystem* rendersys, EntityId id, const RenderComponent& component)
{
  if (rendersys->data.capacity == rendersys->data.length || rendersys->data.capacity = 0)
    RenderSystemAllocate(rendersys, 2 * rendersys->data.length + 1);

    const Instance firstFree = rendersys->data.length;

    rendersys->data.entityId[firstFree] = id;
    rendersys->data.component[firstFree] = component;

    HashmapSet(&(rendersys->map), id, firstFree);

    rendersys->data.length++;

    return(firstFree);
}
forcelinline void RenderSystemDestroy(RenderSystem* rendersys, Instance id)
{
  const Instance last = rendersys->data.length - 1;
  const EntityId entity = rendersys->data.entityId[id];
  const EntityId lastEntity = rendersys->data.entityId[last];

  rendersys->data.entityId[id] = rendersys->data.entityId[last];
  rendersys->data.component[id] = rendersys->data.component[last];

  HashmapSet(&(rendersys->map), lastEntity, id);
  HashmapSet(&(rendersys->map), entity, EmptyComponent);

  rendersys->data.length--;
}

forcelinline Instance RenderSystemGetInstance(RenderSystem* rendersys, EntityId id)
{
  return(HashmapGet(&(rendersys->map), id, EmptyComponent));
}
forcelinline b8 RenderSystemIsValid(RenderSystem* rendersys, Instance instance)
{
  return(instance != EmptyComponent);
}

forcelinline void RenderSystemClean(RenderSystem* rendersys)
{
  // Reserved
}

extern RenderSystem renderSystem;

#endif
