#pragma once

#include <windows.h>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>

// a basic class as a start for the animated objects. This has a basic SG sub-tree containing a placeholder for the actual model you might use
// It is derived from the animation calbak to recieve a anmiation path

class raaAinimatedComponent: public osg::AnimationPathCallback
{
public:
	raaAinimatedComponent(osg::AnimationPath* pAP);
	virtual ~raaAinimatedComponent();

	osg::MatrixTransform* root();


protected:
	osg::MatrixTransform* m_pRoot;
};

