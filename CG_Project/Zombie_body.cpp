#include "pch.h"
#include "Zombie_body.h"

Zombie_body::Zombie_body()
{
	vColor = glm::vec3(0.2f, 0.2f, 0.6f);
	setVertexInfo();

	allocate(sizeof(vertices), GL_STATIC_DRAW);
	upload(vertices, sizeof(vertices));

	setVertexAttrib(0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	setVertexAttrib(1, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	setVertexAttrib(2, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	allocateIndex(sizeof(indexes), GL_STATIC_DRAW);
	uploadIndex(indexes, sizeof(indexes));

	vertexCount = 36;
	setDrawMode(GL_TRIANGLES);
}

Zombie_body::~Zombie_body()
{
}

GLvoid Zombie_body::draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 와이어프레임 모드
	glBindVertexArray(VAO);

	// modelTransform 행렬을 여기에서 변환




	glm::mat4 finalWorldMatrix = worldMatrix * modelMatrix;
	unsigned int modelLocation = glGetUniformLocation(ShaderID, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalWorldMatrix));

	glm::mat4 finalMatrix = viewProjMatrix * finalWorldMatrix;
	unsigned int transformLocation = glGetUniformLocation(ShaderID, "Transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(finalMatrix));

	glDrawElements(DrawMode, vertexCount, GL_UNSIGNED_INT, 0);
}

GLvoid Zombie_body::update()
{
}
