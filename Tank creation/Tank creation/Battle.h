#pragma once


#include "WorkWithWindow.h"
#include "PersonalTank.h"
#include "WorkWithBullet.h"


class Battle : public WorkWithWindow
{
	vector<Component *> components;

	int fieldWidthForBattle;

	vector<Vector2int> positionsOfBackground;
	vector<ViewableObject *> bullets;
	vector<ViewableObject *> backgroundAndSpeedometerObjects;
	vector<ViewableObject *> backgroundObjects;
	ViewableObject *speedometerObjects;
	int allotmentPositionInComponents;
	vector<ViewableObject *> allotmentObjects;
	int bulletPositionInComponents;

	Tank tank;
	PersonalTank *personalTank;

	void updateObjects();

public:
	Battle(string &fileName, Graphic *forCopyWindow, string tankName);

	~Battle();

	void work();
};