#include "stdafx.h"

#include <windows.h>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osgDB/ReadFile>
#include "raaAinimatedComponent.h"
#include <osg/PolygonMode>


raaAinimatedComponent::raaAinimatedComponent(osg::AnimationPath *pAP) : osg::AnimationPathCallback(pAP)
{
	m_pRoot = new osg::MatrixTransform();
	osg::MatrixTransform *pRotation = new osg::MatrixTransform();

	osg::Matrixf rotation = pRotation->getMatrix();
	rotation = rotation.rotate(osg::Quat(osg::DegreesToRadians(90.0f), osg::Vec3f(0.0f, 0.0f, 1.0f)));
	pRotation->setMatrix(rotation);
	m_pRoot->addChild(pRotation);
	m_pRoot->ref();

	osg::Geode*pGeode = new osg::Geode();
	osg::ShapeDrawable* pSD = new osg::ShapeDrawable(new osg::Box(osg::Vec3f(0.0f, 0.0f, 20.0f), 80.0f, 60.0f, 40.0f));

	pRotation->addChild(osgDB::readNodeFile("../../Data/car-delta.OSGB"));

	osg::Material *pMat = new osg::Material();
	pMat->setAmbient(osg::Material::FRONT, osg::Vec4f(0.2f, 0.2f, 0.0f, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT, osg::Vec4f(0.8f, 0.8f, 0.0f, 1.0f));
	pMat->setSpecular(osg::Material::FRONT, osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	pMat->setShininess(osg::Material::FRONT, 100.0f);

	pGeode->getOrCreateStateSet()->setAttributeAndModes(pMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	pGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	pSD->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::Material::ON | osg::Material::OVERRIDE);
	pGeode->addDrawable(pSD);
	m_pRoot->addChild(pGeode);

	m_pRoot->setUpdateCallback(this);
}

raaAinimatedComponent::~raaAinimatedComponent()
{
	m_pRoot->unref();
}

osg::MatrixTransform* raaAinimatedComponent::root()
{
	return m_pRoot;
}