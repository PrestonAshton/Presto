SceneGraph g_scenegraph = { 0 };

void SceneGraphAllocate(u32 length)
{
	if (length <= g_scenegraph.data.length)
		return;

	NodeId bytes = (NodeId)(length * (sizeof(EntityId) + 2 * sizeof(Transform) + 4 * sizeof(NodeId)));

	InstanceData newData;
	newData.length = g_scenegraph.data.length;
	newData.capacity = length;
	newData.data = spawn(bytes);

	newData.entityId = (EntityId*)(newData.data);
	newData.localTransforms = (Transform*)(newData.entityId + length);
	newData.worldTransforms = (Transform*)(newData.localTransforms + length);
	newData.parents = (NodeId*)(newData.worldTransforms + length);
	newData.firstChildren = (NodeId*)(newData.parents + length);
	newData.previousSibling = (NodeId*)(newData.firstChildren + length);
	newData.nextSibling = (NodeId*)(newData.previousSibling + length);

	copyMemory(g_scenegraph.data.entityId, newData.entityId, g_scenegraph.data.length * sizeof(EntityId));
	copyMemory(g_scenegraph.data.localTransforms, newData.localTransforms, g_scenegraph.data.length * sizeof(Transform));
	copyMemory(g_scenegraph.data.worldTransforms, newData.worldTransforms, g_scenegraph.data.length * sizeof(Transform));
	copyMemory(g_scenegraph.data.parents, newData.parents, g_scenegraph.data.length * sizeof(NodeId));
	copyMemory(g_scenegraph.data.firstChildren, newData.firstChildren, g_scenegraph.data.length * sizeof(NodeId));
	copyMemory(g_scenegraph.data.previousSibling, newData.previousSibling, g_scenegraph.data.length * sizeof(NodeId));
	copyMemory(g_scenegraph.data.nextSibling, newData.nextSibling, g_scenegraph.data.length * sizeof(NodeId));

	murder(g_scenegraph.data.data);
	g_scenegraph.data = newData;
}
NodeId SceneGraphCreate(EntityId id, const Transform* transform)
{
	if (g_scenegraph.data.capacity == g_scenegraph.data.length || g_scenegraph.data.capacity == 0)
		SceneGraphAllocate(2 * g_scenegraph.data.length + 2);

	const NodeId last = g_scenegraph.data.length;
	g_scenegraph.data.entityId[last] = id;
	g_scenegraph.data.localTransforms[last] = *transform;
	g_scenegraph.data.worldTransforms[last] = *transform;
	g_scenegraph.data.parents[last] = EmptyNodeId;
	g_scenegraph.data.firstChildren[last] = EmptyNodeId;
	g_scenegraph.data.previousSibling[last] = EmptyNodeId;
	g_scenegraph.data.nextSibling[last] = EmptyNodeId;

	Hashmap_NodeIdSetByValue(&(g_scenegraph.map), id, last);

	g_scenegraph.data.length++;
	return last;
}
void SceneGraphDestroy(NodeId id)
{
	const NodeId last = g_scenegraph.data.length - 1;
	const EntityId e = g_scenegraph.data.entityId[id];
	const EntityId lastEntity = g_scenegraph.data.entityId[last];

	g_scenegraph.data.entityId[id] = g_scenegraph.data.entityId[last];
	g_scenegraph.data.localTransforms[id] = g_scenegraph.data.localTransforms[last];
	g_scenegraph.data.worldTransforms[id] = g_scenegraph.data.worldTransforms[last];
	g_scenegraph.data.parents[id] = g_scenegraph.data.parents[last];
	g_scenegraph.data.firstChildren[id] = g_scenegraph.data.firstChildren[last];
	g_scenegraph.data.previousSibling[id] = g_scenegraph.data.previousSibling[last];
	g_scenegraph.data.nextSibling[id] = g_scenegraph.data.nextSibling[last];

	Hashmap_NodeIdSetByValue(&(g_scenegraph.map), lastEntity, id);
	Hashmap_NodeIdSetByValue(&(g_scenegraph.map), e, EmptyNodeId);

	g_scenegraph.data.length--;
}

NodeId SceneGraphGetTransformId(EntityId id)
{
	return Hashmap_NodeIdGetValue(&(g_scenegraph.map), id);
}

void SceneGraphLink(NodeId parent, NodeId child)
{
	SceneGraphUnlink(child);

	if (!SceneGraphIsValid(g_scenegraph.data.firstChildren[parent]))
	{
		g_scenegraph.data.firstChildren[parent] = child;
		g_scenegraph.data.parents[child] = parent;
	}
	else
	{
		NodeId previous;
		NodeId current = g_scenegraph.data.firstChildren[parent];
		while (SceneGraphIsValid(current))
		{
			previous = current;
			current = g_scenegraph.data.nextSibling[current];
		}

		g_scenegraph.data.nextSibling[previous] = child;

		g_scenegraph.data.firstChildren[child] = EmptyNodeId;
		g_scenegraph.data.nextSibling[child] = EmptyNodeId;
		g_scenegraph.data.previousSibling[child] = previous;
	}

	const Transform parentTransform = g_scenegraph.data.worldTransforms[parent];
	const Transform childTransform = g_scenegraph.data.worldTransforms[child];

	const Transform localTransform = TransformDivide(&parentTransform, &childTransform);

	g_scenegraph.data.localTransforms[child] = localTransform;
	g_scenegraph.data.parents[child] = parent;

	SceneGraphTransformChild(child, &parentTransform);
}

void SceneGraphUnlink(NodeId child)
{
	if (!SceneGraphIsValid(g_scenegraph.data.parents[child]))
		return;

	if (!SceneGraphIsValid(g_scenegraph.data.previousSibling[child]))
		g_scenegraph.data.firstChildren[g_scenegraph.data.parents[child]] = g_scenegraph.data.nextSibling[child];
	else
		g_scenegraph.data.nextSibling[g_scenegraph.data.previousSibling[child]] = g_scenegraph.data.nextSibling[child];

	if (SceneGraphIsValid(g_scenegraph.data.nextSibling[child]))
		g_scenegraph.data.previousSibling[g_scenegraph.data.nextSibling[child]] = g_scenegraph.data.previousSibling[child];

	g_scenegraph.data.parents[child] = EmptyNodeId;
	g_scenegraph.data.nextSibling[child] = EmptyNodeId;
	g_scenegraph.data.previousSibling[child] = EmptyNodeId;
}

void SceneGraphUpdateLocal(NodeId id)
{
	NodeId parentId = g_scenegraph.data.parents[id];
	Transform parentTransform = { 0 };
	if (SceneGraphIsValid(parentId))
		parentTransform = g_scenegraph.data.worldTransforms[parentId];

	SceneGraphTransformChild(id, &parentTransform);
}
void SceneGraphUpdateWorld(NodeId id)
{
	NodeId parentId = g_scenegraph.data.parents[id];
	Transform parentTransform = { 0 };
	if (SceneGraphIsValid(parentId))
		parentTransform = g_scenegraph.data.worldTransforms[parentId];

	g_scenegraph.data.localTransforms[id] = TransformDivide(&(g_scenegraph.data.worldTransforms[id]), &parentTransform);
	SceneGraphTransformChild(id, &parentTransform);
}