/*
Copyright (c) Lim Rui An, Ryan 2016

Creator(s)    : Lim Rui An, Ryan
Creation Date : 30 September 2016 10:40 AM
File Name     : SceneEntity.h
Purpose       : Defines the base functions and variables for a scene
*/

#ifndef SCENE_ENTITY_H
#define SCENE_ENTITY_H

#include "../Internal/Entity.h"
#include "MatrixStack.h"

class SceneEntity : public Entity
{
public:
	SceneEntity() : Entity() {
        modelStack = new MS();
        viewStack = new MS();
        projectionStack = new MS();
    };
    virtual ~SceneEntity() {
        if (modelStack)
            delete modelStack;
        if (viewStack)
            delete viewStack;
        if (projectionStack)
            delete projectionStack;
    };

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

    MS *modelStack;
    MS *viewStack;
    MS *projectionStack;

private:
};

#endif