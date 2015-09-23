/* 
 * File:   WaterSurfaceShader.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:15 PM
 */

#ifndef WATERSURFACESHADER_H
#define	WATERSURFACESHADER_H

#include <osg/StateSet>
#include <osg/Texture3D>
#include <osg/Program>
#include <osg/Uniform>


class WaterSurfaceShader 
{
public:
    
    WaterSurfaceShader();
        
    virtual ~WaterSurfaceShader();
    
    void linkStateSet( osg::ref_ptr<osg::StateSet> stateSet );        

    void loadVariables();
    
    void setVertexTextures( std::vector< osg::ref_ptr< osg::Texture3D > > vertexTextures3D );
    
private:    
    
    static const char* _vertexProgram;

    static const char* _fragmentProgram;
        
    osg::ref_ptr< osg::Program > _shaderProgram;

    osg::ref_ptr< osg::Uniform > _vertexTexturesUniform;
    
    std::vector< osg::ref_ptr< osg::Texture3D > > _vertexTextures3D;
};

#endif	/* WATERSURFACESHADER_H */

