#include "Player_body.h"

Player_body::Player_body()
{
	vColor = glm::vec3(0.0f, 0.8f, 0.0f);

	// 초기 방향 설정 (+z 방향을 바라보고 있음)
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	face_dir = glm::vec3(0.0f, 0.0f, 1.0f); // 카메라 초기 방향
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	moveSpeed = 0.05f; // 프레임당 이동 거리
	pitch = 0.0f; // 초기 pitch
	yaw = glm::radians(90.0f);   // 초기 yaw

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

Player_body::~Player_body()
{
}

GLvoid Player_body::draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix)
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

GLvoid Player_body::update()
{
	return GLvoid();
}

glm::vec3 Player_body::getForwardMovement()
{
	return forward * moveSpeed;
}

glm::vec3 Player_body::getBackwardMovement()
{
	return -forward * moveSpeed;
}

glm::vec3 Player_body::getLeftMovement()
{
	return -right * moveSpeed;
}

glm::vec3 Player_body::getRightMovement()
{
	return right * moveSpeed;
}

GLvoid Player_body::setForwardDirection(const glm::vec3& newForward)
{
	forward = glm::normalize(newForward);
	// 오른쪽 벡터를 업데이트 (Y축 기준으로 수직인 벡터)
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 Player_body::getForwardDirection() const
{
	return forward;
}

glm::vec3 Player_body::getFaceDirection() const
{
	return face_dir;
}

glm::vec3 Player_body::getCameraPosition(const glm::vec3& playerPosition) const
{
	// 플레이어 위치에서 Y축으로 1.5만큼 위에 카메라 위치
	return playerPosition + glm::vec3(0.0f, 0.7f, 0.0f);
}

GLvoid Player_body::updateFaceDirection(float deltaYaw, float deltaPitch)
{
	// 마우스 감도 조절
	const float sensitivity = 0.002f;

	yaw += deltaYaw * sensitivity;
	pitch += deltaPitch * sensitivity;

	// pitch를 -89도에서 +89도 사이로 제한 (위아래 시야 제한)
	const float maxPitch = glm::radians(50.0f);
	if (pitch > maxPitch) pitch = maxPitch;
	if (pitch < -maxPitch) pitch = -maxPitch;

	// 구면 좌표계를 이용해 face_dir 계산
	face_dir.x = cos(pitch) * cos(yaw);
	face_dir.y = sin(pitch);
	face_dir.z = cos(pitch) * sin(yaw);
	face_dir = glm::normalize(face_dir);

	// 이동용 forward 벡터는 Y축을 0으로 고정 (수평면에서만 이동)
	forward.x = cos(yaw);
	forward.y = 0.0f;
	forward.z = sin(yaw);
	forward = glm::normalize(forward);

	// right 벡터 업데이트
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

	// up 벡터 업데이트 (카메라용)
	up = glm::normalize(glm::cross(right, face_dir));
}