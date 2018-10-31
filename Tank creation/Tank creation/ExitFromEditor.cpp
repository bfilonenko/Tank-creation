#include "ExitFromEditor.h"


ExitFromEditor::ExitFromEditor(string &fileName, Graphic *forCopyWindow) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();
}


void ExitFromEditor::work()
{
	if (graphic->getTimeAsMilliseconds() - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				windowIsOpen = false;
				return;
			}
		}


		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].work(mousePosition, Mouse::isButtonPressed(Mouse::Left), timer, timeForWork);
		}

		for (int i = 0; i < numberOfButton; ++i)
		{
			if (button[i].getActivateAnAction())
			{
				if (button[i].getStruct()->buttonName == "Yes")
				{
					windowIsOpen = false;
					return;
				}
			}

		}

		graphic->draw(button);
	}
}