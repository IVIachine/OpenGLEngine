#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <Trackable.h>
#include <iterator>
#include <map>

template <class TKey, class TValue>
class Dictionary : public Trackable
{
public:
	Dictionary();
	~Dictionary();

	void	clear();
	TValue* addData(TKey key, TValue* value);
	TValue* getData(TKey key);
	TValue* setData(TKey key, TValue* value);
	bool	erase(TKey key);

	TValue*	operator[](TKey key);

	std::map<TKey, TValue*> getData() const { return m_data; };

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
inline void Dictionary<TKey, TValue>::clear()
{
	std::map<TKey, TValue*>::iterator it;
	for (it = m_data.begin(); it != m_data.end(); ++it)
	{
		delete it->second;
	}

	m_data.clear();
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

template<class TKey, class TValue>
inline bool Dictionary<TKey, TValue>::erase(TKey key)
{
	std::map<TKey, TValue*>::iterator it = m_data.find(key);
	if(it != m_data.end())
	{
		TValue* tmp = it->second;

		it->second->~TValue();

		m_data.erase(key);

		return true;
	}

	return false;
}


/*	Operator Overloads
* * * * * * * * * * * * * * */
template<class TKey, class TValue>
inline TValue * Dictionary<TKey, TValue>::operator[](TKey key)
{
	return getData(key);
}

#endif // !_DICTIONARY_H_
