#ifndef __ENGINE_H__
#define __ENGINE_H__
#include <SDL.h>
#include <SDL_image.h>
#include <chrono>

// Window and Render properties. Sent to RenderManager.
constexpr double kFPS = 60.0;
constexpr const char* kTitle = "GAME1017 Framework";
constexpr int kXPos = SDL_WINDOWPOS_CENTERED;
constexpr int kYPos = SDL_WINDOWPOS_CENTERED;
constexpr int kWidth = 1024;
constexpr int kHeight = 768;
constexpr int kRows = 24;
constexpr int kCols = 32;
constexpr Uint32 kWindowFlags = NULL;
constexpr Uint32 kRenderFlags = NULL;

class Engine
{
public: // Put public heading first so you ALWAYS question why things are public!
	Engine(); 
	int Run();
	const double& GetDeltaTime() const;
	static Engine& Instance(); // Static method for object access.
	bool& Running(); // For EventManager.

private:
	// General engine properties.
	bool m_isRunning;

	// For fixed timestep.
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_end, m_lastFrameTime, m_thisFrameTime;
	std::chrono::duration<double> m_diff, m_lastFrameDuration;
	double m_deltaTime, m_fps;
	
	// Example-specific properties.
	

	// Private methods.
	int Init();
	void HandleEvents();
	void Wake();
	void Update();
	void Sleep();
	void Render();
	void Clean();	
};

#endif
