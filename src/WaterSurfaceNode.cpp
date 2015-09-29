/* 
 * File:   WaterSurfaceNode.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 2:52 PM
 */


#include "WaterSurfaceNode.h"
#include "PolarGridGeometry.h"


WaterSurfaceNode::WaterSurfaceNode( unsigned int polarGridRadialSize, 
                                    unsigned int polarGridAngularSize )
{    
    osg::ref_ptr< PolarGridGeometry > polarGridGeometry = new PolarGridGeometry( polarGridRadialSize, polarGridAngularSize );
    polarGridGeometry->linkShader();
    
    _geode = new osg::Geode();    
    _geode->addDrawable( polarGridGeometry );
    _geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
        
    addChild( _geode );
}


WaterSurfaceNode::~WaterSurfaceNode() 
{
}

