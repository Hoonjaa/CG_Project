#include "Bullet.h"

Bullet::Bullet(const glm::vec3& startPos, const glm::vec3& dir)
{
	vPos = startPos;
	direction = glm::normalize(dir);
	vColor = glm::vec3(1.0f, 0.0f, 0.0f);

	setVertexInfo();
	// VBO: 정점 데이터
	allocate(sizeof(vertices), GL_STATIC_DRAW);
	upload(vertices, sizeof(vertices));
	// 위치(0), 색상(1), 법선(2)
	setVertexAttrib(0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	setVertexAttrib(1, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	setVertexAttrib(2, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	// EBO: 인덱스 데이터
	allocateIndex(sizeof(indexes), GL_STATIC_DRAW);
	uploadIndex(indexes, sizeof(indexes));
	vertexCount = 36;
	setDrawMode(GL_TRIANGLES);
}

Bullet::~Bullet()
{
}

GLvoid Bullet::draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix)
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

GLvoid Bullet::update()
{
	// 이동 변환을 modelMatrix에 누적
	glm::vec3 movement = direction * speed * (1.0f / 60.0f); // 60FPS 기준
	glm::mat4 moveMatrix = glm::translate(glm::mat4(1.0f), movement);
	modelMatrix = moveMatrix * modelMatrix; // 새로운 변환을 기존 modelMatrix에 누적

	// 시간 업데이트
	currentTime += (1.0f / 60.0f);

	// 현재 위치 업데이트 (vPos는 getPosition()에서 사용하기 위해)
	vPos = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
}
