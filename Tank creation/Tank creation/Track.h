#pragma once


#include "Object.h"


class TrackComponent : public Component
{


public:
	TrackComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints);


};


class Track : public Object
{
	Object **additions;

public:
	Track();
	Track(Component *component);
	Track(Component *component, int index);

	~Track();
};


class AdditionToTrack : public Object
{
	Object *main;

public:
	AdditionToTrack(Object *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};