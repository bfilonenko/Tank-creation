#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"
#include "SaveTank.h"


class ExitFromEditor : public NotificationWindow
{

public:
	ExitFromEditor(string &fileName, Graphic *forCopyWindow);


	void work();
};