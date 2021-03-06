#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include <Trackable.h>

template <class T, size_t SIZE>
class CircularQueue : public Trackable
{
public:
	CircularQueue()
	{
		mCapacity = SIZE;
		mFront = 0;
		mBack = 0;
		mNumEntries = 0;
	}

	virtual ~CircularQueue() {}

	bool pushBack(const T& item)
	{
		//return false if not successfully added (not enough space)
		if (mNumEntries >= mCapacity)
		{
			return false;
		}

		mArray[mBack] = item;
		mBack++;
		mNumEntries++;

		if (mBack >= mCapacity)
		{
			mBack = 0;
		}

		return true;
	}

	bool popFront(T& item)
	{
		//returns false if queue is empty
		if (mNumEntries == 0)
		{
			return false;
		}

		item = mArray[mFront];
		mFront++;
		mNumEntries--;

		if (mFront >= mCapacity)
		{
			mFront = 0;
		}

		return true;
	}

private:
	T mArray[SIZE];
	size_t mCapacity;
	size_t mBack;
	size_t mFront;
	size_t mNumEntries;
};

#endif // !_CIRCULAR_QUEUE_H_
