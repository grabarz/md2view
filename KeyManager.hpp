//----------------------------------------------------------------------------------------------------

#ifndef _KEYMANAGER_HPP_0BA1D8ADD75475B94FEAE0F8DE84EA98
#define _KEYMANAGER_HPP_0BA1D8ADD75475B94FEAE0F8DE84EA98
//----------------------------------------------------------------------------------------------------

#include "KeyManager_fwd.hpp"

#include <functional>
#include <map>
#include <ostream>
#include <string>

#include <SDL2/SDL.h>
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

class KeyManager
{
public:
	typedef std::function<void ()> Action;

	KeyManager();

	void addAction(SDL_Keycode key, const Action& actionDown, const std::string& desc);
	void addAction(SDL_Keycode key, const Action& actionDown, const Action& actionUp, const std::string& desc);

	void processDown(SDL_Keycode key);
	void processUp(SDL_Keycode key);

	friend std::ostream& operator<<(std::ostream& stream, const KeyManager& mngr);

private:
	struct ActionData
	{
		Action actionDown;
		Action actionUp;

		std::string description;
	};

	std::map<SDL_Keycode, ActionData> keyMap;
};
//----------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const KeyManager& mngr);
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _KEYMANAGER_HPP_0BA1D8ADD75475B94FEAE0F8DE84EA98
//----------------------------------------------------------------------------------------------------
