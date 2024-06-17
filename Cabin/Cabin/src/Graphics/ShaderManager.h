#pragma once
#include "Data/RefManager.h"
#include "Graphics/Shader.h"

class ShaderManager : public Internal::RefManager<Shader>
{
public:
	static ShaderManager& GetInstance();

	/*
	Summary:
	Load a Shader from disk with the given filepath, and store it with the given handle.
	[Note: If a Shader exists with the given handle already, that Shader is returned]
	*/
	Ref LoadAs(const String& handle, const String& filepath);
	/*
	Summary:
	Load a Shader script from disk with the given filepath, and store it with its handle being the given filepath.
	[Note: If a Shader exists with the given handle already, that Shader is returned]
	*/
	Ref Load(const String& filepath);

private:
	ShaderManager();
};
using ShaderRef = ShaderManager::Ref;
