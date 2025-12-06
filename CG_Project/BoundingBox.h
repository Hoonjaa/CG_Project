#pragma once
#include "pch.h"

struct BoundingBox {
	glm::vec3 min;
	glm::vec3 max;
	
	bool intersects(const BoundingBox& other) const {
		return (min.x <= other.max.x && max.x >= other.min.x) &&
		       (min.y <= other.max.y && max.y >= other.min.y) &&
		       (min.z <= other.max.z && max.z >= other.min.z);
	}
	
	void drawDebug() const {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
		glLineWidth(2.0f);
		
		glBegin(GL_LINES);
		// 아래 사각형
		glVertex3f(min.x, min.y, min.z); glVertex3f(max.x, min.y, min.z);
		glVertex3f(max.x, min.y, min.z); glVertex3f(max.x, min.y, max.z);
		glVertex3f(max.x, min.y, max.z); glVertex3f(min.x, min.y, max.z);
		glVertex3f(min.x, min.y, max.z); glVertex3f(min.x, min.y, min.z);
		
		// 위 사각형
		glVertex3f(min.x, max.y, min.z); glVertex3f(max.x, max.y, min.z);
		glVertex3f(max.x, max.y, min.z); glVertex3f(max.x, max.y, max.z);
		glVertex3f(max.x, max.y, max.z); glVertex3f(min.x, max.y, max.z);
		glVertex3f(min.x, max.y, max.z); glVertex3f(min.x, max.y, min.z);
		
		// 수직선
		glVertex3f(min.x, min.y, min.z); glVertex3f(min.x, max.y, min.z);
		glVertex3f(max.x, min.y, min.z); glVertex3f(max.x, max.y, min.z);
		glVertex3f(max.x, min.y, max.z); glVertex3f(max.x, max.y, max.z);
		glVertex3f(min.x, min.y, max.z); glVertex3f(min.x, max.y, max.z);
		glEnd();
		
		glEnable(GL_DEPTH_TEST);
		glLineWidth(1.0f);
	}
};
