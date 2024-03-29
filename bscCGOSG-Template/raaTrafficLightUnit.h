#pragma once

#include <windows.h>
#include <osg/Node>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osg/Geode>

#include <list>

typedef std::list<class raaTrafficLightUnit*>raaTrafficLights;

// a basic traffic light class. You will need to extend and develop this to operate the lights and develop junctions and controls for the animation 

class raaTrafficLightUnit : public osg::Node
{
public:

	raaTrafficLightUnit();
	virtual ~raaTrafficLightUnit();

	static void initAsset(std::string sFile);
	static void finshAsset();

	void setTransform(float fX, float fY, float fRot, float fScale);
	void setGreen();
	void setAmber();
	void setRed();
	osg::Node* node();
	osg::MatrixTransform* getBox();
	osg::MatrixTransform* getLight();
	bool testDetection(osg::Group *pWorldRoot, osg::Vec3f vPos);
	int state;		//1 for red //2 for amber //3 for green
protected:
	static osg::Node* sm_pAsset;
	static osg::Material* sm_pRedOn;
	static osg::Material* sm_pRedOff;
	static osg::Material* sm_pAmberOn;
	static osg::Material* sm_pAmberOff;
	static osg::Material* sm_pGreenOn;
	static osg::Material* sm_pGreenOff;


	osg::MatrixTransform* m_pTraslation;
	osg::MatrixTransform* m_pRotation;
	osg::MatrixTransform* m_pScale;
	osg::MatrixTransform* m_pBoxMT;
	osg::MatrixTransform* m_pBoxTranslateMT;

	osg::Geode* m_pRed;
	osg::Geode* m_pGreen;
	osg::Geode* m_pAmber;

	static void materialBuilder(osg::Material* pOn, osg::Material* pOff, osg::Vec3f vMat);

	static raaTrafficLights sm_lLights;
};

