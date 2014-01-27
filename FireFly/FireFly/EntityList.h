#pragma once
class EntityList
{
public:
	static EntityList &getEntityList();

private:
	EntityList();
	~EntityList();
	void operator=(const EntityList &el);
	static EntityList eL;
};

