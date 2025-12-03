#include "pch.h"
#include "Minimap.h"
#include "Zombie.h"

Minimap::Minimap(GLuint shader) : shaderProgramID(shader), VAO(0), VBO(0) {
    initBuffers();
}

Minimap::~Minimap() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

GLvoid Minimap::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 동적으로 업데이트할 것이므로 충분한 공간 할당
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 1000, nullptr, GL_DYNAMIC_DRAW);
    
    // 위치 속성
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 색상 속성
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec2 Minimap::worldToMinimapCoords(const glm::vec3& worldPos) {
    // 월드 좌표를 미니맵 좌표로 변환
    float normalizedX = (worldPos.x / worldSize) * mapSize;
    float normalizedZ = (worldPos.z / worldSize) * mapSize;
    
    return glm::vec2(mapPosX + normalizedX, mapPosY - normalizedZ);
}

GLvoid Minimap::drawBackground() {
    // 미니맵 배경 (반투명 검은색 사각형)
    float bgVertices[] = {
        // 위치 (x, y, z)              // 색상 (r, g, b)
        mapPosX - mapSize/2, mapPosY + mapSize/2, 0.0f,  0.0f, 0.0f, 0.0f,
        mapPosX + mapSize/2, mapPosY + mapSize/2, 0.0f,  0.0f, 0.0f, 0.0f,
        mapPosX + mapSize/2, mapPosY - mapSize/2, 0.0f,  0.0f, 0.0f, 0.0f,
        
        mapPosX - mapSize/2, mapPosY + mapSize/2, 0.0f,  0.0f, 0.0f, 0.0f,
        mapPosX + mapSize/2, mapPosY - mapSize/2, 0.0f,  0.0f, 0.0f, 0.0f,
        mapPosX - mapSize/2, mapPosY - mapSize/2, 0.0f,  0.0f, 0.0f, 0.0f,
    };
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bgVertices), bgVertices);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLvoid Minimap::drawPoint(const glm::vec3& worldPos, const glm::vec3& color, float size) {
    glm::vec2 mapPos = worldToMinimapCoords(worldPos);
    
    // 점 하나만 그리기
    float pointVertex[] = {
        mapPos.x, mapPos.y, 0.0f,  // 위치
        color.r, color.g, color.b   // 색상
    };
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointVertex), pointVertex);
    
    glPointSize(size);
    glDrawArrays(GL_POINTS, 0, 1);
}

GLvoid Minimap::render(const glm::vec3& playerPos, const std::vector<Zombie*>& zombies) {
    // 깊이 테스트 비활성화 
    glDisable(GL_DEPTH_TEST);
    
    // 단위 행렬로 설정 (2D 오버레이)
    GLuint modelLoc = glGetUniformLocation(shaderProgramID, "model");
    GLuint transformLoc = glGetUniformLocation(shaderProgramID, "Transform");
    glm::mat4 identity = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(identity));
    
    // 배경 그리기
    drawBackground();
    
    // 테두리 그리기
    float borderVertices[] = {
        mapPosX - mapSize/2, mapPosY + mapSize/2, 0.0f,  1.0f, 1.0f, 1.0f,
        mapPosX + mapSize/2, mapPosY + mapSize/2, 0.0f,  1.0f, 1.0f, 1.0f,
        mapPosX + mapSize/2, mapPosY - mapSize/2, 0.0f,  1.0f, 1.0f, 1.0f,
        mapPosX - mapSize/2, mapPosY - mapSize/2, 0.0f,  1.0f, 1.0f, 1.0f,
    };
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(borderVertices), borderVertices);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    
    // 플레이어 그리기 (파란색)
    drawPoint(playerPos, glm::vec3(0.0f, 0.5f, 1.0f), 10.0f);
    
    // 좀비들 그리기 (빨간색)
    for (auto* zombie : zombies) {
        if (zombie) {
            drawPoint(zombie->getPosition(), glm::vec3(1.0f, 0.0f, 0.0f), 8.0f);
        }
    }
    
    // 깊이 테스트 다시 활성화
    glEnable(GL_DEPTH_TEST);
    
    glBindVertexArray(0);
}

GLvoid Minimap::setWorldSize(float size) {
    worldSize = size;
}