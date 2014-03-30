//----------------------------------------------------------------------------------------------------

#ifndef _ANIMATION_HPP_FCEAEAD391463788542A387B3AED3230
#define _ANIMATION_HPP_FCEAEAD391463788542A387B3AED3230
//----------------------------------------------------------------------------------------------------

#include "Animation_fwd.hpp"

#include <string>
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

enum class AnimationId: int
{
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINT,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH, 
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS
};
//----------------------------------------------------------------------------------------------------

struct Animation
{
	Animation(const std::string& n, int f, int l, int fp);

	std::string name;

	int firstFrame;
	int lastFrame;
	int fps;

	float frameDuration;
	float animationDuration;
};
//----------------------------------------------------------------------------------------------------

AnimationVector getAnimations() noexcept;
//----------------------------------------------------------------------------------------------------

class Animator
{
public:
	Animator();

	void setAnimation(const Animation& anim);

	void playPause();

	void update(float dt);

	int getFrame() const
	{
		return currentFrame;
	}

	float getScale() const
	{
		return scale;
	}

private:
	const Animation* animation;

	bool paused {true};
	float time {};
	float scale {};
	int currentFrame {};
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _ANIMATION_HPP_FCEAEAD391463788542A387B3AED3230
//----------------------------------------------------------------------------------------------------
