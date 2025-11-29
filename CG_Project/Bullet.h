#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
    GLfloat vertices[9 * 24];

    GLvoid setVertexInfo() {
        GLfloat temp[9 * 24] = {
            // ¾Õ¸é (z = +0.5, normal = 0, 0, 1)
            vPos.x + 0.025f, vPos.y + 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
            vPos.x - 0.025f, vPos.y + 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
            vPos.x - 0.025f, vPos.y - 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
            vPos.x + 0.025f, vPos.y - 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,

            // ¿ÞÂÊ¸é (x = -0.5, normal = -1, 0, 0)
            vPos.x - 0.025f, vPos.y + 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
            vPos.x - 0.025f, vPos.y + 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
            vPos.x - 0.025f, vPos.y - 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
            vPos.x - 0.025f, vPos.y - 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,

            // µÞ¸é (z = -0.5, normal = 0, 0, -1)
            vPos.x - 0.025f, vPos.y + 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
            vPos.x + 0.025f, vPos.y + 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
            vPos.x + 0.025f, vPos.y - 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
            vPos.x - 0.025f, vPos.y - 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,

            // ¿À¸¥ÂÊ¸é (x = +0.5, normal = 1, 0, 0)
            vPos.x + 0.025f, vPos.y + 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
            vPos.x + 0.025f, vPos.y + 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
            vPos.x + 0.025f, vPos.y - 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
            vPos.x + 0.025f, vPos.y - 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,

            // À­¸é (y = +0.5, normal = 0, 1, 0)
            vPos.x + 0.025f, vPos.y + 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
            vPos.x - 0.025f, vPos.y + 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
            vPos.x - 0.025f, vPos.y + 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
            vPos.x + 0.025f, vPos.y + 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,

            // ¾Æ·§¸é (y = -0.5, normal = 0, -1, 0)
            vPos.x + 0.025f, vPos.y - 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
            vPos.x - 0.025f, vPos.y - 0.025f, vPos.z + 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
            vPos.x - 0.025f, vPos.y - 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
            vPos.x + 0.025f, vPos.y - 0.025f, vPos.z - 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
        };
        memcpy(vertices, temp, sizeof(temp));
    }

    GLuint indexes[6 * 6] = {
        // ¾Õ¸é (normal: 0, 0, 1)
        0,1,2,    0,2,3,
        // ¿ÞÂÊ¸é (normal: -1, 0, 0)
        4,5,6,    4,6,7,
        // µÞ¸é (normal: 0, 0, -1)
        8,9,10,   8,10,11,
        // ¿À¸¥ÂÊ¸é (normal: 1, 0, 0)
        12,13,14, 12,14,15,
        // À­¸é (normal: 0, 1, 0)
        16,17,18, 16,18,19,
        // ¾Æ·§¸é (normal: 0, -1, 0)
        20,21,22, 20,22,23
    };
private:
    glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
    GLfloat speed = 50.0f;
    GLfloat lifeTime = 5.0f; // 5ÃÊ ÈÄ »èÁ¦
    GLfloat currentTime = 0.0f;

public:
    Bullet(const glm::vec3& startPos, const glm::vec3& dir);
    ~Bullet();

    GLvoid draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix) override;
    GLvoid update() override;
    bool Destroy() const { return currentTime >= lifeTime; }
};

