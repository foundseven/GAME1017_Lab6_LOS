#ifndef __STATES_H__
#define __STATES_H__
#include <vector>
#include <string>
#include "GameObject.h"

// An abstract class is one that cannot be instantiated. 
// Why? Because they'd be a base class most likely.
class State // This is the abstract base class for all state subclasses.
{
public:
	virtual ~State() = default;
	virtual void Enter() = 0; // = 0 means pure virtual. Method MUST be defined in subclass.
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume() {};
	void AddChild(std::string key, GameObject* object);
	GameObject* GetChild(const std::string& key);
	template <class T>
	T GetChild(const std::string& key);
	void RemoveChild(const std::string& key);
	
protected: // Private but inherited.
	std::vector<std::pair<std::string, GameObject*>> m_objects;
	State() = default;
};

class TitleState : public State
{
public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void Exit();
private:

};

class PauseState : public State
{
public:
	PauseState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class GameState : public State
{
public:
	GameState();
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume();
private:
};
#endif