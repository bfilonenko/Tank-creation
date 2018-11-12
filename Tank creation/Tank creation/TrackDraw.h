#pragma once


#include "ComponentDraw.h"
#include "Track.h"


class TrackDraw : public ComponentDraw
{
	Texture *trackTexture;
	Sprite *trackSprite;
	int numberOfVariant;

public:
	TrackDraw(ComponentParameter *component);

	~TrackDraw();

	void draw(RenderTexture &renderTexture, long timer, Object *object);
};