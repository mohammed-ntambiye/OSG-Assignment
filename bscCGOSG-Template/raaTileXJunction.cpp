#include "stdafx.h"
#include "raaRoadSet.h"
#include "raaTrafficLightUnit.h"
#include "raaTileXJunction.h"


raaTileXJunction::raaTileXJunction(unsigned int uiName, osg::Node* pNode, raaAnimationPoints* pAP) : raaTile(uiName, pNode, pAP)
{
	raaTrafficLightUnit *pTraficLight2 = new raaTrafficLightUnit();
	pTraficLight2->setTransform(-190.0f, -190.0f, 0.0f, 0.05f);
	m_pLocalRoot->addChild(pTraficLight2->node());
	addLightUnit(pTraficLight2);
	m_pLocalRoot->addUpdateCallback(this);
}

raaTileXJunction::~raaTileXJunction()
{
}
