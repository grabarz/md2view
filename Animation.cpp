//----------------------------------------------------------------------------------------------------

#include "Animation.hpp"

#include <algorithm>
#include <cmath>
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

Animation::Animation(const std::string& n, int f, int l, int fp)
	: name {n}
	, firstFrame {f}
	, lastFrame {l}
	, fps {fp}
	, frameDuration {static_cast<float>(1.0 / (fps))}
	, animationDuration {static_cast<float>((lastFrame - firstFrame + 1) * frameDuration)}
{
}
//----------------------------------------------------------------------------------------------------

AnimationVector getAnimations() noexcept
{
	AnimationVector animation = {
		{"STAND", 0, 39, 9},
		{"RUN", 40, 45, 10},
		{"ATTAC", 46, 53, 10},
		{"PAIN_A", 54, 57, 7},
		{"PAIN_B", 58, 61, 7},
		{"PAIN_C", 62, 65, 7},
		{"JUMP", 66, 71, 7},
		{"FLIP", 72, 83, 7},
		{"SALUTE", 84, 94, 7},
		{"FALLBACK", 95, 111, 10},
		{"WAVE", 112, 122, 7},
		{"PONT", 123, 134, 6},
		{"CROUCH_STAND", 135, 153, 10},
		{"CROUCH_WALK", 154, 159, 7},
		{"CROUCH_ATTACK", 160, 168, 10},
		{"CROUCH_PAIN", 169, 172, 7},
		{"CROUCH_DEATH", 173, 177, 5},
		{"DEATH_FALLBACK", 178, 183, 7},
		{"DEATH_FALLFORWARD", 184, 189, 7},
		{"DEATH_FALLBACKSLOW", 190, 197, 7},
		{"BOOM", 198, 198, 5}
	};

	return animation;
}
//----------------------------------------------------------------------------------------------------

Animator::Animator()
{
}
//----------------------------------------------------------------------------------------------------

void Animator::setAnimation(const Animation& anim)
{
	animation = &anim;
	time = 0.0;
	currentFrame = animation->firstFrame;
	scale = 0.0;
}
//----------------------------------------------------------------------------------------------------

void Animator::playPause()
{
	paused = !paused;
}
//----------------------------------------------------------------------------------------------------

void Animator::update(float dt)
{
	if (!paused)
	{
		time += dt;

		if (time >= animation->animationDuration)
			time -= animation->animationDuration;

		float a = time / animation->frameDuration;
		float f = std::floor(a);
		currentFrame = animation->firstFrame + static_cast<int>(f);
		scale = 0.1; // needs some fixes
	}
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
