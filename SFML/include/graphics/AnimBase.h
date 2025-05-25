#pragma once
#include <sstream>

class SpriteSheet;

class AnimBase
{
	friend class SpriteSheet;

public:
	AnimBase();
	virtual ~AnimBase();

	void setSpriteSheet(SpriteSheet* ss) { spriteSheet = ss; }
	void setLooping(bool l) { loop = l; }
	void setName(const std::string& n) { name = n; }
 	void setFrame(int fr);
	bool isInAction();
	bool isPlaying() const { return playing; }
	bool isLooping() const { return loop; }

	int getCurrentFrame() const { return curFrame; }
	int getStartFrame() const { return startFrame; }
	int getEndFrame() const { return endFrame; }
	int getFrameRow() const { return frameRow; }
	float getFrameTime() const { return frameTime; }
	int getFrameActionStart() const { return frameActionStart; }
	int getFrameActionEnd() const { return frameActionEnd; }

	const std::string& getName() const { return name; }

	void play();
	void pause();
	void stop();
	void reset();

	virtual void update(float elapsedTime);

	friend std::stringstream& operator >>(std::stringstream& st, AnimBase& a)
	{
		a.readIn(st);
		return st;
	}

protected:

	virtual void frameStep() = 0;
	virtual void cropSprite() = 0;
	virtual void readIn(std::stringstream& ss) = 0;

	int curFrame;
	int startFrame;
	int endFrame;
	int frameRow;

	int frameActionStart;
	int frameActionEnd;
	float frameTime;
	float elapsedTime;
	bool loop;
	bool playing;

	std::string name;
	SpriteSheet* spriteSheet;
};

