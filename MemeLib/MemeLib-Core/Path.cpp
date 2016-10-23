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
	if ((unsigned int)index < mNodes.size())
	{
		return mNodes[index];
	}
	else
	{
		return NULL;
	}
}

Node* Path::peekNext() const
{
	if (mNodes.size() > 0)
	{
		return mNodes.back();
	}
	else
	{
		return NULL;
	}
}

Node* Path::getAndRemoveNext()
{
	if (mNodes.size() > 0)
	{
		Node* pNode = mNodes.back();
		mNodes.pop_back();
		return pNode;
	}
	else
	{
		return NULL;
	}
}

size_t Path::size() const
{
	return mNodes.size();
}


void Path::add(Node* pNode)
{
	mNodes.push_back(pNode);
}

void Path::clear()
{
	mNodes.clear();
}

bool Path::contains(Node* pNode) const
{
	bool retVal = false;

	for (unsigned int i = 0; i<mNodes.size(); i++)
	{
		if (mNodes[i] == pNode)
		{
			retVal = true;
			break;
		}
	}
	return retVal;
}

void Path::resize(size_t size)
{
	std::vector<Node*> temp;

	for (size_t i = 0; i < size && i < size(); i++)
	{
		temp.push_back(mNodes[i]);
	}

	mNodes = temp;
}

void Path::reverse()
{
	std::reverse(mNodes.begin(), mNodes.end());
}


Node* Path::begin()
{
	if (size() > 0)
	{
		return mNodes[0];
	}

	return NULL;
}

Node* Path::end()
{
	if (size() > 0)
	{
		return mNodes[size() - 1];
	}

	return NULL;
}


Node* Path::operator[](size_t index) const
{
	return peek(index);
}