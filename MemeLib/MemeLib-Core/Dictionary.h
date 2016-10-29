#ifndef _MEMORY_MANAGER_H_
#define _MEMORY_MANAGER_H_

#include <Trackable.h>
#include <iterator>
#include <map>

template <class TKey, class TValue>
class Dictionary : public Trackable
{
public:
	Dictionary();
	~Dictionary();

	void	cleanup();
	TValue* addData(TKey key, TValue* value);
	TValue* getData(TKey key);
	TValue* setData(TKey key, TValue* value);

	TValue*	operator[](TKey key);

private:
	std::map<TKey, TValue*> m_data;	
};

/*	Constructor/Destructor
* * * * * * * * * * * * * * */
template<class TKey, class TValue>
inline Dictionary<TKey, TValue>::Dictionary()
{
}

template<class TKey, class TValue>
inline Dictionary<TKey, TValue>::~Dictionary()
{

}


/*	Functions
* * * * * * * * * * * * * * */
template<class TKey, class TValue>
inline void Dictionary<TKey, TValue>::cleanup()
{
	std::map<TKey, TValue*>::iterator it;
	for (it = m_data.begin(); it != m_data.end(); ++it)
	{
		TValue* tmp = it->second;
		delete tmp;
	}
}

template<class TKey, class TValue>
inline TValue * Dictionary<TKey, TValue>::addData(TKey key, TValue* value)
{
	if (m_data.find(key) == m_data.end())
	{
		m_data[key] = value;

		return getData(key);
	}

	return NULL;
}

template<class TKey, class TValue>
inline TValue * Dictionary<TKey, TValue>::getData(TKey key)
{
	if (m_data.find(key) != m_data.end())
	{
		return m_data[key];
	}

	return NULL;
}

template<class TKey, class TValue>
inline TValue * Dictionary<TKey, TValue>::setData(TKey key, TValue* value)
{
	if (m_data.find(key) != m_data.end())
	{
		m_data[key] = value;

		return getData(key);
	}

	return NULL;
}


/*	Operator Overloads
* * * * * * * * * * * * * * */
template<class TKey, class TValue>
inline TValue * Dictionary<TKey, TValue>::operator[](TKey key)
{
	return getData(key);
}

#endif // !_MEMORY_MANAGER_H_
