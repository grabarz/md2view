//----------------------------------------------------------------------------------------------------

#ifndef _OBJECT_HPP_4148D8CEBCD4CFB2B8315161727493E7
#define _OBJECT_HPP_4148D8CEBCD4CFB2B8315161727493E7
//----------------------------------------------------------------------------------------------------

#include "Object_fwd.hpp"

#include <vector>

#include "Animation.hpp"
#include "Iterator.hpp"
#include "Model_fwd.hpp"
#include "Program_fwd.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

class Object
{
public:
	Object(ProgramVector& progs, ModelVector& mods, AnimationVector& anim);

	void update(float dt);

	void playPause();

	void nextFrame();
	void prevFrame();

	void nextAnimation();
	void prevAnimation();

	void nextModel();
	void nextProgram();

	Program& getProgram()
	{
		return **program;
	}

	Model& getModel()
	{
		return **model;
	}

	int getFrame() const
	{
		return animator.getFrame();
	}

	float getScale() const
	{
		return animator.getScale();
	}

private:
	Iterator<ProgramPtr> program;
	Iterator<ModelPtr> model;
	Iterator<Animation> animation;

	Animator animator;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _OBJECT_HPP_4148D8CEBCD4CFB2B8315161727493E7
//----------------------------------------------------------------------------------------------------
