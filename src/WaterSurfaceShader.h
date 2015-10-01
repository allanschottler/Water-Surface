/* 
 * File:   WaterSurfaceShader.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:15 PM
 */

#ifndef WATERSURFACESHADER_H
#define	WATERSURFACESHADER_H

#include <osg/StateSet>
#include <osg/Program>
#include <osg/Uniform>
#include <osg/NodeVisitor>
#include <osg/Texture3D>


class WaterSurfaceShader
{
public:
    
    WaterSurfaceShader();
        
    virtual ~WaterSurfaceShader();    
    
    void linkStateSet( osg::ref_ptr<osg::StateSet> stateSet );    

    void loadVariables();
    
private:    
        
    static std::string readFile( const char *filePath );
    
    
    std::string _vertexProgram;

    std::string _fragmentProgram;
        
    osg::ref_ptr< osg::Program > _shaderProgram;

    osg::ref_ptr< osg::Uniform > _timeUniform;
     
};

#endif	/* WATERSURFACESHADER_H */

