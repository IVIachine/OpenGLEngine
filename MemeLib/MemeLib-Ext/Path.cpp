#include "Path.h"
#include "Node.h"
#include <algorithm>

Path::Path()
{
}

Path::Path(const std::vector<Node*>& list)
{
	for (auto& i : list)
	{
		add(i);
	}
}

Path::~Path()
{
}


Node* Path::peek(size_t index) const
{
	if ((unsigned int)index < m_nodeList.size())
	{
		return m_nodeList[index];
	}
	else
	{
		return NULL;
	}
}

Node* Path::peekNext() const
{
	if (m_nodeList.size() > 0)
	{
		return m_nodeList.back();
	}
	else
	{
		return NULL;
	}
}

Node* Path::getAndRemoveNext()
{
	if (m_nodeList.size() > 0)
	{
		Node* pNode = m_nodeList.back();
		m_nodeList.pop_back();
		return pNode;
	}
	else
	{
		return NULL;
	}
}

void Path::removeFront()
{
	if (m_nodeList.size() > 0)
	{
		m_nodeList.erase(m_nodeList.begin() + 0);
	}
}

size_t Path::size() const
{
	return m_nodeList.size();
}


void Path::add(Node* pNode)
{
	m_nodeList.push_back(pNode);
}

void Path::clear()
{
	m_nodeList.clear();
}

bool Path::contains(Node* pNode) const
{
	bool retVal = false;

	for (unsigned int i = 0; i<m_nodeList.size(); i++)
	{
		if (m_nodeList[i] == pNode)
		{
			retVal = true;
			break;
		}
	}
	return retVal;
}

void Path::resize(size_t value)
{
	std::vector<Node*> temp;

	for (size_t i = 0; i < value && i < size(); i++)
	{
		temp.push_back(m_nodeList[i]);
	}

	m_nodeList = temp;
}

void Path::reverse()
{
	std::reverse(m_nodeList.begin(), m_nodeList.end());
}


Node* Path::begin()
{
	if (size() > 0)
	{
		return m_nodeList[0];
	}

	return NULL;
}

Node* Path::end()
{
	if (size() > 0)
	{
		return m_nodeList[size() - 1];
	}

	return NULL;
}


Node* Path::operator[](size_t index) const
{
	return peek(index);
}