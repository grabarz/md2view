//----------------------------------------------------------------------------------------------------

#ifndef _OBJECT_HPP_4148D8CEBCD4CFB2B8315161727493E7
#define _OBJECT_HPP_4148D8CEBCD4CFB2B8315161727493E7
//----------------------------------------------------------------------------------------------------

#include "Object_fwd.hpp"

#include <vector>

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
	Object(std::vector<ProgramPtr>& progs, std::vector<ModelPtr>& mods);

	void update(float dt);

	void play();
	void pause();

	void nextFrame();
	void prevFrame();

	void nextAnimation();
	void prevAnimation();

	void nextModel();
	void nextProgram();

	Program& getProgram();
	Model& getModel();

private:
	Iterator<ProgramPtr> program;
	Iterator<ModelPtr> model;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _OBJECT_HPP_4148D8CEBCD4CFB2B8315161727493E7
//----------------------------------------------------------------------------------------------------
