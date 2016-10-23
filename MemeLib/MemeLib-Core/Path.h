#ifndef _PATH_H_
#define _PATH_H_

#include <glm.hpp>
#include <vector>
#include <Trackable.h>
#include "NodeRecord.h"

class Node;

class Path :public Trackable
{
public:
	Path();
	Path(const std::vector<Node*>& list);
	~Path();

	Node*	peek(size_t index) const;
	Node*	peekNext() const;
	Node*	getAndRemoveNext();
	size_t	size() const;

	void	add(Node* pNode);
	void	clear();
	bool	contains(Node* pNode) const;
	void	resize(size_t size);
	void	reverse();

	Node*	begin();
	Node*	end();

	Node* operator[](size_t index) const;

private:
	std::vector<Node*> mNodes;

};

#endif // !_PATH_H_
