#include "pch.h"
#include "Random.h"

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_real_distribution<float> random_revolve_speed(-0.5f, 0.5f);
std::uniform_real_distribution<float> random_obstacle(-4.0f, 4.0f);

// 좀비 스폰 위치 분포
std::uniform_real_distribution<float> random_zombie_outer(21.0f, 25.0f);  // 외곽 영역 (21~25)
std::uniform_real_distribution<float> random_zombie_inner(-10.0f, 10.0f); // 내부 영역 (-10~10)

glm::vec3 getRandomZombieSpawnPosition() {
    // 4개의 변(상, 하, 좌, 우) 중 하나를 랜덤하게 선택
    std::uniform_int_distribution<int> side_dist(0, 3);
    int side = side_dist(gen);
    
    float x, z;
    
    switch (side) {
        case 0: // 북쪽 (z > 0)
            x = random_zombie_inner(gen);      // x: -10 ~ 10
            z = random_zombie_outer(gen);       // z: 21 ~ 25
            break;
        case 1: // 남쪽 (z < 0)
            x = random_zombie_inner(gen);      // x: -10 ~ 10
            z = -random_zombie_outer(gen);      // z: -25 ~ -21
            break;
        case 2: // 동쪽 (x > 0)
            x = random_zombie_outer(gen);       // x: 21 ~ 25
            z = random_zombie_inner(gen);      // z: -10 ~ 10
            break;
        case 3: // 서쪽 (x < 0)
            x = -random_zombie_outer(gen);      // x: -25 ~ -21
            z = random_zombie_inner(gen);      // z: -10 ~ 10
            break;
    }
    
    // y는 지면 위치
    return glm::vec3(x, 0.0f, z);
}