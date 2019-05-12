#include "stdafx.h"
#include <windows.H>
#include <osgDB/ReadFile>
#include "raaTrafficLightUnit.h"
#include "raaFinder.h"
#include "raaPrinter.h"
#include <osg/PolygonMode>
#include <osg/ShapeDrawable>
#include <osg/Switch>

osg::Node* raaTrafficLightUnit::sm_pAsset = 0;
osg::Material* raaTrafficLightUnit::sm_pRedOn = 0;
osg::Material* raaTrafficLightUnit::sm_pRedOff = 0;
osg::Material* raaTrafficLightUnit::sm_pAmberOn = 0;
osg::Material* raaTrafficLightUnit::sm_pAmberOff = 0;
osg::Material* raaTrafficLightUnit::sm_pGreenOn = 0;
osg::Material* raaTrafficLightUnit::sm_pGreenOff = 0;

raaTrafficLights raaTrafficLightUnit::sm_lLights;

raaTrafficLightUnit::raaTrafficLightUnit()
{
	sm_lLights.push_back(this);
	m_pTraslation = new osg::MatrixTransform();
	m_pTraslation->ref();
	m_pRotation = new osg::MatrixTransform();
	m_pScale = new osg::MatrixTransform();

	m_pTraslation->addChild(m_pRotation);
	m_pRotation->addChild(m_pScale);

	m_pScale->addChild((osg::Node*) sm_pAsset->clone(osg::CopyOp::DEEP_COPY_NODES));

	raaFinder<osg::Geode> redFinder("trafficLight::RedLamp-GEODE", m_pRotation);
	raaFinder<osg::Geode> greenFinder("trafficLight::GreenLamp-GEODE", m_pRotation);
	raaFinder<osg::Geode> amberFinder("trafficLight::AmberLamp-GEODE", m_pRotation);

	m_pBoxMT = new osg::MatrixTransform();
	m_pBoxTranslateMT = new osg::MatrixTransform();
	osg::Matrixf translate = m_pBoxTranslateMT->getMatrix();
	translate.makeTranslate(160.0f, -100.0f, 0.0f);
	m_pBoxTranslateMT->setMatrix(translate);
	m_pBoxTranslateMT->ref();
	//m_pBoxMT->setUpdateCallback(this);
	osg::Geode *pBoxGeode = new osg::Geode();
	osg::ShapeDrawable *pBoxSD = new osg::ShapeDrawable(new osg::Box(osg::Vec3f(-30.0f, -30.0f, 30.0f), 60.0f));

	m_pBoxMT->addChild(m_pBoxTranslateMT);
	m_pBoxTranslateMT->addChild(pBoxGeode);
	pBoxGeode->addDrawable(pBoxSD);

	pBoxGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pBoxMT->getOrCreateStateSet()->setAttributeAndModes(sm_pRedOn, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	m_pRotation->addChild(m_pBoxMT);
	m_pRed = redFinder.node();
	m_pGreen = greenFinder.node();
	m_pAmber = amberFinder.node();

	setRed();
}

void raaTrafficLightUnit::setGreen()
{
	m_pRed->getOrCreateStateSet()->setAttributeAndModes(sm_pRedOff, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pGreen->getOrCreateStateSet()->setAttributeAndModes(sm_pGreenOn, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pAmber->getOrCreateStateSet()->setAttributeAndModes(sm_pAmberOff, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	state = 3;
}

void raaTrafficLightUnit::setAmber() {
	m_pRed->getOrCreateStateSet()->setAttributeAndModes(sm_pRedOff, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pGreen->getOrCreateStateSet()->setAttributeAndModes(sm_pGreenOff, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pAmber->getOrCreateStateSet()->setAttributeAndModes(sm_pAmberOn, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	state = 2;
}

void raaTrafficLightUnit::setRed() {
	m_pRed->getOrCreateStateSet()->setAttributeAndModes(sm_pRedOn, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pGreen->getOrCreateStateSet()->setAttributeAndModes(sm_pGreenOff, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	m_pAmber->getOrCreateStateSet()->setAttributeAndModes(sm_pAmberOff, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	state = 1;
}

osg::MatrixTransform* raaTrafficLightUnit::getBox() {
	return m_pBoxMT;
}

osg::MatrixTransform* raaTrafficLightUnit::getLight() {
	return m_pTraslation;
}

bool raaTrafficLightUnit::testDetection(osg::Group *pWorldRoot, osg::Vec3f vPos) {
	bool detection = false;
	osg::Matrixf mWorldToZone = osg::computeWorldToLocal(m_pBoxMT->getParentalNodePaths(pWorldRoot)[0]);
	osg::BoundingSphere b = m_pBoxMT->getBound();
	vPos = vPos * mWorldToZone;
	
	if (b.contains(vPos)) {
		m_pBoxMT->getOrCreateStateSet()->setAttributeAndModes(sm_pGreenOn, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		detection = true;
	}
	else {
		m_pBoxMT->getOrCreateStateSet()->setAttributeAndModes(sm_pRedOn, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	}
	return detection;
}

void raaTrafficLightUnit::initAsset(std::string sFile)
{
	if (!sm_pAsset)
	{
		sm_pAsset = osgDB::readNodeFile(sFile);
		sm_pAsset->ref();

		sm_pRedOn = new osg::Material();
		sm_pRedOn->ref();
		sm_pRedOff = new osg::Material();
		sm_pRedOff->ref();
		materialBuilder(sm_pRedOn, sm_pRedOff, osg::Vec3f(1.0f, 0.0f, 0.0f));

		sm_pGreenOn = new osg::Material();
		sm_pGreenOn->ref();
		sm_pGreenOff = new osg::Material();
		sm_pGreenOff->ref();
		materialBuilder(sm_pGreenOn, sm_pGreenOff, osg::Vec3f(0.0f, 1.0f, 0.0f));

		sm_pAmberOn = new osg::Material();
		sm_pAmberOn->ref();
		sm_pAmberOff = new osg::Material();
		sm_pAmberOff->ref();
		materialBuilder(sm_pAmberOn, sm_pAmberOff, osg::Vec3f(1.0f, 0.5f, 0.0f));
	}
}

void raaTrafficLightUnit::finshAsset()
{
	if (sm_pAsset)
	{
		sm_pAsset->unref();
		sm_pAsset = 0;

		sm_pRedOn->unref();
		sm_pRedOff->unref();
		sm_pGreenOn->unref();
		sm_pGreenOff->unref();
		sm_pAmberOn->unref();
		sm_pAmberOff->unref();
	}
}


void raaTrafficLightUnit::setTransform(float fX, float fY, float fRot, float fScale)
{
	if (m_pTraslation)
	{
		osg::Matrixf mT, mR, mS;

		mT.makeTranslate(osg::Vec3f(fX, fY, 0.0f));
		mR.makeRotate(osg::DegreesToRadians(fRot), osg::Vec3f(0.0f, 0.0f, 1.0f));
		mS.makeScale(osg::Vec3f(fScale, fScale, fScale));

		m_pTraslation->setMatrix(mT);
		m_pRotation->setMatrix(mR);
		m_pScale->setMatrix(mS);
	}
}

osg::Node* raaTrafficLightUnit::node()
{
	return m_pTraslation;
}

void raaTrafficLightUnit::materialBuilder(osg::Material* pOn, osg::Material* pOff, osg::Vec3f vMat)
{
	pOn->setAmbient(osg::Material::FRONT, osg::Vec4f(vMat[0] * 0.2f, vMat[1] * 0.2f, vMat[2] * 0.2f, 1.0f));
	pOn->setDiffuse(osg::Material::FRONT, osg::Vec4f(vMat[0], vMat[1], vMat[2], 1.0f));
	pOn->setSpecular(osg::Material::FRONT, osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	pOn->setShininess(osg::Material::FRONT, 200.0f);

	pOff->setAmbient(osg::Material::FRONT, osg::Vec4f(vMat[0] * 0.1f, vMat[1] * 0.1f, vMat[2] * 0.1f, 1.0f));
	pOff->setDiffuse(osg::Material::FRONT, osg::Vec4f(vMat[0] * 0.3f, vMat[1] * 0.3f, vMat[2] * 0.3f, 1.0f));
	pOff->setSpecular(osg::Material::FRONT, osg::Vec4f(0.3f, 0.3f, 0.3f, 1.0f));
	pOff->setShininess(osg::Material::FRONT, 10.0f);
}

raaTrafficLightUnit::~raaTrafficLightUnit()
{
	if (m_pTraslation) m_pTraslation->unref();
	sm_lLights.remove(this);
}
