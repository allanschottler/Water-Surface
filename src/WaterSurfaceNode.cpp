/* 
 * File:   WaterSurfaceNode.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 2:52 PM
 */


#include "WaterSurfaceNode.h"
#include "PolarGridGeometry.h"

#include <osg/BlendFunc>

WaterSurfaceNode::WaterSurfaceNode( unsigned int polarGridRadialSize, 
                                    unsigned int polarGridAngularSize )
{        
    const osg::BoundingBox bb( osg::Vec3( -100.0f, -100.0f, -100.0f ), osg::Vec3( 100.0f, 100.0f, 100.0f ) );
    
    _waterSurfaceGeometry = new PolarGridGeometry( polarGridRadialSize, polarGridAngularSize );
    _waterSurfaceGeometry->setInitialBound( bb );
    _waterSurfaceShader.linkStateSet( _waterSurfaceGeometry->getOrCreateStateSet() );  
    
    _waterSurfaceGeometry->getOrCreateStateSet()->setRenderBinDetails( 1, "transparent" );
    _waterSurfaceGeometry->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    
    _oceanFloorGeometry = new PolarGridGeometry( polarGridRadialSize, polarGridAngularSize );
    _oceanFloorGeometry->setInitialBound( bb );
    _oceanFloorShader.linkStateSet( _oceanFloorGeometry->getOrCreateStateSet() );
    
    osg::ref_ptr< osg::BlendFunc > bf = new osg::BlendFunc;
    bf->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    _geode = new osg::Geode();    
    _geode->addDrawable( _waterSurfaceGeometry );
    _geode->addDrawable( _oceanFloorGeometry );
    _geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    _geode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    _geode->getOrCreateStateSet()->setAttributeAndModes( bf ); 
        
    addChild( _geode );
}


WaterSurfaceNode::~WaterSurfaceNode() 
{
}

