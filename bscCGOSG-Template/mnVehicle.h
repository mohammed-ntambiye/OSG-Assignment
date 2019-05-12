#pragma once

#include <windows.h>
#include <osg/AnimationPath>
#include <osg/Node>
#include <osg/MatrixTransform>
#include "raaAinimatedComponent.h"

class mnVehicle : public raaAinimatedComponent
{
public:
	mnVehicle(osg::AnimationPath* pAP);
	virtual ~mnVehicle();
	void operator()(osg::Node* node, osg::NodeVisitor* nv);
};
