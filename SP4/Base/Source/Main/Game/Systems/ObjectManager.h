/*
Copyright (c) Lim Rui An, Ryan 2016

Creator(s)    : Lim Rui An, Ryan
Creation Date : 14 November 2016 15:20 PM
File Name     : ObjectManager.h
Purpose       : Defines the object manager
*/

#ifndef _OBJECT_CONTAINER_H
#define _OBJECT_CONTAINER_H

#include "../Miscellaneous/DetectMemoryLeak.h"
#include "../../Engine/Internal/SingletonTemplate.h"

class ObjectManager : public SingletonTemplate<ObjectManager>
{
public:
	void Exit();

	float WorldWidth;
	float WorldHeight;
	const int MaxItems = 20;

private:
};

#endif // _OBJECT_CONTAINER_H