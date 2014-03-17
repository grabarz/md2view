//----------------------------------------------------------------------------------------------------

#include "KeyManager.hpp"
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

KeyManager::KeyManager()
{
}
//----------------------------------------------------------------------------------------------------

void KeyManager::addAction(SDL_Keycode key, const Action& actionDown, const std::string& desc)
{
	ActionData data;

	data.actionDown = actionDown;
	data.description = desc;

	keyMap[key] = data;
}
//----------------------------------------------------------------------------------------------------

void KeyManager::addAction(
	SDL_Keycode key, const Action& actionDown, const Action& actionUp, const std::string& desc)
{
	ActionData data;

	data.actionDown = actionDown;
	data.actionUp = actionUp;
	data.description = desc;

	keyMap[key] = data;
}
//----------------------------------------------------------------------------------------------------

void KeyManager::processDown(SDL_Keycode key)
{
	auto it = keyMap.find(key);

	if (it != keyMap.end())
	{
		auto a = it->second.actionDown;

		if (a)
			a();
	}
}
//----------------------------------------------------------------------------------------------------

void KeyManager::processUp(SDL_Keycode key)
{
	auto it = keyMap.find(key);

	if (it != keyMap.end())
	{
		auto a = it->second.actionUp;

		if (a)
			a();
	}
}
//----------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const KeyManager& mngr)
{
	for (const auto& key : mngr.keyMap)
	{
		stream << SDL_GetKeyName(key.first) << " - " << key.second.description << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
