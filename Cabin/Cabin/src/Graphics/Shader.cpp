#include "Graphics/Shader.h"
#include "Core/Debug.h"
#include "Core/File.h"

#include <glad.h>
//#define GLFW_INCLUDE_NONE
//#include <glfw3.h>

Shader::Shader()
{
	program = 0;
}
Shader::Shader(String _filepath)
{
	Load(_filepath);
}
Shader::~Shader()
{
	Unload();
}

void Shader::Unload()
{
	if (!program) return;
	glDeleteProgram(program);
	program = 0;
}
bool Shader::Load(String _filepath)
{
	Unload();

	filepath = _filepath;

	program = glCreateProgram();
	
	StringBuilder vertexSrc, fragmentSrc, geometrySrc;
	_LoadShaderSrc(filepath, vertexSrc, fragmentSrc, geometrySrc);

	unsigned int vert = (vertexSrc.Length() > 1) ? _CompileShader(vertexSrc.c_str(), GL_VERTEX_SHADER) : 0;
	unsigned int frag = (fragmentSrc.Length() > 1) ? _CompileShader(fragmentSrc.c_str(), GL_FRAGMENT_SHADER) : 0;
	unsigned int geo = (geometrySrc.Length() > 1) ? _CompileShader(geometrySrc.c_str(), GL_GEOMETRY_SHADER) : 0;

	glLinkProgram(program);

	/* Debuging info and error log output */
	int success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char errorLog[512];
		glGetShaderInfoLog(program, 512, nullptr, errorLog);
		DEBUG_MSG_WARNING("Failed to link shader program for reason(s):\n" << errorLog);
		glDeleteProgram(program);
	}
	else
		glValidateProgram(program);

	if (vert) glDeleteShader(vert);
	if (frag) glDeleteShader(frag);
	if (geo) glDeleteShader(geo);

	return true;
}
bool Shader::Load() { return Load(filepath); }

bool Shader::IsLoaded() const { return program; }

void Shader::Bind() const { glUseProgram(program); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::_LoadShaderSrc(String filepath, StringBuilder& vertexSrc, StringBuilder& fragmentSrc, StringBuilder& geometrySrc) const
{
	String fileContents = File::ReadFile(filepath.c_str());

	const char* current = fileContents.c_str();
	StringBuilder* currentSrc = nullptr;
	StringBuilder version;
	while (current)
	{
		if (version.Length() == 1 && StringFunctions::Compare(current, "#version ", 9) == 0)
		{
			int nextLine = StringFunctions::Find(current + 9, "\n") + 9;
			if (nextLine == 8) version.Append(current);
			else version.Append(current, nextLine);
		}

		if (StringFunctions::Compare(current, "#vertex\n", 8) == 0) { currentSrc = &vertexSrc; current += 8; }
		else if (StringFunctions::Compare(current, "#fragment\n", 10) == 0) { currentSrc = &fragmentSrc; current += 10; }
		else if (StringFunctions::Compare(current, "#geometry\n", 10) == 0) { currentSrc = &geometrySrc; current += 10; }

		int nextRegion = StringFunctions::Find(current + 1, "\n#") + 2;
		if (nextRegion == 1)
		{
			if (currentSrc) currentSrc->Append(current);
			break;
		}

		if (currentSrc) currentSrc->Append(current, nextRegion);
		current += nextRegion;
	}

	ASSERT_MSG(version.Length() > 1, "No version specified in shader file.");
	ASSERT_MSG(vertexSrc.Length() > 1, "No vertex source found in shader file.");
	ASSERT_MSG(fragmentSrc.Length() > 1, "No fragment source found in shader file.");

	vertexSrc.Prepend(version);
	fragmentSrc.Prepend(version);
	if (geometrySrc.Length() > 1) geometrySrc.Prepend(version);
}

bool Shader::_CompileShader(const char* src, unsigned int type)
{
	unsigned int shader = glCreateShader(type);

	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	/* Debuging info and error log output */
	int success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char errorLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, errorLog);

		String shaderType;
		if (type == GL_VERTEX_SHADER) shaderType = "Vertex";
		else if (type == GL_FRAGMENT_SHADER) shaderType = "Fragment";
		else if (type == GL_GEOMETRY_SHADER) shaderType = "Geometry";
		DEBUG_MSG_WARNING(shaderType.c_str() << " shader failed to compile for reason(s):\n" << errorLog);
		return shader;
	}

	glAttachShader(program, shader);

	return shader;
}

// surely a better way to handle the uniforms

int Shader::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(program, name);
}
void Shader::SetUniform(int location, const int value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform1i(location, value);
}
void Shader::SetUniform(int location, const int* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform1iv(location, count, value);
}
void Shader::SetUniform(int location, const float value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform1f(location, value);
}
void Shader::SetUniform(const int location, const float* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform1fv(location, count, value);
}
void Shader::SetUniform(int location, const Vec2 value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform2f(location, value.x, value.y);
}
void Shader::SetUniform(int location, const Vec2* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform2fv(location, count, (float*)value);
}
void Shader::SetUniform(int location, const Vec3 value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform3f(location, value.x, value.y, value.z);
}
void Shader::SetUniform(int location, const Vec3* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform3fv(location, count, (float*)value);
}
void Shader::SetUniform(int location, const Vec4 value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform4f(location, value.x, value.y, value.z, value.w);
}
void Shader::SetUniform(int location, const Vec4* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniform4fv(location, count, (float*)value);
}
void Shader::SetUniform(int location, const Mat3 value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniformMatrix3fv(location, 1, GL_FALSE, (float*)&value);
}
void Shader::SetUniform(int location, const Mat3* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniformMatrix3fv(location, count, GL_FALSE, (float*)value);
}
void Shader::SetUniform(int location, const Mat4 value) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&value);
}
void Shader::SetUniform(int location, const Mat4* value, int count) const
{
	ASSERT_MSG(location != -1, "No uniform found with given name.");
	glUniformMatrix4fv(location, count, GL_FALSE, (float*)value);
}
