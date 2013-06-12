//GameTime.h
#ifndef GAMETIME_H_INCLUDED
#define GAMETIME_H_INCLUDED

#include <chrono>

class GameTime
{
public:
	GameTime(float targetFPS = 60.0f);
	~GameTime();

	void StartFrame();
	void EndFrame();

	float GetFPS() const;
	float GetAverageFPS()const;
	int GetFrameCount()const;
	float GetElapsedGameTime()const;
	float GetTimeScale()const;
	void SetTimeScale(float timeScale);
private:
	int _frameCount;
	float _elapsedGameTime; //In Seconds
	float _totalGameTime; //Scaled
	float _timeScale;
	float _targetFPS;
	bool _frameStarted;
	std::chrono::high_resolution_clock::time_point _startFrameTime;
	std::chrono::high_resolution_clock::time_point _endFrameTime;
};
#endif //GAMETIME_H_INCLUDED