#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"

class CoreEngine {
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	static CoreEngine* GetInstance();

	bool Oncreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();

private:
	CoreEngine();
	~CoreEngine();
	void Update(const float deltaTime_);
	void Render();
	void Ondestroy();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;
};

#endif COREENGINE_H