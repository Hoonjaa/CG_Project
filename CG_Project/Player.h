#pragma once
#include "pch.h"
#include "TreeNode.h"
#include "Object_part.h"
#include "Player_body.h"
#include "Gun_body.h"
#include "Gun_cover.h"
#include "Gun_barrel.h"

class Player
{
private:
	std::shared_ptr<TreeNode> root;
	std::shared_ptr<Object_Part> player_body;
	std::shared_ptr<Object_Part> gun_body;
	std::shared_ptr<Object_Part> gun_cover;
	std::shared_ptr<Object_Part> gun_barrel;

public:
	GLvoid setup(GLuint shader);
	GLvoid render(const glm::mat4& viewProjectionMatrix);
};

