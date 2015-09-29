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
    
    osg::ref_ptr< osg::GraphicsContext > gc = viewer.getCamera()->getGraphicsContext();    
    osg::ref_ptr< osg::State > state = new osg::State;
    state->setCheckForGLErrors( osg::State::ONCE_PER_FRAME );
    gc->setState( state );
    
    osg::ref_ptr< osgGA::TrackballManipulator > manipulator = new osgGA::TrackballManipulator();
    viewer.setCameraManipulator( manipulator );
            
    //osg::ref_ptr< osg::PositionAttitudeTransform > terrainTransform = new osg::PositionAttitudeTransform();  
    
    osg::ref_ptr< WaterSurfaceNode > waterSurfaceNode = new WaterSurfaceNode( GridRadialSize, GridAngularSize );
        
    // Link
    //terrainTransform->addChild( waterSurfaceNode );
    //root->addChild( terrainTransform );    
    viewer.setSceneData( waterSurfaceNode ); 
    
    // Render
    viewer.realize();
    
    while( !viewer.done() ) 
    {
        viewer.frame(); 
    }
    
    return 0;
}

