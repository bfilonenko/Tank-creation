#pragma once


#include "WorkWithWindow.h"
#include "PersonalTank.h"


class Battle : public WorkWithWindow
{
	vector<Component *> components;

	int fieldWidthForBattle;

	vector<Vector2int> positionsOfBackground;
	vector<ViewableObject *> objectsForBackground;

	Tank tank;
	PersonalTank *personalTank;

	void updatePositionOfBackground();

public:
	Battle(string &fileName, Graphic *forCopyWindow, string tankName);

	~Battle();

	void work();
};