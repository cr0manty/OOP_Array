#pragma once
#include <cassert>

template<class Array>
class iterator;

template<typename Type>
class Array 
{
	Type * m_pData;
	size_t m_size;
	size_t m_FrontIndex;
	size_t m_BackIndex;
	size_t _nextindex(size_t);
	void destroy();
public:
	typedef iterator<Type> iterator;
	friend iterator;
	Array(size_t = 10);
	Array(const Array &);
	Array(Array &&);
	Array&operator=(const Array&);
	Array&operator=(Array&&);
	void clear();
	size_t capacity();
	size_t size();
	bool empty();
	bool is_full();
	iterator begin();
	iterator end();
	void push_back(const Type &);
	void pop();
	Type front();
	~Array();
};

template<class Basic>
class iterator 
{
	typedef Array<Basic> Array;
	Basic *m_Data;
	size_t index;
public:
	iterator(Basic*);
	bool operator!=(Basic*);
	iterator &operator++();
	Basic operator*();
};

template<typename Type>
inline size_t Array<Type>::_nextindex(size_t _index)
{
	if (_index + 1 == m_size)
		return 0;

	return _index + 1;
}

template<typename Type>
inline void Array<Type>::destroy()
{
	if (capacity())
		delete[] m_pData;
}

template<typename Type>
inline Array<Type>::Array(size_t _size) :
	m_size(_size + 1)
{
	m_pData = new Type[m_size];
	clear();
}

template<typename Type>
inline Array<Type>::Array(const Array &_other)
{
	m_size = _other.m_size;
	m_pData = new Type[m_size];
	clear();
	for (size_t i = 0; i < capacity(); i++)
		m_pData[i] = _other.m_pData[i];
	return *this;
}

template<typename Type>
inline Array<Type>::Array(Array &&_other) :
	m_pData(_other.m_pData), m_size(_other.m_size),
	m_FrontIndex(_other.m_FrontIndex), m_BackIndex(_other.m_BackIndex)
{
	_other.destroy();
	_other.m_BackIndex = 0;
	_other.m_size = 0;
	_other.m_FrontIndex = 0;
}

template<typename Type>
inline Array<Type> & Array<Type>::operator=(const Array &_other)
{
	m_size = _other.m_size;
	m_pData = new Type[m_size];
	clear();
	
	for (size_t i = 0; i < capacity(); i++)
		m_pData[i] = _other.m_pData[i];
	return *this;
}

template<typename Type>
inline Array<Type> & Array<Type>::operator=(Array &&_other)
{
	m_pData =_other.m_pData;
	m_size = _other.m_size;
	m_FrontIndex = _other.m_FrontIndex;
	m_BackIndex = _other.m_BackIndex;

	_other.destroy();
	_other.m_BackIndex = 0;
	_other.m_size = 0;
	_other.m_FrontIndex = 0;
	return *this;
}

template<typename Type>
inline void Array<Type>::clear()
{
	m_FrontIndex = 0;
	m_BackIndex = 0;
}

template<typename Type>
inline size_t Array<Type>::capacity()
{
	return (m_FrontIndex <= m_BackIndex) ?
		m_BackIndex - m_FrontIndex :
		m_BackIndex + m_size - m_FrontIndex;
}

template<typename Type>
inline size_t Array<Type>::size()
{
	return m_size;
}

template<typename Type>
inline bool Array<Type>::empty()
{
	return !capacity();
}

template<typename Type>
inline bool Array<Type>::is_full()
{
	return capacity() == m_size + 1;
}

template<typename Type>
inline iterator<Type> Array<Type>::begin()
{
	return this->m_pData;
}

template<typename Type>
inline iterator<Type> Array<Type>::end()
{
	return &m_pData[capacity()];
}

template<typename Type>
inline void Array<Type>::push_back(const Type &_value)
{
	assert(!is_full());

	m_pData[m_BackIndex] = _value;
	m_BackIndex = _nextindex(m_BackIndex);
}

template<typename Type>
inline void Array<Type>::pop()
{
	assert(!empty());
	m_FrontIndex = _nextindex(m_FrontIndex);
}

template<typename Type>
inline Type Array<Type>::front()
{
	assert(!empty());
	return m_pData[m_FrontIndex];
}

template<typename Type>
inline Array<Type>::~Array()
{
	destroy();
}

template<class Basic>
inline iterator<Basic>::iterator(Basic *_arr) :
	m_Data(_arr), index(0)
{
}

template<class Basic>
inline bool iterator<Basic>::operator!=(Basic * _end)
{
	return this->index  == 1;
}

template<class Basic>
inline iterator<Basic>& iterator<Basic>::operator++()
{
	index++;
	return *this;
}

template<class Basic>
inline Basic iterator<Basic>::operator*()
{
	return m_Data[index];
}
