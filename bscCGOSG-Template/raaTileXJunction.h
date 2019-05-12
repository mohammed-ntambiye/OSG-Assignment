#pragma once
#include "raaTile.h"
#include "raaJunctionController.h"

class raaTileXJunction: public raaTile, public raaJunctionController 
{
public:
	raaTileXJunction(unsigned int uiName, osg::Node* pNode, raaAnimationPoints* pAP);
	virtual ~raaTileXJunction();
};

