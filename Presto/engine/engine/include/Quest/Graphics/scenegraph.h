#ifndef QUEST_GRAPHICS_SCENEGRAPH_H
#define QUEST_GRAPHICS_SCENEGRAPH_H

#include <Quest/Common.h>
#include <Quest/Containers.h>
#include <Quest/Graphics/Entity.h>

typedef u32 NodeId;
#define EmptyNodeId (NodeId)(-1)

DEFINE_HASHMAP(NodeId);

typedef struct
{
	NodeId length;
	NodeId capacity;
	void* data;

	EntityId* entityId;
	Transform* localTransforms;
	Transform* worldTransforms;
	NodeId* parents;
	NodeId* firstChildren;
	NodeId* previousSibling;
	NodeId* nextSibling;
} InstanceData;

typedef struct
{
	InstanceData data;

	Hashmap_NodeId map;

} SceneGraph;

extern SceneGraph g_scenegraph;

void SceneGraphAllocate(u32 length);
NodeId SceneGraphCreate(EntityId id, const Transform* transform);
void SceneGraphDestroy(NodeId id);
NodeId SceneGraphGetTransformId(EntityId id);

forceinline b8 SceneGraphIsValid(NodeId id)
{
	return id != EmptyNodeId;
}

forceinline NodeId SceneGraphNodeCount(void)
{
	return g_scenegraph.data.length;
}

forceinline NodeId SceneGraphGetNodeId(EntityId id)
{
	return Hashmap_NodeIdGetValueDefault(&(g_scenegraph.map), id, EmptyNodeId);
}

void SceneGraphLink(NodeId parent, NodeId child);
void SceneGraphUnlink(NodeId child);

forceinline void SceneGraphTransformChild(NodeId id, const Transform* transform)
{
	g_scenegraph.data.worldTransforms[id] = TransformMultiply(&(g_scenegraph.data.localTransforms[id]), transform);
	NodeId child = g_scenegraph.data.firstChildren[id];
	if (SceneGraphIsValid(child))
	{
		SceneGraphTransformChild(child, &(g_scenegraph.data.worldTransforms[id]));
		child = g_scenegraph.data.nextSibling[child];
	}
}

void SceneGraphUpdateLocal(NodeId id);
void SceneGraphUpdateWorld(NodeId id);

forceinline Transform SceneGraphGetLocalTransform(NodeId id)
{
	return g_scenegraph.data.localTransforms[id];
}

forceinline Transform SceneGraphGetWorldTransform(NodeId id)
{
	return g_scenegraph.data.worldTransforms[id];
}

forceinline Vector3 SceneGraphGetLocalPosition(NodeId id)
{
	return g_scenegraph.data.localTransforms[id].position;
}

forceinline Quaternion SceneGraphGetLocalOrientation(NodeId id)
{
	return g_scenegraph.data.localTransforms[id].orientation;
}

forceinline Vector3 SceneGraphGetLocalScale(NodeId id)
{
	return g_scenegraph.data.localTransforms[id].scale;
}

forceinline Vector3 SceneGraphGetWorldPosition(NodeId id)
{
	return g_scenegraph.data.worldTransforms[id].position;
}

forceinline Quaternion SceneGraphGetWorldOrientation(NodeId id)
{
	return g_scenegraph.data.worldTransforms[id].orientation;
}

forceinline Vector3 SceneGraphGetWorldScale(NodeId id)
{
	return g_scenegraph.data.worldTransforms[id].scale;
}

forceinline void SceneGraphSetLocalTransform(NodeId id, const Transform* t)
{
	g_scenegraph.data.localTransforms[id] = *t;
	SceneGraphUpdateLocal(id);
}

forceinline void SceneGraphSetWorldTransform(NodeId id, const Transform* t)
{
	g_scenegraph.data.worldTransforms[id] = *t;
	SceneGraphUpdateWorld(id);
}

forceinline void SceneGraphSetLocalPosition(NodeId id, const Vector3* t)
{
	g_scenegraph.data.localTransforms[id].position = *t;
	SceneGraphUpdateLocal(id);
}

forceinline void SceneGraphSetLocalOrientation(NodeId id, const Quaternion* t)
{
	g_scenegraph.data.localTransforms[id].orientation = *t;
	SceneGraphUpdateLocal(id);
}

forceinline void SceneGraphSetLocalScale(NodeId id, const Vector3* t)
{
	g_scenegraph.data.localTransforms[id].scale = *t;
	SceneGraphUpdateLocal(id);
}

forceinline void SceneGraphSetWorldPosition(NodeId id, const Vector3* t)
{
	g_scenegraph.data.worldTransforms[id].position = *t;
	SceneGraphUpdateWorld(id);
}


forceinline void SceneGraphSetWorldOrientation(NodeId id, const Quaternion* t)
{
	g_scenegraph.data.worldTransforms[id].orientation = *t;
	SceneGraphUpdateWorld(id);
}

forceinline void SceneGraphSetWorldScale(NodeId id, const Vector3* t)
{
	g_scenegraph.data.worldTransforms[id].scale = *t;
	SceneGraphUpdateWorld(id);
}

#endif
