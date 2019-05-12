#pragma once

#include <windows.h>
#include <osg/NodeCallback>

#include <list>

class raaTrafficLightUnit;
class raaAinimatedComponent;

typedef std::list<raaTrafficLightUnit*>raaLights;
typedef std::list<raaAinimatedComponent*>raaVehicles;

// a basic junction controller. This will manage the lights as a single junction. You should develop and extend this to manage a set of lights 
// as a single junction. 

class raaJunctionController: public osg::NodeCallback
{
public:
	raaJunctionController();
	virtual ~raaJunctionController();
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

	static void addVehicle(raaAinimatedComponent *pVehicle);
	void addLightUnit(raaTrafficLightUnit *pLight);



protected:
	static raaVehicles sm_lVehicles;
	raaLights m_lLights;
	osg::Group *g_pRoot;
};

