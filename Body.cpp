#include "body.h"

#define PLANET_COUNT 9

body::body(float distance, float size, float speed, ofColor* color, BodyType bodyType)
{
	// Setup the body variables
	_distance = distance;
	_size = size;
	_speed = speed;
	_bodyColor = color;
	// Setup the position
	glm::vec2 vPos(0, distance * -1);
	_position = vPos;
	_bodyType = bodyType;

	// Setup the body (and it's sub-bodies)
	createSolarSystem();
}

bool body::createSolarSystem()
{
	int mDist = 0;
	switch (_bodyType)
	{
	case Sun:
		_bodyCount = 9;
		_bodies = new body[_bodyCount];
		mDist = 60;
		_bodies[0].setBodyAttributes(  // Mercury
			mDist,
			3.8,
			0.03,
			new ofColor(ofColor::red),
			Planet);
		
		_bodies[1].setBodyAttributes(  // Venus
			mDist * 2,
			9.5,
			0.025,
			new ofColor(ofColor::sandyBrown),
			Planet);
		
		_bodies[2].setBodyAttributes(  // Earth
			mDist * 3,
			10,
			0.020,
			new ofColor(ofColor::blue),
			MoonPlanet);
		
		_bodies[3].setBodyAttributes(  // Mars
			mDist * 4,
			5.3,
			0.018,
			new ofColor(ofColor::rosyBrown),
			Planet);

		_bodies[4].setBodyAttributes(  // Jupiter
			mDist * 5,
			40,
			0.015,
			new ofColor(ofColor::orange),
			Planet);

		_bodies[5].setBodyAttributes(  // Saturn
			mDist * 6,
			35,
			0.012,
			new ofColor(ofColor::gold),
			Planet);

		_bodies[6].setBodyAttributes(  // Uranus
			mDist * 7,
			15,
			0.010,
			new ofColor(ofColor::lightBlue),
			Planet);

		_bodies[7].setBodyAttributes(  // Neptune
			mDist * 8,
			20,
			0.008,
			new ofColor(ofColor::mediumBlue),
			Planet);
			
		break;

	case MoonPlanet:
		_bodyCount = 1;
		_bodies = new body[_bodyCount];
		mDist = 20;    // Distance between planets
		_bodies[0].setBodyAttributes(   // Moon
			mDist + _size,
			5, // Body Size
			.05, // Body Velocity
			new ofColor(155, 155, 155), Empty);
		break;
	default:
		_bodyCount = 0;
		_bodies = NULL;
		break;
	}

	return true;
}

bool body::setBodyAttributes(float distance, float size, float speed, ofColor* color, BodyType bt)
{
	_distance = distance;
	_size = size;
	_speed = speed;
	_bodyColor = color;
	glm::vec2 vPos(0, distance * -1);
	_position = vPos;
	_bodyType = bt;
	createSolarSystem();

	return true;
}

// Draw the body
void body::draw()
{
	ofPushMatrix();

	ofSetColor(*_bodyColor);
	ofTranslate(_position);
	ofDrawCircle(0.0, 0.0, _size);

	for (int i = 0; i < _bodyCount; i++)
		_bodies[i].draw();

	ofPopMatrix();
}

// Calculate the body's position
void body::calc()
{
	// calc the new position of this body
	_position.x = cos(ofGetFrameNum() * _speed) * _distance;
	_position.y = sin(ofGetFrameNum() * _speed) * _distance;

	// Calculate all the sub items of this body
	for (int i = 0; i < _bodyCount; i++)
		_bodies[i].calc();
}