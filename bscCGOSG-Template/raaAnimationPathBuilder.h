#pragma once

//#include <windows.h>
#include <osg/AnimationPath>
#include <list>

typedef std::list<unsigned int> uIntList;

// NOTE: This is a basic class that will load/save the animation data from a  file and store it in two lists
// containing the tile and actual animation point for each step in an animation. You should extend and enhance this to populate the annimation paths
// you wish to use

class raaAnimationPathBuilder
{
public:
	raaAnimationPathBuilder(osg::AnimationPath *pAP, osg::Node* pRoot);
	virtual ~raaAnimationPathBuilder();

	void load(std::string sFile);  // read animation file and populate 
	void save(std::string sFile); // save the animation points

	void addControlPoint(unsigned int uiTile, unsigned int uiAP); // manually add points

	void createAnimationPath();

protected:
	osg::AnimationPath *m_pAP;
	osg::Node *m_pRoot;
	uIntList m_lTiles;
	uIntList m_lPoints;
};