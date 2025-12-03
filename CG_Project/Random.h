#pragma once
#include <random>

// 랜덤 디바이스 및 생성기
extern std::random_device rd;
extern std::mt19937 gen;

// 기존 분포
extern std::uniform_real_distribution<float> random_revolve_speed;
extern std::uniform_real_distribution<float> random_obstacle;

// 좀비 스폰 위치 분포
extern std::uniform_real_distribution<float> random_zombie_x;
extern std::uniform_real_distribution<float> random_zombie_z;

// 좀비 스폰 위치 생성 함수
glm::vec3 getRandomZombieSpawnPosition();