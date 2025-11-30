#pragma once
#include "pch.h"
#include "TreeNode.h"
#include "Object_part.h"
#include "Player_body.h"
#include "Gun_body.h"
#include "Gun_cover.h"
#include "Gun_barrel.h"
#include "Gun_handle.h"
#include "Gun_magazine.h"

class Player
{
private:
	std::shared_ptr<TreeNode> root;
	std::shared_ptr<Object_Part> player_body;
	std::shared_ptr<Object_Part> gun_body;
	std::shared_ptr<Object_Part> gun_cover;
	std::shared_ptr<Object_Part> gun_barrel;
	std::shared_ptr<Object_Part> gun_handle;
	std::shared_ptr<Object_Part> gun_magazine;
	bool firstPersonMode; // 1인칭/3인칭 모드 전환용

	// 총 회전 업데이트를 위한 private 메서드
	GLvoid updateGunRotation();

public:
	// 총알 관련 변수
	GLint bulletCount = 30;
	bool canFire = true;

public:
	GLvoid setup(GLuint shader);
	GLvoid render(const glm::mat4& viewProjectionMatrix);
	// 이동 관련 함수
	GLvoid processMovement(bool w_pressed, bool a_pressed, bool s_pressed, bool d_pressed);
	glm::vec3 getPosition() const;
	// 총알 관련 변수
	glm::vec3 getFireDirection() const; //총알 발사 방향
	glm::vec3 getRightDirection() const; // 플레이어 오른쪽 방향
	glm::vec3 getMuzzlePosition() const; // 총구 위치
	// 재장전 애니메이션 관련 함수& 변수
	GLvoid reload();
	bool is_reloading = false; // 재장전 중인지 여부
	GLfloat gun_reload_angle = 0.0f; // 재장전 애니메이션 각도
	GLfloat gun_reload_speed = 1.0f; // 재장전 애니메이션 속도


	// 1인칭 카메라 관련 함수
	GLvoid handleMouseMovement(float deltaX, float deltaY);
	glm::mat4 getFirstPersonViewMatrix() const;
	glm::mat4 getThirdPersonViewMatrix() const;
	GLvoid toggleViewMode(); // 1인칭/3인칭 전환
	bool isFirstPersonMode() const;
};

