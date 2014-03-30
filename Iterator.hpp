//----------------------------------------------------------------------------------------------------

#ifndef _ITERATOR_HPP_2868DEF94E970249751211C4DEC0876F
#define _ITERATOR_HPP_2868DEF94E970249751211C4DEC0876F
//----------------------------------------------------------------------------------------------------

#include <vector>
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

template <typename T, typename V = std::vector<T>>
class Iterator
{
public:
	Iterator(V& v)
		: vector {&v}
		, _position {0}
	{
	}

	Iterator<T, V>& operator++()
	{
		++_position;
		_position %= vector->size();

		return *this;
	}

	Iterator<T, V>& operator++(int)
	{
		++*this;

		return *this;
	}

	Iterator<T, V>& operator--()
	{
		_position += vector->size() - 1;
		_position %= vector->size();

		return *this;
	}

	Iterator<T, V>& operator--(int)
	{
		--*this;

		return *this;
	}

	bool empty() const
	{
		return vector->empty();
	}

	T& operator*() const
	{
		return (*vector)[_position];
	}

	T& operator*()
	{
		return (*vector)[_position];
	}

	const T& operator->() const
	{
		return (*vector)[_position];
	}

	T& operator->()
	{
		return (*vector)[_position];
	}

	std::size_t position() const
	{
		return _position;
	}

private:
	V* vector;
	std::size_t _position;
};
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------

#endif // _ITERATOR_HPP_2868DEF94E970249751211C4DEC0876F
//----------------------------------------------------------------------------------------------------
