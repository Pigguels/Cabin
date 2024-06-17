#include "Graphics/GeoManager.h"

GeoManager::GeoManager() : Internal::RefManager<Geometry<Vertex>>() {}

GeoManager& GeoManager::GetInstance()
{
	static GeoManager* instance = new GeoManager();
	return *instance;
}

GeoRef GeoManager::Create(const String& handle)
{
	Ref ref;
	if (!refs.TryGet(handle, ref)) ref = _CreateRef(handle);
	return ref;
}
GeoRef GeoManager::Create(const String& handle, Stack<Vertex>& vertices, Stack<unsigned int>& indices, bool takeOwnership)
{
	Ref ref;
	if (!refs.TryGet(handle, ref))
	{
		ref = _CreateRef(handle);
		ref.Ref()->Set(vertices, indices, takeOwnership);
	}
	return ref;
}
