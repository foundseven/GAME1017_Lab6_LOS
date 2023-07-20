#include "Engine.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "States.h"
#include <ctime>
#include <iostream>
#include <string>

Engine::Engine():m_isRunning(false), m_deltaTime(0.0),
	m_fps(0.0), m_diff(0.0), m_lastFrameDuration(0.0) {}

int Engine::Run()
{
	if (m_isRunning)
	{
		return 1; // 1 arbitrarily means that engine is already running.
	}
	if (Init() != 0)
	{
		return 2; // 2 arbitrarily means that something went wrong in init.
	}
	while (m_isRunning) // Main game loop. Run while isRunning = true.
	{
		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_isRunning == true)
			Sleep();
	}
	Clean(); // Deinitialize SDL and free up memory.
	return 0;
}

const double& Engine::GetDeltaTime() const
{
	return m_deltaTime;
}

Engine& Engine::Instance()
{
	static Engine instance; // Magic statics. Creating the object.
	return instance;
}

bool& Engine::Running()
{
	return m_isRunning;
}

int Engine::Init()
{
	std::cout << "Initializing framework..." << std::endl;
	srand((unsigned)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	if (REMA::Init(kTitle, kXPos, kYPos, kWidth, kHeight, kWindowFlags, kRenderFlags) == 1)
	{
		return 1; // Something went wrong in RenderManager Init().
	}
	// Initialize SDL sublibraries and engine subcomponents.
	EVMA::Init();
	SOMA::Init();
	TEMA::Init(); // Note that the TextureManager initializes SDL_image sublibrary.
	STMA::ChangeState(new TitleState());
	// Initialize rest of framework.
	m_fps = 1.0 / kFPS; // Converts FPS into a fraction of seconds.
	m_lastFrameTime = std::chrono::high_resolution_clock::now();
	m_isRunning = true; // Start your engine.
	return 0;
}

void Engine::HandleEvents()
{
	EVMA::HandleEvents();
}

void Engine::Wake()
{
	m_thisFrameTime = std::chrono::high_resolution_clock::now(); // New snapshot of number of seconds.
	m_lastFrameDuration = m_thisFrameTime - m_lastFrameTime;
	m_deltaTime = m_lastFrameDuration.count(); // Now we have our deltaTime multiplier.
	m_lastFrameTime = m_thisFrameTime;

	m_start = m_thisFrameTime; // Comment this out to just use deltaTime.
}

void Engine::Update()
{
	STMA::Update();
}

void Engine::Sleep() 
{
	// Note: Not really better, but you can decide to not limit frameRate and just use deltaTime.
	// Comment all this out to just use deltaTime.
	m_end = std::chrono::high_resolution_clock::now();
	m_diff = m_end - m_start; // Similar to before, but now chrono and double.
	if (m_diff.count() < m_fps)
		SDL_Delay((Uint32)((m_fps - m_diff.count()) * 1000.0)); // Sleep for number of ms.
}

void Engine::Render()
{
	STMA::Render();
}

void Engine::Clean()
{
	std::cout << "Cleaning up..." << std::endl;
	STMA::Quit();
	EVMA::Quit();
	SOMA::Quit();
	TEMA::Quit();
	REMA::Quit();
	SDL_Quit();
}