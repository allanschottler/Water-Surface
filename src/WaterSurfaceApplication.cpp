/* 
 * File:   WaterSurfaceApplication.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 2:25 PM
 */

#include "WaterSurfaceApplication.h"

#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>


WaterSurfaceApplication::WaterSurfaceApplication() 
{
}


WaterSurfaceApplication::~WaterSurfaceApplication() 
{
}


int WaterSurfaceApplication::run()
{
    osgViewer::Viewer viewer;    
    viewer.setUpViewInWindow( 0, 0, 800, 800 );
    
    osg::ref_ptr< osg::Group > root = new osg::Group;

    osg::ref_ptr< osg::PositionAttitudeTransform > terrainTransform = new osg::PositionAttitudeTransform();


    root->addChild( terrainTransform );
    
    viewer.setSceneData( root.get() ); 
    
    viewer.realize();
    
    while( !viewer.done() ) 
    {
        viewer.frame(); 
    }
    
    return 0;
}

