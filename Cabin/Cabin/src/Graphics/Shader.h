#pragma once
#include "Data/String.h"
#include "Data/StringBuilder.h"
#include "Maths/Vec2.h"
#include "Maths/Vec3.h"
#include "Maths/Vec4.h"
#include "Maths/Mat3.h"
#include "Maths/Mat4.h"

class Shader
{
public:
	Shader();
	Shader(String _filepath);
	~Shader();

	void Unload();
	bool Load(String _filepath);
	bool Load(); // works for reloading

	bool IsLoaded() const;

	void Bind() const;
	void Unbind() const;

	int GetUniformLocation(const char* name) const;
	void SetUniform(int location, const int value) const;
	void SetUniform(int location, const int* value, int count) const;
	void SetUniform(int location, const float value) const;
	void SetUniform(int location, const float* value, int count) const;
	void SetUniform(int location, const Vec2 value) const;
	void SetUniform(int location, const Vec2* value, int count) const;
	void SetUniform(int location, const Vec3 value) const;
	void SetUniform(int location, const Vec3* value, int count) const;
	void SetUniform(int location, const Vec4 value) const;
	void SetUniform(int location, const Vec4* value, int count) const;
	void SetUniform(int location, const Mat3 value) const;
	void SetUniform(int location, const Mat3* value, int count) const;
	void SetUniform(int location, const Mat4 value) const;
	void SetUniform(int location, const Mat4* value, int count) const;

private:
	void _LoadShaderSrc(String filepath, StringBuilder& vertexSrc, StringBuilder& fragmentSrc, StringBuilder& geometrySrc) const;
	bool _CompileShader(const char* src, unsigned int type);

	unsigned int program;
	String filepath;
};
