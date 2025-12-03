#pragma once
#include "Object.h"
class Zombie_body : public Object
{
private:
	GLfloat vertices[9 * 24];  // ¼öÁ¤: 9 * 24 (À§Ä¡3 + »ö»ó3 + ¹ý¼±3)

	GLvoid setVertexInfo() {
		GLfloat temp[216] = {  // 9 * 24 = 216
			// ¾Õ¸é (z = +0.3, normal = 0,0,1)
			vPos.x + 0.4f, vPos.y + 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x - 0.4f, vPos.y + 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x - 0.4f, vPos.y - 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x + 0.4f, vPos.y - 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			
			// ¿ÞÂÊ¸é (x = -0.4, normal = -1,0,0)
			vPos.x - 0.4f, vPos.y + 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 0.4f, vPos.y + 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 0.4f, vPos.y - 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 0.4f, vPos.y - 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			
			// µÞ¸é (z = -0.3, normal = 0,0,-1)
			vPos.x - 0.4f, vPos.y + 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x + 0.4f, vPos.y + 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x + 0.4f, vPos.y - 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x - 0.4f, vPos.y - 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			
			// ¿À¸¥ÂÊ¸é (x = +0.4, normal = 1,0,0)
			vPos.x + 0.4f, vPos.y + 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 0.4f, vPos.y + 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 0.4f, vPos.y - 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 0.4f, vPos.y - 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			
			// À­¸é (y = +0.7, normal = 0,1,0)
			vPos.x + 0.4f, vPos.y + 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x - 0.4f, vPos.y + 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x - 0.4f, vPos.y + 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x + 0.4f, vPos.y + 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			
			// ¾Æ·§¸é (y = -0.7, normal = 0,-1,0)
			vPos.x + 0.4f, vPos.y - 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x - 0.4f, vPos.y - 0.7f, vPos.z + 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x - 0.4f, vPos.y - 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x + 0.4f, vPos.y - 0.7f, vPos.z - 0.3f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
		};
		memcpy(vertices, temp, sizeof(temp));
	}

	GLuint indexes[6 * 6] = {
		0,1,2,  0,2,3,       // ¾Õ¸é
		4,5,6,  4,6,7,       // ¿ÞÂÊ¸é
		8,9,10, 8,10,11,     // µÞ¸é
		12,13,14, 12,14,15,  // ¿À¸¥ÂÊ¸é
		16,17,18, 16,18,19,  // À­¸é
		20,21,22, 20,22,23   // ¾Æ·§¸é
	};

public:
	Zombie_body();
	~Zombie_body();
	GLvoid draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix) override;
	GLvoid update() override;
};

