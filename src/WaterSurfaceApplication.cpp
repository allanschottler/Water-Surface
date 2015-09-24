/* 
 * File:   WaterSurfaceApplication.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 2:25 PM
 */

#include "WaterSurfaceApplication.h"
#include "WaterSurfaceNode.h"

#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/SmoothingVisitor>
#include <osgGA/TrackballManipulator>


const int WindowWidth       = 800;
const int WindowHeight      = 800;
const int NumHeightMaps     = 8;
const int GridRadialSize    = 100;
const int GridAngularSize   = 100;

WaterSurfaceApplication::WaterSurfaceApplication() 
{
}


WaterSurfaceApplication::~WaterSurfaceApplication() 
{
}


int WaterSurfaceApplication::run()
{    
    // Build    
    osgViewer::Viewer viewer;    
    viewer.setUpViewInWindow( 0, 0, WindowWidth, WindowHeight );    
    
    osg::ref_ptr< osgGA::TrackballManipulator > manipulator = new osgGA::TrackballManipulator();
    viewer.setCameraManipulator( manipulator );
    
    osg::ref_ptr< osg::Group > root = new osg::Group;
    
    osg::ref_ptr< osg::PositionAttitudeTransform > terrainTransform = new osg::PositionAttitudeTransform();  
    
    osg::ref_ptr< WaterSurfaceNode > waterSurfaceNode = new WaterSurfaceNode( NumHeightMaps, GridRadialSize, GridAngularSize );
    
    osgUtil::SmoothingVisitor smoothingVisitor;
    
    // Link
    waterSurfaceNode->accept( smoothingVisitor );    
    terrainTransform->addChild( waterSurfaceNode );
    root->addChild( terrainTransform );    
    viewer.setSceneData( root.get() ); 
    
    // Render
    viewer.realize();
    
    while( !viewer.done() ) 
    {
        viewer.frame(); 
    }
    
    return 0;
}

