#ifndef _UNIT_MANAGER_H_
#define _UNIT_MANAGER_H_

#include <vector>
#include "Unit.h"

#define UNIT_MANAGER UnitManager::getInstance()

class Unit;
typedef std::string UnitKey;

class UnitManager
{
public:
	static UnitManager*	getInstance();
	static UnitManager*	createInstance();
	static void			destroyInstance();

	void	cleanup();

	Unit*	createUnit(Texture2D& texture2D, int speed, Vector2 pos, Vector2 size, Vector2 scale);
	Unit*	findByIndex(int index);
	void	removeByIndex(int index);

	int		count();

	bool	getPause();
	void	setPause(bool thePause);

	virtual void draw();
	virtual void update();

private:
	UnitManager();
	~UnitManager();

	std::vector<Unit*> m_unitList;
	bool m_isUpdating;

	static UnitManager* sp_instance;
};

#endif // !_UNIT_MANAGER_H_
