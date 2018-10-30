#pragma once


#include "WorkWithWindow.h"


class Editor : public WorkWithWindow
{
	int backgroundXCoordinate, backgroundYCoordinate, backgroundWidth, backgroundHeight;
	string backgroundNameOfPicture;

public:
	Editor(string &fileName);

	Editor(string &fileName, Graphic *forCopyWindow);


	void work();
};