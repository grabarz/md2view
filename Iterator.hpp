//----------------------------------------------------------------------------------------------------

#ifndef _ITERATOR_HPP_2868DEF94E970249751211C4DEC0876F
#define _ITERATOR_HPP_2868DEF94E970249751211C4DEC0876F
//----------------------------------------------------------------------------------------------------

#include <vector>
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template <typename T>
class Iterator
{
public:
	Iterator(std::vector<T>& v)
		: vector {v}
		, _position {0}
	{
	}

	void next()
	{
		++_position;
		_position %= vector.size();
	}

	void prev()
	{
		_position += vector.size() - 1;
		_position %= vector.size();
	}

	bool empty() const
	{
		return vector.empty();
	}

	const T& get() const
	{
		return vector[_position];
	}

	T& get()
	{
		return vector[_position];
	}

	std::size_t position() const
	{
		return _position;
	}

private:
	std::vector<T>& vector;
	std::size_t _position;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _ITERATOR_HPP_2868DEF94E970249751211C4DEC0876F
//----------------------------------------------------------------------------------------------------
