#include "Objects/ObjectNode.h"
#include "Data/String.h"

class Object : protected ObjectNode
{
public:
	String name = "Object";

	Object* FindParent(String name, int distance = -1)
	{
		return (Object*)_SearchUpEx((ObjectNode*)this, [](ObjectNode* node, void* data) -> bool { return ((Object*)node)->name == *(String*)data; }, &name, distance);
	}
	Object* FindParent(ObjectTypes _type, int distance = -1)
	{
		return (Object*)_SearchUpEx((ObjectNode*)this, [](ObjectNode* node, void* data) -> bool { return ((Object*)node)->type == *(ObjectTypes*)data; }, &type, distance);
	}
	Object* FindChild(String name, int distance = -1)
	{
		return (Object*)_SearchDownEx((ObjectNode*)this, [](ObjectNode* node, void* data) -> bool { return ((Object*)node)->name == *(String*)data; }, &name, distance);
	}
	Object* FindChild(ObjectTypes _type, int distance = -1)
	{
		return (Object*)_SearchDownEx((ObjectNode*)this, [](ObjectNode* node, void* data) -> bool { return ((Object*)node)->type == *(ObjectTypes*)data; }, &type, distance);
	}

	bool SetParent(Object* parent)
	{
		return _SetParent((ObjectNode*)this, (ObjectNode*)parent);
	}

	bool IsType(ObjectTypes _type) const { return type & _type; }
	bool IsExactType(ObjectTypes _type) const { return type == _type; }

	ObjectTypes GetType() const { return type; }
	ObjectId GetId() const { return id; }
	Object* GetParent() const { return (Object*)parent; }
	const Stack<Object*>& GetChildren() const { return *((Stack<Object*>*)&children); } // this is some insane casting stuff
};
