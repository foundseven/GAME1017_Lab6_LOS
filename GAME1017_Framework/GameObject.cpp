#include "GameObject.h"

GameObject::GameObject() :m_dst({ 0.0f, 0.0f, 0.0f, 0.0f }), m_enabled(true) {}

GameObject::GameObject(const SDL_FRect dst)
    :m_dst(dst), m_enabled(true) {}

SDL_FRect* GameObject::GetDst()
{
    return &m_dst;
}

SDL_FPoint GameObject::GetCenter() const
{
    return { m_dst.x + m_dst.w / 2, m_dst.y + m_dst.h / 2 };
}

const bool GameObject::GetEnabled() const
{
	return m_enabled;
}

void GameObject::SetEnabled(const bool e)
{
	m_enabled = e;
}

Sprite::Sprite(const SDL_Rect src, const SDL_FRect dst)
    :GameObject(dst), m_src(src) {}

SDL_Rect* Sprite::GetSrc()
{
    return &m_src;
}

AnimatedSprite::AnimatedSprite(const SDL_Rect src, const SDL_FRect dst, AnimState state)
	:Sprite(src, dst), m_state(state), m_frame(0), m_frameMax(0), m_sprite(0), m_spriteMin(0), m_spriteMax(0) {}

void AnimatedSprite::SetAnimation(AnimState state, const unsigned short frameMax, const unsigned short spriteMin,
	const unsigned short spriteMax, const int srcY)
{
	m_state = state;
	m_frame = 0;
	m_frameMax = frameMax;
	m_sprite = m_spriteMin = spriteMin;
	m_spriteMax = spriteMax;
	m_src.x = m_src.w * m_sprite;
	m_src.y = srcY;
}
void AnimatedSprite::Animate()
{
	if (m_frame++ == m_frameMax)
	{
		m_frame = 0;
		if (++m_sprite == m_spriteMax)
			m_sprite = m_spriteMin; // I don't use % in case m_sprite doesn't start at 0.
		m_src.x = m_src.w * m_sprite; // Moved to outside if.
	}
}