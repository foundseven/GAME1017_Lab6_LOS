#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <SDL_rect.h>

enum AnimState { STATE_IDLING, STATE_RUNNING };

class GameObject
{
public:
	virtual ~GameObject() = default;
	SDL_FRect* GetDst();
	SDL_FPoint GetCenter() const;
	virtual void Update() = 0;
	virtual void Render() = 0;
	const bool GetEnabled() const; 
	void SetEnabled(const bool e);

protected: // private but inherited.
	SDL_FRect m_dst;
	bool m_enabled;
	GameObject();
	GameObject(const SDL_FRect dst);
};

class Sprite : public GameObject
{
public:
	SDL_Rect* GetSrc();
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	SDL_Rect m_src;
	Sprite(const SDL_Rect src, const SDL_FRect dst);
};

class AnimatedSprite : public Sprite
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

protected: 
	unsigned short m_frame, m_frameMax, m_sprite, m_spriteMin, m_spriteMax;
	AnimState m_state;
	AnimatedSprite(const SDL_Rect src, const SDL_FRect dst, AnimState state);
	void SetAnimation(AnimState state, const unsigned short frameMax, const unsigned short spriteMin,
		const unsigned short spriteMax, const int srcY = 0);
	void Animate();
};

#endif

