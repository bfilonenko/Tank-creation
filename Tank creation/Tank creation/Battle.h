#pragma once


#include "WorkWithWindow.h"
#include "PersonalTank.h"


class Battle : public WorkWithWindow
{
	vector<Component *> components;

	int fieldWidthForBattle;

	vector<Vector2int> positionsOfBackground;
	vector<ViewableObject *> objects;
	vector<ViewableObject *> backgroundObjects;
	ViewableObject *speedometerObjects;
	int allotmentPositionInComponents;
	vector<ViewableObject *> allotmentObjects;

	Tank tank;
	PersonalTank *personalTank;

	void updateObjects();

public:
	Battle(string &fileName, Graphic *forCopyWindow, string tankName);

	~Battle();

	void work();
};