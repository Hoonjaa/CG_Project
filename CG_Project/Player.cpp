#include "Player.h"

GLvoid Player::setup(GLuint shader) {
	root = std::make_shared<TreeNode>();

	auto P_body = std::make_shared<Player_body>();
	player_body = std::make_shared<Object_Part>(P_body, shader);
	root->addChild(player_body);

	auto G_body = std::make_shared<Gun_body>();
	gun_body = std::make_shared<Object_Part>(G_body, shader);
	gun_body->translate(glm::vec3(-0.55f, 0.4f, 0.5f));
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
	if (root) {
		root->render(viewProjectionMatrix);
	}
}