#include "../../include/graphics/AnimBase.h"
#include "../../include/graphics/SpriteSheet.h"

AnimBase::AnimBase() : 
	curFrame(0),
	startFrame(0),
	endFrame(0),
	frameRow(0),
	frameTime(1.f),
	elapsedTime(0.f),
	frameActionStart(-1),
	frameActionEnd(-1),
	loop(false),
	playing(false),
	spriteSheet(nullptr)
{}

AnimBase::~AnimBase() {}

void AnimBase::setFrame(int fr)
{
	if ((fr >= startFrame && fr <= endFrame) || (fr >= endFrame && fr <= startFrame))
		curFrame = fr;
}

bool AnimBase::isInAction()
{
	if (frameActionStart == -1 || frameActionEnd == -1)
		return true;

	return (curFrame >= frameActionStart && curFrame <= frameActionEnd);
}

void AnimBase::play()
{
	playing = true;
}

void AnimBase::pause()
{
	playing = false;
}

void AnimBase::stop()
{
	playing = false;
	reset();
}

void AnimBase::reset()
{
	curFrame = startFrame;
	elapsedTime = 0.0f;
	cropSprite();
}

void AnimBase::update(float eTime)
{
	if (!playing)
		return;

	elapsedTime += eTime;

	if (elapsedTime < frameTime)
		return;

	frameStep();
	cropSprite();
	elapsedTime = 0;
}


