#include "BotTank.h"



BotTank::BotTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize) : PersonalTank(objects, fieldWidthForBattle, screenWidth, dataArraySize)
{

}


BotTank::~BotTank()
{

}


void BotTank::updateTracks()
{
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(Track))
			{
				(*objects)[i][j]->timerForObject = ((*objects)[i][j]->timerForObject + (speed > 0 ? (*objects)[i][j]->getComponentParameter()->numberOfVariant - 1 : 1)) % (*objects)[i][j]->getComponentParameter()->numberOfVariant;
				(*objects)[i][j]->needDraw = true;
			}
		}
	}
}


void BotTank::setGlobalOffset(Vector2int offset)
{
	globalOffset = offset;
}

Vector2int BotTank::getOffsetForTank()
{
	if (position == 0)
	{
		return Vector2int(xOffset, yOffset) - globalOffset;
	}
	return Vector2int(xOffset + position, yOffset - globalOffset.y) - globalOffset;
}


Vector2int BotTank::getBorder()
{
	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	Vector2int result(dataArraySize, -1);

	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j])
			{
				result.x = min(result.x, i);
				result.y = max(result.y, i);
			}
		}
	}

	++result.y;
	result = Vector2int(dataArraySize - result.y, dataArraySize - result.x) * 20;

	return result;
}


void BotTank::work(long timer, int fps, int lengthBetweenTanks, Vector2int personalPosition, vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets)
{
	//Work with motion
	if (needDrive)
	{
		needDrive = false;
		if (driveRight)
		{
			speed += maxSpeed / 6;
			speed = min(speed, maxSpeed);
		}
		else
		{
			speed -= maxSpeed / 6;
			speed = max(speed, -maxSpeed);
		}
	}

	if (speed != 0 && timer - timerForSpeed >= 100 - (100 * abs(speed)) / maxSpeed)
	{
		timerForSpeed = timer;
		updateTracks();

		globalOffset.x -= speed / abs(speed);
		Vector2int border = getBorder();

		if (globalOffset.x <= 0 && globalOffset.x >= -(fieldWidthForBattle - screenWidth))
		{
			if (position < 0)
			{
				globalOffset.x = 0;
				position += 1;
			}
			else if (position > 0)
			{
				globalOffset.x = -(fieldWidthForBattle - screenWidth);
				position -= 1;
			}
			else if (getOffsetForTank().x + border.x < personalPosition.x + lengthBetweenTanks)
			{
				globalOffset.x -= 1;
			}
			else
			{
				position = 0;
			}
		}
		else if (globalOffset.x > 0)
		{
			position -= 1;
			globalOffset.x = 0;
			if (position < -xOffset - border.x)
			{
				position = -xOffset - border.x;
			}
		}
		else if (globalOffset.x < -(fieldWidthForBattle - screenWidth))
		{
			position += 1;
			globalOffset.x = -(fieldWidthForBattle - screenWidth);
			if (position > screenWidth - xOffset - border.y)
			{
				position = screenWidth - xOffset - border.y;
			}
		}

		if (position != 0)
		{
			highlightingUpdated = true;
		}
	}


	//Work with bullet
	bool needRemoveHangingObjects = false;
	for (int k = 0; k < int(bullets.size()); ++k)
	{
		bool breakCheck = true;
		if (bullets[k]->getFather() != nullptr)
		{
			Vector2int bulletPosition = getBuletPositionFromTime(bullets[k], timer),
				offsetForBullet = Vector2int((Vector2int(dataArraySize * 20, 0) - (bulletPosition - getOffsetForTank()) - bulletPosition).x, -getOffsetForTank().y);
			if (bullets[k]->getFather()->getHealth() > 0 && !collisionCheck(bullets[k]->getFather(), bullets[k], bulletPosition, offsetForBullet) && !bullets[k]->canDoDamageToItself)
			{
				bullets[k]->canDoDamageToItself = true;
			}
			else if (bullets[k]->getFather()->getHealth() > 0 && collisionCheck(bullets[k]->getFather(), bullets[k], bulletPosition, offsetForBullet) && bullets[k]->canDoDamageToItself)
			{
				bullets[k]->getFather()->setHeath(bullets[k]->getFather()->getHealth() - bullets[k]->damage);
				if (bullets[k]->getFather()->getHealth() <= 0)
				{
					highlightingUpdated = true;
					needRemoveHangingObjects = true;
				}
				bullets[k]->getFather()->needDraw = true;
				breakBullet(components, bulletPositionInComponents, bullets, k, timer);
				breakCheck = false;
			}
		}
		if (!breakCheck)
		{
			--k;
		}
	}

	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if (checkForExistenceAndNotComplementarity((*objects)[i][j]))
			{
				for (int k = 0; k < int(bullets.size()); ++k)
				{
					Vector2int bulletPosition = getBuletPositionFromTime(bullets[k], timer),
						offsetForBullet = Vector2int((Vector2int(dataArraySize * 20, 0) - (bulletPosition - getOffsetForTank()) - bulletPosition).x, -getOffsetForTank().y);
					if (bullets[k]->getFather() != (*objects)[i][j] && collisionCheck((*objects)[i][j], bullets[k], bulletPosition, offsetForBullet))
					{
						(*objects)[i][j]->setHeath((*objects)[i][j]->getHealth() - bullets[k]->damage);
						if ((*objects)[i][j]->getHealth() <= 0)
						{
							needUpdateTank = true;
							needRemoveHangingObjects = true;
							if (typeid(*(*objects)[i][j]) == typeid(Gun))
							{
								highlightingUpdated = true;
							}
						}
						(*objects)[i][j]->needDraw = true;

						breakBullet(components, bulletPositionInComponents, bullets, k, timer - fps);
						--k;
					}
				}
			}
		}
	}

	if (needRemoveHangingObjects)
	{
		removeHangingObjects();
		needUpdateLengthBetweenTanks = true;
	}
}