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

#include "WaterSurfaceShader.h"


class WaterSurfaceNode : public osg::Node
{
public:
    
    WaterSurfaceNode( unsigned int heightMapLevels, 
                      unsigned int polarGridRadialSize, 
                      unsigned int polarGridAngularSize );
    
    virtual ~WaterSurfaceNode();
    
private:
        
    void buildVertexTextures();
    
    
    unsigned int _heightMapLevels;
    
    osg::ref_ptr< osg::Geode > _geode;
        
    WaterSurfaceShader _shader;

};

#endif	/* WATERSURFACENODE_H */

