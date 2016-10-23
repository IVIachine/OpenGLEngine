#ifndef _COMPONENT_PARENT_H_
#define _COMPONENT_PARENT_H_

#include <Trackable.h>
#include "TransactionProcessor.h"

class Component;
class TransactionProcessor;

class ComponentParent : public Trackable
{
public:
	ComponentParent();
	virtual ~ComponentParent();

private:
	TransactionProcessor m_processor;
};

#endif