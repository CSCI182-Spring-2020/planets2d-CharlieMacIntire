#pragma once
#include "ofMain.h"
class Body
{
public:

	Body() {};
	Body(float distance, float size, float speed, ofColor*);

	float _distance = 0;
	float _size = 0;
	float _speed = 0;
	glm::uvec2 _position;
	ofColor* bodyColor = NULL;


};

