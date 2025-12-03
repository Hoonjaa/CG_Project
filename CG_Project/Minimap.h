#pragma once
#include "pch.h"

class Zombie; 

class Minimap {
private:
    GLuint VAO, VBO;
    GLuint shaderProgramID;

    // 미니맵 설정
    float mapSize = 0.2f;        // 화면 크기 대비 미니맵 크기 (0.3 = 30%)
    float mapPosX = -0.8f;       // 우측 상단 위치 (NDC 좌표)
    float mapPosY = 0.8f;
    float worldSize = 20.0f;     // 월드 공간 크기 (맵의 경계)

    GLvoid initBuffers();
    GLvoid drawBackground();
    GLvoid drawPoint(const glm::vec3& worldPos, const glm::vec3& color, float size);
    glm::vec2 worldToMinimapCoords(const glm::vec3& worldPos);

public:
    Minimap(GLuint shader);
    ~Minimap();

    GLvoid render(const glm::vec3& playerPos, const std::vector<Zombie*>& zombies);
    GLvoid setWorldSize(float size);
};