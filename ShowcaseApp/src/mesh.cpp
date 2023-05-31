#include "mesh.h"
#include <iostream>

// Control Shaders and Vertices

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &elements) {
	// Bind newly generated triangles
	glGenVertexArrays(1, &_vertexArrayObject);
	glGenBuffers(1, &_vertexBufferObject);
	glGenBuffers(1, &_elementBufferObject);

	// Sets up Vertex buffer that requires access in GLU
	glBindVertexArray(_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>
		(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

	// Sets up Elements buffer that requires access in GLU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>
		(elements.size() * sizeof(uint32_t)), elements.data(), GL_STATIC_DRAW);

	// Bind Vertex attributes [Position, Size, Type, Normalize Values (Stride in bytes and Offset)]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Color));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Uv));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	_elementCount = elements.size();
}

void Mesh::Draw() {

	// Bind Buffers
	glBindVertexArray(_vertexArrayObject);

	// Gl draw calls [First Index, How Many Elements Should be Drawn, What Kind of Element]
	glDrawElements(GL_TRIANGLES, _elementCount, GL_UNSIGNED_INT, nullptr);
}