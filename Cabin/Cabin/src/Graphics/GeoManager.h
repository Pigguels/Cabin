#pragma once
#include "Data/RefManager.h"
#include "Graphics/Geometry.h"
#include "Graphics/Vertex.h"

class GeoManager : public Internal::RefManager<Geometry<Vertex>>
{
public:
	static GeoManager& GetInstance();

	/*
	Summary:
	Creates a Geometry object with the given vertices and indices then returns a ref to it.
	If an object already exists with the given handle then no object is created and the existing object is returned.
	*/
	Ref Create(const String& handle);
	/*
	Summary:
	Creates a Geometry object then returns a ref to it.
	If an object already exists with the given handle then no object is created and the existing object is returned.
	*/
	Ref Create(const String& handle, Stack<Vertex>& vertices, Stack<unsigned int>& indices, bool takeOwnership = false);

private:
	GeoManager();
};
using GeoRef = GeoManager::Ref;
