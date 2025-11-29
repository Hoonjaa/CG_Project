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

public:
	GLvoid setup(GLuint shader);
	GLvoid render(const glm::mat4& viewProjectionMatrix);
	// 이동 관련 함수
	GLvoid processMovement(bool w_pressed, bool a_pressed, bool s_pressed, bool d_pressed);
	glm::vec3 getPosition() const;

	// 1인칭 카메라 관련 함수
	GLvoid handleMouseMovement(float deltaX, float deltaY);
	glm::mat4 getFirstPersonViewMatrix() const;
	glm::mat4 getThirdPersonViewMatrix() const;
	GLvoid toggleViewMode(); // 1인칭/3인칭 전환
	bool isFirstPersonMode() const;
};

