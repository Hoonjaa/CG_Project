#pragma once
#include "Object.h"
class Zombie_arm : public Object
{
private:
	GLfloat vertices[9 * 24];

	GLvoid setVertexInfo() {
		GLfloat temp[216] = {  // 9 * 24 = 216
			// ¾Õ¸é (z = +0.0625, normal = 0,0,1)
			vPos.x + 0.0625f, vPos.y + 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x - 0.0625f, vPos.y + 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x - 0.0625f, vPos.y - 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			vPos.x + 0.0625f, vPos.y - 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
			
			// ¿ÞÂÊ¸é (x = -0.0625, normal = -1,0,0)
			vPos.x - 0.0625f, vPos.y + 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y + 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y - 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y - 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
			
			// µÞ¸é (z = -0.0625, normal = 0,0,-1)
			vPos.x - 0.0625f, vPos.y + 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x + 0.0625f, vPos.y + 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x + 0.0625f, vPos.y - 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			vPos.x - 0.0625f, vPos.y - 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
			
			// ¿À¸¥ÂÊ¸é (x = +0.0625, normal = 1,0,0)
			vPos.x + 0.0625f, vPos.y + 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 0.0625f, vPos.y + 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 0.0625f, vPos.y - 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			vPos.x + 0.0625f, vPos.y - 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
			
			// À­¸é (y = +0.3125, normal = 0,1,0)
			vPos.x + 0.0625f, vPos.y + 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y + 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y + 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			vPos.x + 0.0625f, vPos.y + 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
			
			// ¾Æ·§¸é (y = -0.3125, normal = 0,-1,0)
			vPos.x + 0.0625f, vPos.y - 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y - 0.3125f, vPos.z + 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x - 0.0625f, vPos.y - 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
			vPos.x + 0.0625f, vPos.y - 0.3125f, vPos.z - 0.0625f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
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
	Zombie_arm();
	~Zombie_arm();

	GLvoid set_color(const glm::vec3& color) {
		vColor = color;
		setVertexInfo(); // Á¤Á¡ »ö»ó Á¤º¸ ¾÷µ¥ÀÌÆ®

		// VBO µ¥ÀÌÅÍ °»½Å
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		upload(vertices, sizeof(vertices));
	}

	GLvoid draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix) override;
	GLvoid update() override;
};

