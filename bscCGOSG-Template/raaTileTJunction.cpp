#include "stdafx.h"
#include "raaRoadSet.h"
#include "raaTileTJunction.h"
#include "raaTrafficLightUnit.h"


raaTileTJunction::raaTileTJunction(unsigned int uiName, osg::Node* pNode, raaAnimationPoints* pAP): raaTile(uiName, pNode, pAP)
{
	osg::Matrixf m;
	m.makeTranslate(-2.0f*raaRoadSet::sm_fTileUnit, 0.0, 0.0);
	m_pOffset->setMatrix(m);

	raaTrafficLightUnit *pL1 = new raaTrafficLightUnit();
	pL1->setTransform(-190.0f, -190.0f, 0.0f, 0.05f);
	m_pLocalRoot->addChild(pL1->node());
	addLightUnit(pL1);
	m_pLocalRoot->addUpdateCallback(this);
}


raaTileTJunction::~raaTileTJunction()
{
}
