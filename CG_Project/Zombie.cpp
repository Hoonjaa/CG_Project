#include "Zombie.h"

GLvoid Zombie::setup(GLuint shader) {
	root = std::make_shared<TreeNode>();

	//몸체 생성
	auto body = std::make_shared<Zombie_body>();
	bodyPart = std::make_shared<Object_Part>(body, shader);
	bodyPart->translate(glm::vec3(0.0f, 2.0f, 0.0f));
	root->addChild(bodyPart);

	//오른팔 생성
	auto Rarm = std::make_shared<Zombie_arm>();
	RightArmPart = std::make_shared<Object_Part>(Rarm, shader);
	RightArmPart->translate(glm::vec3(-0.5f, 0.1f, 0.0f));
	bodyPart->addChild(RightArmPart);

	//왼팔 생성
	auto Larm = std::make_shared<Zombie_arm>();
	LeftArmPart = std::make_shared<Object_Part>(Larm, shader);
	LeftArmPart->translate(glm::vec3(0.5f, 0.1f, 0.0f));
	bodyPart->addChild(LeftArmPart);

	//오른다리 생성
	auto Rleg = std::make_shared<Zombie_arm>();
	RightLegPart = std::make_shared<Object_Part>(Rleg, shader);
	RightLegPart->translate(glm::vec3(-0.2f, -1.1f, 0.0f));
	bodyPart->addChild(RightLegPart);

	//왼다리 생성
	auto Lleg = std::make_shared<Zombie_arm>();
	LeftLegPart = std::make_shared<Object_Part>(Lleg, shader);
	LeftLegPart->translate(glm::vec3(0.2f, -1.1f, 0.0f));
	bodyPart->addChild(LeftLegPart);

	//머리 생성
	auto head = std::make_shared<Zombie_head>();
	headPart = std::make_shared<Object_Part>(head, shader);
	headPart->translate(glm::vec3(0.0f, 0.9f, 0.0f));
	bodyPart->addChild(headPart);

	// 추가: 초기 회전 각도를 목표 지점을 향하도록 설정
	updateRotationToTarget();
}

// 추가: 목표 지점을 향해 회전 각도 업데이트
GLvoid Zombie::updateRotationToTarget() {
	glm::vec3 direction = target - position;
	// y 축 회전만 계산 (xz 평면에서의 방향)
	rotation_angle = atan2(direction.x, direction.z);
}

GLvoid Zombie::render(const glm::mat4& viewProjectionMatrix) {
	if (root) {
		// 좀비의 위치와 회전만 적용 (viewProjection은 나중에 적용)
		glm::mat4 zombieTransform = glm::translate(glm::mat4(1.0f), position);
		zombieTransform = glm::rotate(zombieTransform, rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));

		// viewProjMatrix를 모든 자식에게 전달
		setViewProjMatrixRecursive(root, viewProjectionMatrix);

		// 좀비의 월드 변환만 전달 (Player와 동일한 방식)
		root->render(zombieTransform);
	}
}

GLvoid Zombie::setViewProjMatrixRecursive(std::shared_ptr<TreeNode> node, const glm::mat4& viewProjMatrix) {
	// Object_Part로 캐스팅 시도
	auto objPart = std::dynamic_pointer_cast<Object_Part>(node);
	if (objPart) {
		objPart->setViewProjMatrix(viewProjMatrix);
	}

	// 모든 자식 노드에 대해 재귀 호출
	for (const auto& child : node->getChildren()) {
		setViewProjMatrixRecursive(child, viewProjMatrix);
	}
}

GLvoid Zombie::Walk(const glm::vec3 PlayerPos) {
	target = PlayerPos;
	// 목표 지점까지의 거리 계산
	glm::vec3 direction = target - position;
	float distance = glm::length(glm::vec2(direction.x, direction.z));  // xz 평면에서의 거리

	// 목표 지점에 충분히 가까우면 멈춤
	if (distance < 0.1f) {
		return;  // 더 이상 이동하지 않음
	}

	// 매 프레임마다 목표 지점을 향해 회전
	updateRotationToTarget();

	// 다음 이동할 위치 미리 계산
	glm::vec3 nextPosition = position;
	nextPosition.x += walk_speed * sin(rotation_angle);
	nextPosition.z += walk_speed * cos(rotation_angle);

	// 실제로 이동하도록 설정
	position = nextPosition;

	// 팔다리 회전 각도 업데이트
	if (limb_forward) {
		limb_rotation += glm::radians(2.0f);
		if (limb_rotation >= MAX_LIMB_ROTATION) {
			limb_rotation = MAX_LIMB_ROTATION;
			limb_forward = false;
		}
	}
	else {
		limb_rotation -= glm::radians(2.0f);
		if (limb_rotation <= -MAX_LIMB_ROTATION) {
			limb_rotation = -MAX_LIMB_ROTATION;
			limb_forward = true;
		}
	}

	// 오른팔 - 상단(어깨) 기준 회전
	if (RightArmPart) {
		glm::vec3 rightArmPos(-0.5f, 0.1f, 0.0f);
		glm::vec3 pivotOffset(0.0f, 0.5f, 0.0f); // 팔 길이의 절반만큼 위로 (상단)

		RightArmPart->setTransform(glm::mat4(1.0f));
		RightArmPart->translate(rightArmPos);
		RightArmPart->translate(pivotOffset); // 회전축으로 이동
		RightArmPart->rotate(limb_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		RightArmPart->translate(-pivotOffset); // 원위치
	}

	// 왼팔 - 상단(어깨) 기준 회전
	if (LeftArmPart) {
		glm::vec3 leftArmPos(0.5f, 0.1f, 0.0f);
		glm::vec3 pivotOffset(0.0f, 0.5f, 0.0f);

		LeftArmPart->setTransform(glm::mat4(1.0f));
		LeftArmPart->translate(leftArmPos);
		LeftArmPart->translate(pivotOffset);
		LeftArmPart->rotate(-limb_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		LeftArmPart->translate(-pivotOffset);
	}

	// 오른다리 - 상단(골반) 기준 회전
	if (RightLegPart) {
		glm::vec3 rightLegPos(-0.2f, -1.1f, 0.0f);
		glm::vec3 pivotOffset(0.0f, 0.5f, 0.0f); // 다리 길이의 절반만큼 위로 (상단)

		RightLegPart->setTransform(glm::mat4(1.0f));
		RightLegPart->translate(rightLegPos);
		RightLegPart->translate(pivotOffset);
		RightLegPart->rotate(-limb_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		RightLegPart->translate(-pivotOffset);
	}

	// 왼다리 - 상단(골반) 기준 회전
	if (LeftLegPart) {
		glm::vec3 leftLegPos(0.2f, -1.1f, 0.0f);
		glm::vec3 pivotOffset(0.0f, 0.5f, 0.0f);

		LeftLegPart->setTransform(glm::mat4(1.0f));
		LeftLegPart->translate(leftLegPos);
		LeftLegPart->translate(pivotOffset);
		LeftLegPart->rotate(limb_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		LeftLegPart->translate(-pivotOffset);
	}
}

GLvoid Zombie::resetMotion() {
	this->limb_rotation = 0.0f;
	this->limb_forward = true;

	if (RightArmPart) {
		glm::vec3 rightArmPos(-0.5f, 0.1f, 0.0f);
		RightArmPart->setTransform(glm::mat4(1.0f));
		RightArmPart->translate(rightArmPos);
	}

	// 왼팔 초기 위치로 복원
	if (LeftArmPart) {
		glm::vec3 leftArmPos(0.5f, 0.1f, 0.0f);
		LeftArmPart->setTransform(glm::mat4(1.0f));
		LeftArmPart->translate(leftArmPos);
	}

	// 오른다리 초기 위치로 복원
	if (RightLegPart) {
		glm::vec3 rightLegPos(-0.2f, -1.1f, 0.0f);
		RightLegPart->setTransform(glm::mat4(1.0f));
		RightLegPart->translate(rightLegPos);
	}

	// 왼다리 초기 위치로 복원
	if (LeftLegPart) {
		glm::vec3 leftLegPos(0.2f, -1.1f, 0.0f);
		LeftLegPart->setTransform(glm::mat4(1.0f));
		LeftLegPart->translate(leftLegPos);
	}
}

GLvoid Zombie::reset() {
	// 수정: 원점에서 멀리 다시 시작
	position = glm::vec3(3.0f, 1.0f, 3.0f);

	// 회전 각도 초기화
	rotation_angle = 0.0f;
	walk_angle = 0.0f;

	// 추가: 다시 목표를 향하도록 회전
	updateRotationToTarget();

	// 걷기 모션 초기화
	resetMotion();

	// 속도 및 회전 각도 초기화
	walk_speed = 0.03f;
	MAX_LIMB_ROTATION = glm::radians(20.0f);
}