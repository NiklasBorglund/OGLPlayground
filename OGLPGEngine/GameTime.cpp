//GameTime.cpp
#include "GameTime.h"
GameTime::GameTime(float targetFPS): _frameCount(0), _elapsedGameTime(0.0f),
		_totalGameTime(0.0f),
		_frameStarted(false), _timeScale(1.0f), _targetFPS(targetFPS),
		_startFrameTime(std::chrono::high_resolution_clock::now()),
		_endFrameTime(std::chrono::high_resolution_clock::now())
{

}
GameTime::~GameTime(){}

void GameTime::StartFrame()
{
	if(!_frameStarted)
	{
		_frameStarted = true;
		_frameCount++;
		_startFrameTime = std::chrono::high_resolution_clock::now();
	}
}
void GameTime::EndFrame()
{
	if(_frameStarted)
	{
		_frameStarted = false;
		_endFrameTime = std::chrono::high_resolution_clock::now();
		_elapsedGameTime =  std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1,1>>>(_endFrameTime - _startFrameTime).count();

		//if the elapsed game time is too large, we must have resumed from a break point
		// frame-lock to the target rate this frame
		if(_elapsedGameTime >= (1.0f / 10.0f))
		{
			_elapsedGameTime = (1.0f / _targetFPS);
		}

		_totalGameTime += _elapsedGameTime * _timeScale;
	}
}

float GameTime::GetFPS() const
{
	return 1.0f / _elapsedGameTime;
}
float GameTime::GetAverageFPS()const
{
	return _frameCount / _totalGameTime;
}
int GameTime::GetFrameCount()const
{
	return _frameCount;
}
float GameTime::GetElapsedGameTime()const
{
	return _elapsedGameTime * _timeScale;
}
float GameTime::GetTimeScale()const
{
	return _timeScale;
}
void GameTime::SetTimeScale(float timeScale)
{
	_timeScale = timeScale;
}