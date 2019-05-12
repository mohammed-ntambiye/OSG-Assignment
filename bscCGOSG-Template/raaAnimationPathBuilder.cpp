#include "stdafx.h"
#include <windows.h>

#include "raaRoadSet.h"
#include "raaTile.h"
#include <osgDB/ReadFile>
#include "raaAnimationPathBuilder.h"

raaAnimationPathBuilder::raaAnimationPathBuilder(osg::AnimationPath *pAP, osg::Node *pRoot) : m_pAP(pAP), m_pRoot(pRoot)
{

}

raaAnimationPathBuilder::~raaAnimationPathBuilder()
{
}

void raaAnimationPathBuilder::load(std::string sFile)
{
	std::ifstream file(sFile);
	unsigned int uiTile, uiAP;

	while (!file.eof())
	{
		file >> uiTile >> uiAP;
		m_lTiles.push_back(uiTile);
		m_lPoints.push_back(uiAP);
	}

	file.close();
}

void raaAnimationPathBuilder::save(std::string sFile)
{
	std::ofstream file(sFile);
	unsigned int uiTile, uiAP;

	uIntList::iterator itTile = m_lTiles.begin();
	uIntList::iterator itAP = m_lPoints.begin();

	for (; itTile != m_lTiles.end() && itAP != m_lPoints.end(); itTile++, itAP++)
	{
		file << (*itTile) << " " << (*itAP) << std::endl;
	}
	file.close();

}

void raaAnimationPathBuilder::addControlPoint(unsigned int uiTile, unsigned int uiAP)
{
	m_lTiles.push_back(uiTile);
	m_lPoints.push_back(uiAP);
}

void raaAnimationPathBuilder::createAnimationPath() {
	raaRoadSet *roadSet = raaRoadSet::instance();
	uIntList::iterator itTile = m_lTiles.begin();
	uIntList::iterator itAP = m_lPoints.begin();

	float f = 0.0f, speed = 350.0f;
	osg::Vec3f v1;
	for (; itTile != m_lTiles.end(); itTile++, itAP++) {
		osg::Matrixf m = osg::computeLocalToWorld(roadSet->tile(*itTile)->lowestTransform()->getParentalNodePaths(m_pRoot)[0]);
		osg::Vec3f currentV = roadSet->tile(*itTile)->animPointPosition(*itAP) * m;
		float time = (currentV - v1).length() / speed;
		v1 = currentV;
		m_pAP->insert(f += time, osg::AnimationPath::ControlPoint(currentV, roadSet->tile(*itTile)->animPointRotation(*itAP) * m.getRotate()));
	}
}