#include "stdafx.h"

#include "raaTrafficLightUnit.h"
#include "raaAinimatedComponent.h"

#include "raaJunctionController.h"
#include <iostream>

raaVehicles raaJunctionController::sm_lVehicles;
//extern osg::Group *g_pRoot;
int count;

raaJunctionController::raaJunctionController()
{
}

raaJunctionController::~raaJunctionController()
{
}

void raaJunctionController::addVehicle(raaAinimatedComponent* pVehicle)
{
	if (pVehicle && std::find(sm_lVehicles.begin(), sm_lVehicles.end(), pVehicle) == sm_lVehicles.end())
		sm_lVehicles.push_back(pVehicle);
}


void raaJunctionController::addLightUnit(raaTrafficLightUnit* pLight)
{
	if (pLight && std::find(m_lLights.begin(), m_lLights.end(), pLight) == m_lLights.end())
	{
		m_lLights.push_back(pLight);
	}
}


void raaJunctionController::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	count++;
	raaLights::iterator itLights = m_lLights.begin();
	raaVehicles::iterator itVehicles = sm_lVehicles.begin();

	//Loop through all the traffic lights
	for (; itLights != m_lLights.end(); itLights++) {
		switch (count)
		{
		case 25:
			(*itLights)->setRed();
			break;
		case 75:
			(*itLights)->setAmber();
			break;
		case 125:
			(*itLights)->setGreen();
			break;
		case 175:
			(*itLights)->setAmber();
			count = 0;
			break;
		}

		for (; itVehicles != sm_lVehicles.end(); itVehicles++)
		{
			osg::Matrixf mCarToWorld = osg::computeLocalToWorld((*itVehicles)->root()->getParentalNodePaths(g_pRoot)[0]);
			osg::Vec3f vPos(0.0f, 0.0f, 0.0f);
			vPos = vPos * mCarToWorld;

			if ((*itLights)->testDetection(g_pRoot, vPos)) {
				if ((*itLights)->state == 1) {
					(*itVehicles)->setPause(true);
				}
				else {
					(*itVehicles)->setPause(false);
				}
			}
		}
	}
	traverse(node, nv);
}