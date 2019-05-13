#include "stdafx.h"
#include "raaInputController.h"
#include "raaTile.h"
#include "raaTrafficLightUnit.h"


bool raaInputController::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
{
	if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{
		switch(ea.getKey())
		{
			case 'a':
			case 'A':
				raaTile::toggleAnimPoints();
				return true;
			case '+':
				raaTile::toggleAnimPoints();
				return true;
		}
	}

	return false;
}

raaInputController::raaInputController()
{
}


raaInputController::~raaInputController()
{
}
