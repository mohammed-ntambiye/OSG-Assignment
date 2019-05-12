#include "stdafx.h"
#include "mnVehicle.h"
#include <osgDB/ReadFile>
#include <osg/Geode>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/PolygonMode>
#include <osg/Light>
#include <osg/LightSource>

mnVehicle::mnVehicle(osg::AnimationPath * pAP) : raaAinimatedComponent(pAP)
{
	std::string sFile = "../../Data/car-veyron.OSGB";

	osg::Geode*pGeode = new osg::Geode();
	osg::ShapeDrawable* pSD = new osg::ShapeDrawable(new osg::Box(osg::Vec3f(0.0f, 0.0f, 20.0f), 60.0f, 60.0f, 40.0f)); // add osg::Switch to toggle this

	osg::Material *pMat = new osg::Material();
	pMat->setAmbient(osg::Material::FRONT, osg::Vec4f(0.2f, 0.2f, 0.0f, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT, osg::Vec4f(0.8f, 0.8f, 0.0f, 1.0f));
	pMat->setSpecular(osg::Material::FRONT, osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	pMat->setShininess(osg::Material::FRONT, 100.0f);

	pGeode->getOrCreateStateSet()->setAttributeAndModes(pMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	pGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	pSD->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::Material::ON | osg::Material::OVERRIDE);
	pGeode->addDrawable(pSD);
	m_pRotation->addChild(pGeode);

	// Vehicle model asset
	osg::Node* pAsset = osgDB::readNodeFile(sFile);
	pAsset->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::Material::ON | osg::Material::OVERRIDE);
	osg::Matrixf mT;
	mT.makeTranslate(osg::Vec3f(0.0f, 0.0f, 2.8f));
	osg::MatrixTransform* pModelTranslation = new osg::MatrixTransform();
	pModelTranslation->setMatrix(mT);
	pModelTranslation->addChild((osg::Node*) pAsset->clone(osg::CopyOp::DEEP_COPY_NODES));
	m_pScale->addChild(pModelTranslation);
}

mnVehicle::~mnVehicle()
{
}

void mnVehicle::operator()(osg::Node * node, osg::NodeVisitor * nv)
{
	raaAinimatedComponent::operator()(node, nv);
}
