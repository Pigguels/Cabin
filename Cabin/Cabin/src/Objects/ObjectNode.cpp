#include "Objects/ObjectNode.h"

void _PropagateUp(ObjectNode* node, PropagateObjectNodeFunction function, void* data, int distance)
{
	function(node, data);
	if (distance != 1 && node->parent) _PropagateUp(node->parent, function, data, distance - 1);
}
void _PropagateUpEx(ObjectNode* node, PropagateObjectNodeFunction function, void* data, int distance)
{
	if (distance != 0 && node->parent) _PropagateUp(node->parent, function, data, distance);
}
void _PropagateDown(ObjectNode* node, PropagateObjectNodeFunction function, void* data, int distance)
{
	function(node, data);
	if (distance != 0)
	{
		for (ObjectNode* child : node->children) _PropagateDown(child, function, data, distance - 1);
	}
}
void _PropagateDownEx(ObjectNode* node, PropagateObjectNodeFunction function, void* data, int distance)
{
	for (ObjectNode* child : node->children) _PropagateDown(child, function, data, distance);
}

ObjectNode* _SearchUp(ObjectNode* node, CheckObjectNodeFunction function, void* data, int distance)
{
	if (function(node, data)) return node;
	if (distance != 0 && node->parent) return _SearchUp(node->parent, function, data, distance - 1);
	return nullptr;
}
ObjectNode* _SearchUpEx(ObjectNode* node, CheckObjectNodeFunction function, void* data, int distance)
{
	if (node->parent) return _SearchUp(node->parent, function, data, distance);
	return nullptr;
}
ObjectNode* _SearchDown(ObjectNode* node, CheckObjectNodeFunction function, void* data, int distance)
{
	if (function(node, data)) return node;

	if (distance != 0)
	{
		for (ObjectNode* child : node->children)
		{
			ObjectNode* potential = _SearchDown(child, function, data, distance - 1);
			if (potential) return potential;
		}
	}
	return nullptr;
}
ObjectNode* _SearchDownEx(ObjectNode* node, CheckObjectNodeFunction function, void* data, int distance)
{
	for (ObjectNode* child : node->children)
	{
		ObjectNode* potential = _SearchDown(child, function, data, distance);
		if (potential) return potential;
	}
	return nullptr;
}

void _SearchAllUp(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction checkFunction, void* data, int distance)
{
	if (checkFunction(node, data)) outNodes.Add(node);
	if (distance != 0 && node->parent) _SearchAllUp(outNodes, node->parent, checkFunction, data, distance - 1);
}
void _SearchAllUpEx(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction checkFunction, void* data, int distance)
{
	if (node->parent) _SearchAllUp(outNodes, node->parent, checkFunction, data, distance);
}
void _SearchAllDown(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction checkFunction, void* data, int distance)
{
	if (checkFunction(node, data)) outNodes.Add(node);
	if (distance != 0)
	{
		for (ObjectNode* child : node->children) _SearchAllDown(outNodes, child, checkFunction, data, distance - 1);
	}
}
void _SearchAllDownEx(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction checkFunction, void* data, int distance)
{
	for (ObjectNode* child : node->children) _SearchAllDown(outNodes, child, checkFunction, data, distance);
}

bool _SetParent(ObjectNode* node, ObjectNode* parent)
{
	// check the node isnt already a child of the parent and that the parent isn't a child of the given node
	CheckObjectNodeFunction checkFunction = [](ObjectNode* context, void* data) -> bool { return context == (ObjectNode*)data; };
	if (parent && (_SearchUp(parent, checkFunction, (void*)node) || _SearchDownEx(parent, checkFunction, (void*)node, 0))) return false;

	if (node->parent) node->parent->children.Remove(node);
	node->parent = parent;
	if (parent) parent->children.Add(node);
	return true;
}
