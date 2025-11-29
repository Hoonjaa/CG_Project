#pragma once
#include "Object.h"
class Player_body : public Object
{
private:
    GLfloat vertices[9 * 24];

    GLvoid setVertexInfo() {
        GLfloat temp[9 * 24] = {
            // 앞면 (z = +0.5, normal = 0, 0, 1)
        vPos.x + 0.5f, vPos.y + 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
        vPos.x - 0.5f, vPos.y + 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
        vPos.x - 0.5f, vPos.y - 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,
        vPos.x + 0.5f, vPos.y - 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, 1.0f,

        // 왼쪽면 (x = -0.5, normal = -1, 0, 0)
        vPos.x - 0.5f, vPos.y + 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
        vPos.x - 0.5f, vPos.y + 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
        vPos.x - 0.5f, vPos.y - 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,
        vPos.x - 0.5f, vPos.y - 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  -1.0f, 0.0f, 0.0f,

        // 뒷면 (z = -0.5, normal = 0, 0, -1)
        vPos.x - 0.5f, vPos.y + 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
        vPos.x + 0.5f, vPos.y + 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
        vPos.x + 0.5f, vPos.y - 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,
        vPos.x - 0.5f, vPos.y - 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 0.0f, -1.0f,

        // 오른쪽면 (x = +0.5, normal = 1, 0, 0)
        vPos.x + 0.5f, vPos.y + 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
        vPos.x + 0.5f, vPos.y + 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
        vPos.x + 0.5f, vPos.y - 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,
        vPos.x + 0.5f, vPos.y - 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  1.0f, 0.0f, 0.0f,

        // 윗면 (y = +0.5, normal = 0, 1, 0)
        vPos.x + 0.5f, vPos.y + 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
        vPos.x - 0.5f, vPos.y + 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
        vPos.x - 0.5f, vPos.y + 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,
        vPos.x + 0.5f, vPos.y + 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, 1.0f, 0.0f,

        // 아랫면 (y = -0.5, normal = 0, -1, 0)
        vPos.x + 0.5f, vPos.y - 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
        vPos.x - 0.5f, vPos.y - 1.0f, vPos.z + 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
        vPos.x - 0.5f, vPos.y - 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
        vPos.x + 0.5f, vPos.y - 1.0f, vPos.z - 0.5f,  vColor.r, vColor.g, vColor.b,  0.0f, -1.0f, 0.0f,
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

public:
    // 플레이어 방향과 이동 관련 변수
    glm::vec3 forward;  // 앞쪽 방향 벡터
    glm::vec3 right;    // 오른쪽 방향 벡터
    float moveSpeed;    // 이동 속도

    // 플레이어 1인칭 카메라 변수
    glm::vec3 face_dir; // 카메라가 바라보는 방향 벡터 (Y축 자유)
    glm::vec3 up;       // 위쪽 방향 벡터
    float pitch;        // 상하 회전각 (라디안)
    float yaw;          // 좌우 회전각 (라디안)

    // 이동량 반환 메서드들 (실제 이동은 TreeNode에서 처리)
    glm::vec3 getForwardMovement();
    glm::vec3 getBackwardMovement();
    glm::vec3 getLeftMovement();
    glm::vec3 getRightMovement();

    // 방향 관련 메서드
    GLvoid setForwardDirection(const glm::vec3& forward);
    glm::vec3 getForwardDirection() const;

    // 1인칭 카메라 관련 메서드
    glm::vec3 getFaceDirection() const;
    glm::vec3 getCameraPosition(const glm::vec3& playerPosition) const;
    GLvoid updateFaceDirection(float deltaYaw, float deltaPitch);

public:
    Player_body();
	~Player_body();

    GLvoid draw(const GLuint& ShaderID, const glm::mat4& worldMatrix, const glm::mat4& viewProjMatrix) override;
    GLvoid update() override;
};

