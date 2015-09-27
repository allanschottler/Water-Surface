/* 
 * File:   WaterSurfaceNode.h
 * Author: allanws
 *
 * Created on September 23, 2015, 2:52 PM
 */

#ifndef WATERSURFACENODE_H
#define	WATERSURFACENODE_H

#include <osg/Node>
#include <osg/Geode>
#include <osg/Texture3D>
#include <vector>


class WaterSurfaceNode : public osg::Group
{
public:
    
    WaterSurfaceNode( unsigned int polarGridRadialSize, 
                      unsigned int polarGridAngularSize );
    
    virtual ~WaterSurfaceNode();
        
private:
               
    osg::ref_ptr< osg::Geode > _geode;        

};

#endif	/* WATERSURFACENODE_H */

