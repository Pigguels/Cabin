#include "Graphics/ShaderManager.h"

ShaderManager::ShaderManager() : Internal::RefManager<Shader>() {}
ShaderManager& ShaderManager::GetInstance()
{
	static ShaderManager* instance = new ShaderManager();
	return *instance;
}

ShaderRef ShaderManager::LoadAs(const String& filepath, const String& handle)
{
	ShaderRef ref;
	if (!refs.TryGet(handle, ref))
	{
		ref = _CreateRef(handle);
		ref.Ref()->Load(filepath);
	}
	return ref;
}
ShaderRef ShaderManager::Load(const String& filepath)
{
	return LoadAs(filepath, filepath);
}
