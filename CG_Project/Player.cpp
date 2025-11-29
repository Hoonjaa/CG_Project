#include "Player.h"

glm::vec3 Player::getFireDirection() const
{
	if (player_body && player_body->getObject()) {
		auto playerBodyObj = std::dynamic_pointer_cast<Player_body>(player_body->getObject());
		if (playerBodyObj) {
			if (firstPersonMode) {
				// 1인칭 모드에서는 카메라가 바라보는 방향으로 발사
				return playerBodyObj->getFaceDirection();
			}
			else {
				// 3인칭 모드에서는 플레이어 앞쪽 방향으로 발사
				return playerBodyObj->getForwardDirection();
			}
		}
	}
	return glm::vec3(0.0f, 0.0f, -1.0f); // 기본값
}

glm::vec3 Player::getRightDirection() const
{
	if (player_body && player_body->getObject()) {
		auto playerBodyObj = std::dynamic_pointer_cast<Player_body>(player_body->getObject());
		if (playerBodyObj) {
			if (firstPersonMode) {
				// 1인칭 모드: 카메라의 face_dir를 기준으로 오른쪽 벡터 계산
				glm::vec3 faceDir = playerBodyObj->getFaceDirection();
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
				return glm::normalize(glm::cross(faceDir, up));
			}
			else {
				// 3인칭 모드: 플레이어의 forward를 기준으로 오른쪽 벡터 계산
				glm::vec3 forward = playerBodyObj->getForwardDirection();
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
				return glm::normalize(glm::cross(forward, up));
			}
		}
	}
	return glm::vec3(1.0f, 0.0f, 0.0f); // 기본값 (오른쪽)
}

glm::vec3 Player::getMuzzlePosition() const
{
	glm::vec3 playerPos = getPosition();
	glm::vec3 fireDir = getFireDirection();
	glm::vec3 rightDir = getRightDirection();

	// 총구 위치 계산
	glm::vec3 muzzlePos = playerPos;

	if (firstPersonMode) {
		// 1인칭 모드: 카메라(눈) 위치 기준으로 총구 위치 계산
		muzzlePos.y += 0.3f; // 눈 높이
		muzzlePos += rightDir * 0.4f; // 오른쪽으로 약간 이동 (총이 오른쪽에 있다고 가정)
		muzzlePos += fireDir * 1.7f; // 앞쪽으로 약간 이동 (총구가 앞에 있음)
	}
	else {
		// 3인칭 모드: 플레이어 몸체 기준으로 총구 위치 계산
		muzzlePos.y += 0.8f; // 어깨 높이
		muzzlePos += rightDir * 0.3f; // 오른쪽으로 이동
		muzzlePos += fireDir * 0.5f; // 앞쪽으로 이동
	}

	return muzzlePos;
}

GLvoid Player::setup(GLuint shader) {
	root = std::make_shared<TreeNode>();

	auto P_body = std::make_shared<Player_body>();
	player_body = std::make_shared<Object_Part>(P_body, shader);
	player_body->translate(glm::vec3(0.0f, 1.0f, 0.0f));
	root->addChild(player_body);

	auto G_body = std::make_shared<Gun_body>();
	gun_body = std::make_shared<Object_Part>(G_body, shader);
	gun_body->translate(glm::vec3(-0.3f, 0.45f, 0.7f));
	player_body->addChild(gun_body);

	auto G_cover = std::make_shared<Gun_cover>();
	gun_cover = std::make_shared<Object_Part>(G_cover, shader);
	gun_cover->translate(glm::vec3(0.0f, 0.0f, 0.25f));
	gun_body->addChild(gun_cover);

	auto G_barrel = std::make_shared<Gun_barrel>();
	gun_barrel = std::make_shared<Object_Part>(G_barrel, shader);
	gun_barrel->translate(glm::vec3(0.0f, 0.0f, 0.7f));
	gun_body->addChild(gun_barrel);

	auto G_handle = std::make_shared<Gun_handle>();
	gun_handle = std::make_shared<Object_Part>(G_handle, shader);
	gun_handle->translate(glm::vec3(0.0f, -0.25f, -0.45f));
	gun_body->addChild(gun_handle);

	auto G_magazine = std::make_shared<Gun_magazine>();
	gun_magazine = std::make_shared<Object_Part>(G_magazine, shader);
	gun_magazine->translate(glm::vec3(0.0f, -0.3f, -0.025f));
	gun_body->addChild(gun_magazine);
}

GLvoid Player::render(const glm::mat4& viewProjectionMatrix) {
	if (firstPersonMode && gun_body && player_body && player_body->getObject()) {
		updateGunRotation();
	}

	if (root) {
		root->render(viewProjectionMatrix);
	}
}

GLvoid Player::updateGunRotation() {
	auto playerBodyObj = std::dynamic_pointer_cast<Player_body>(player_body->getObject());
	if (playerBodyObj) {
		// 현재 yaw 값을 가져와서 총 회전 적용
		float currentYaw = playerBodyObj->yaw;

		// 총의 로컬 변환 초기화 (이전 회전 제거)
		player_body->setTransform(glm::mat4(1.0f));

		player_body->translate(glm::vec3(-0.3f, 0.45f, 0.7f));
		player_body->rotate(currentYaw - glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	}
}

GLvoid Player::processMovement(bool w_pressed, bool a_pressed, bool s_pressed, bool d_pressed)
{
	if (player_body && player_body->getObject()) {
		auto playerBodyObj = std::dynamic_pointer_cast<Player_body>(player_body->getObject());
		if (playerBodyObj) {
			// TreeNode의 translate를 직접 사용하여 이동
			if (w_pressed) {
				root->translate(playerBodyObj->getForwardMovement());
			}
			if (s_pressed) {
				root->translate(playerBodyObj->getBackwardMovement());
			}
			if (a_pressed) {
				root->translate(playerBodyObj->getLeftMovement());
			}
			if (d_pressed) {
				root->translate(playerBodyObj->getRightMovement());
			}
		}
	}
}

glm::vec3 Player::getPosition() const
{
	if (player_body) {
		// TreeNode의 월드 변환에서 위치 추출
		glm::mat4 worldTransform = player_body->getWorldTransform();
		return glm::vec3(worldTransform[3][0], worldTransform[3][1], worldTransform[3][2]);
	}
	return glm::vec3(0.0f);
}

GLvoid Player::handleMouseMovement(float deltaX, float deltaY)
{
	if (player_body && player_body->getObject()) {
		auto playerBodyObj = std::dynamic_pointer_cast<Player_body>(player_body->getObject());
		if (playerBodyObj) {
			// 마우스 이동을 face_dir 업데이트에 사용
			playerBodyObj->updateFaceDirection(deltaX, -deltaY); // Y축 반전
		}
	}
}

glm::mat4 Player::getFirstPersonViewMatrix() const
{
	if (player_body && player_body->getObject()) {
		auto playerBodyObj = std::dynamic_pointer_cast<Player_body>(player_body->getObject());
		if (playerBodyObj) {
			glm::vec3 playerPos = getPosition();
			glm::vec3 cameraPos = playerBodyObj->getCameraPosition(playerPos);
			glm::vec3 faceDir = playerBodyObj->getFaceDirection();
			glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);

			return glm::lookAt(cameraPos, cameraPos + faceDir, upDir);
		}
	}
	return glm::mat4(1.0f);
}

glm::mat4 Player::getThirdPersonViewMatrix() const
{
	glm::vec3 eye = glm::vec3(0.0f, 10.0f, 20.0f);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	return glm::lookAt(eye, center, up);
}

GLvoid Player::toggleViewMode()
{
	firstPersonMode = !firstPersonMode;
}

bool Player::isFirstPersonMode() const
{
	return firstPersonMode;
}