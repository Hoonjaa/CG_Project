#pragma once
#include "TreeNode.h"
#include "Object_part.h"
#include "Zombie_arm.h"
#include "Zombie_body.h"
#include "Zombie_head.h"
#include "Zombie_leg.h"
#include "pch.h"

class Zombie
{
private:
	std::shared_ptr<TreeNode> root;
	std::shared_ptr<Object_Part> bodyPart;
	std::shared_ptr<Object_Part> headPart;
	std::shared_ptr<Object_Part> LeftArmPart;
	std::shared_ptr<Object_Part> RightArmPart;
	std::shared_ptr<Object_Part> LeftLegPart;
	std::shared_ptr<Object_Part> RightLegPart;

	glm::vec3 position{ 3.0f, 1.0f, 3.0f };
	glm::vec3 target{ 0.0f, 1.0f, 0.0f };
	GLfloat walk_angle = 0.0f;
	GLfloat rotation_angle = 0.0f;
	//걷는 모션
	GLfloat limb_rotation = 0.0f;
	bool limb_forward = true;
	GLfloat walk_speed = 0.03f;
	GLfloat MAX_LIMB_ROTATION = glm::radians(20.0f);

	GLvoid setViewProjMatrixRecursive(std::shared_ptr<TreeNode> node, const glm::mat4& viewProjMatrix);
public:
	// 추가: 생성자에 시작 위치 매개변수
	Zombie(const glm::vec3& startPos = glm::vec3(3.0f, 1.0f, 3.0f))
		: position(startPos) {
	}

	GLvoid setup(GLuint shader);

	// 추가: 목표 지점을 향해 회전 각도 업데이트
	GLvoid updateRotationToTarget();

	GLvoid render(const glm::mat4& viewProjectionMatrix);

	GLvoid Walk(const glm::vec3 PlayerPos);

	GLvoid resetMotion();

	GLvoid reset();
};

