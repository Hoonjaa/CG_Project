#pragma once
#include "Object.h"
#include "BoundingBox.h"

class Bullet : public Object
{
private:
    GLfloat vertices[9 * 24];

    GLvoid setVertexInfo() {
        GLfloat temp[9 * 24] = {
            // 앞면 (z = +0.5, normal = 0, 0, 1)
            0.025f, 0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
            -0.025f, 0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
            -0.025f, -0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
            0.025f, -0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,

            // 왼쪽면 (x = -0.5, normal = -1, 0, 0)
            -0.025f, 0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
            -0.025f, 0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
            -0.025f, -0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
            -0.025f, -0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,

            // 뒷면 (z = -0.5, normal = 0, 0, -1)
            -0.025f, 0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
            0.025f, 0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
            0.025f, -0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
            -0.025f, -0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,

            // 오른쪽면 (x = +0.5, normal = 1, 0, 0)
            0.025f, 0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
            0.025f, 0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
            0.025f, -0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
            0.025f, -0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,

            // 윗면 (y = +0.5, normal = 0, 1, 0)
            0.025f, 0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
            -0.025f, 0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
            -0.025f, 0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
            0.025f, 0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,

            // 아랫면 (y = -0.5, normal = 0, -1, 0)
            0.025f, -0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
            -0.025f, -0.025f, 0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
            -0.025f, -0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
            0.025f, -0.025f, -0.025f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
        };
        memcpy(vertices, temp, sizeof(temp));
    }

    GLuint indexes[6 * 6] = {
        // 앞면 (normal: 0, 0, 1)
        0,1,2,    0,2,3,
        // 왼쪽면 (normal: -1, 0, 0)
        4,5,6,    4,6,7,
        // 뒷면 (normal: 0, 0, -1)
        8,9,10,   8,10,11,
        // 오른쪽면 (normal: 1, 0, 0)
        12,13,14, 12,14,15,
        // 윗면 (normal: 0, 1, 0)
        16,17,18, 16,18,19,
        // 아랫면 (normal: 0, -1, 0)
        20,21,22, 20,22,23
    };
private:
    glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
    GLfloat speed = 50.0f;
    GLfloat lifeTime = 5.0f; // 5초 후 삭제
    GLfloat currentTime = 0.0f;

public:
    Bullet(const glm::vec3& startPos, const glm::vec3& dir);
    ~Bullet();

    GLvoid draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix) override;
    GLvoid update() override;
    bool Destroy() const { return currentTime >= lifeTime; }
    
    BoundingBox get_bb() const {
        BoundingBox bb;
        // modelMatrix에서 현재 위치 추출
        glm::vec3 currentPos = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
        // 총알의 작은 크기 (0.05 x 0.05 x 0.05)
        bb.min = currentPos + glm::vec3(-0.025f, -0.025f, -0.025f);
        bb.max = currentPos + glm::vec3(0.025f, 0.025f, 0.025f);
        return bb;
    }
};
