#pragma once
#include "Data/Stack.h"
#include <glad.h>

template<typename VertexType>
class Geometry
{
public:
	Geometry() {}
	Geometry(Stack<VertexType>& _vertices, Stack<unsigned int>& _indices, bool takeOwnership = false)
	{
		Set(_vertices, _indices, takeOwnership);
	}

	void Upload()
	{
		if (vertices.Count() == 0 || indices.Count() == 0) return;

		if (!IsLoaded())
		{
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);
		}

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertices.Count(), vertices.begin(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.Count(), indices.begin(), GL_STATIC_DRAW);

		_EnableVertexAttribs();

		glBindVertexArray(0);
	}
	bool Unload()
	{
		if (IsLoaded())
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
			vao = 0;
			vbo = 0;
			ebo = 0;
			return true;
		}
		return false;
	}

	void Bind() const { glBindVertexArray(vao); }
	void Unbind() const { glBindVertexArray(0); }
	void Draw() const { if (IsLoaded()) glDrawElements(GL_TRIANGLES, sizeof(VertexType) * indices.Count(), GL_UNSIGNED_INT, 0); }

	bool IsLoaded() const { return vao; }

	void Set(Stack<VertexType>& _vertices, Stack<unsigned int>& _indices, bool takeOwnership = false)
	{
		if (takeOwnership)
		{
			vertices.TakeOwnership(_vertices);
			indices.TakeOwnership(_indices);
		}
		else
		{
			vertices.CopyFrom(_vertices);
			indices.CopyFrom(_indices);
		}
	}

	Stack<VertexType> vertices;
	Stack<unsigned int> indices;

private:
	void _EnableVertexAttribs();

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
};
