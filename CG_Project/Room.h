#pragma once

#include "Object.h"
#include "Cube.h"

class Room : public Object
{
private:
	GLfloat vertices[9 * 24];

	GLvoid setVertexInfo() {
		// 법선을 안쪽으로 향하도록 반전 (내부가 보이도록)
		GLfloat temp[9 * 24] = {
			// 앞면 (z = +0.5, normal = 0, 0, -1) - 법선 반전
			vPos.x + 2.0f, vPos.y + 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x - 2.0f, vPos.y + 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x - 2.0f, vPos.y - 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x + 2.0f, vPos.y - 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,

			// 왼쪽면 (x = -0.5, normal = 1, 0, 0) - 법선 반전
			vPos.x - 2.0f, vPos.y + 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 2.0f, vPos.y + 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 2.0f, vPos.y - 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 2.0f, vPos.y - 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,

			// 뒷면 (z = -0.5, normal = 0, 0, 1) - 법선 반전
			vPos.x - 2.0f, vPos.y + 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x + 2.0f, vPos.y + 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x + 2.0f, vPos.y - 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x - 2.0f, vPos.y - 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,

			// 오른쪽면 (x = +0.5, normal = -1, 0, 0) - 법선 반전
			vPos.x + 2.0f, vPos.y + 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 2.0f, vPos.y + 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 2.0f, vPos.y - 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 2.0f, vPos.y - 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,

			// 윗면 (y = +0.5, normal = 0, -1, 0) - 법선 반전
			vPos.x + 2.0f, vPos.y + 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x - 2.0f, vPos.y + 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x - 2.0f, vPos.y + 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x + 2.0f, vPos.y + 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,

			// 아랫면 (y = -0.5, normal = 0, 1, 0) - 법선 반전
			vPos.x + 2.0f, vPos.y - 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x - 2.0f, vPos.y - 0.5f, vPos.z + 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x - 2.0f, vPos.y - 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x + 2.0f, vPos.y - 0.5f, vPos.z - 2.0f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
		};
		memcpy(vertices, temp, sizeof(temp));
	}

	GLuint indexes[6 * 6] = {
		// 앞면 - CW 순서로 변경
		0,1,2,    0,2,3,
		// 왼쪽면 - CW 순서로 변경
		4,5,6,    4,6,7,
		// 뒷면 - CW 순서로 변경
		8,9,10,   8,10,11,
		// 오른쪽면 - CW 순서로 변경
		12,13,14, 12,14,15,
		// 윗면 - CW 순서로 변경
		16,17,18, 16,18,19,
		// 아랫면 - CW 순서로 변경
		20,21,22, 20,22,23
	};

public:
	Room();
	~Room();

	GLvoid draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix) override;
	GLvoid update() override;
};

