#pragma once
#include "Data/Stack.h"
#include "Objects/ObjectTypes.h"

typedef unsigned int ObjectId;

struct ObjectNode
{
	ObjectTypes type;
	ObjectId id;
	ObjectNode* parent;
	Stack<ObjectNode*> children;
};

/*
	For all node functions:
	-	-1 distance means infinite checks.
	-	Given start node must not be nullptr.

	- functions are presumed to be inclusive unless explicitly stated (usually a 'Ex' prefix)

	- inclusive functions will always run on the given node even if the initial distance is zero
	- inclusive functions with a distance of zero will run on themselves, a distance of 1 will run on itself and its neighboring nodes

	- exclusive functions will always run on the given nodes neighboring nodes even if the initial distance is zero
	- exclusive functions with a distance of zero will run only on their neighboring nodes, a distance of 1 will run on its neighboring nodes and their neighbors.
*/

typedef void(*PropagateObjectNodeFunction)(ObjectNode* context, void* data);

void _PropagateUp(ObjectNode* node, PropagateObjectNodeFunction function, void* data = nullptr, int distance = -1);
void _PropagateUpEx(ObjectNode* node, PropagateObjectNodeFunction function, void* data = nullptr, int distance = -1);
void _PropagateDown(ObjectNode* node, PropagateObjectNodeFunction function, void* data = nullptr, int distance = -1);
void _PropagateDownEx(ObjectNode* node, PropagateObjectNodeFunction function, void* data = nullptr, int distance = -1);

typedef bool(*CheckObjectNodeFunction)(ObjectNode* context, void* data);

ObjectNode* _SearchUp(ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);
ObjectNode* _SearchUpEx(ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);
ObjectNode* _SearchDown(ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);
ObjectNode* _SearchDownEx(ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);

void _SearchAllUp(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);
void _SearchAllUpEx(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);
void _SearchAllDown(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);
void _SearchAllDownEx(Stack<ObjectNode*>& outNodes, ObjectNode* node, CheckObjectNodeFunction function, void* data = nullptr, int distance = -1);

bool _SetParent(ObjectNode* node, ObjectNode* parent);
