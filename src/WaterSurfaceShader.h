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


class WaterSurfaceShader
{
public:
    
    WaterSurfaceShader();
        
    virtual ~WaterSurfaceShader();    
    
    void linkStateSet( osg::ref_ptr<osg::StateSet> stateSet );    
    
private:    
        
    static std::string readFile( const char *filePath );
    
    
    std::string _vertexProgram;

    std::string _fragmentProgram;
        
    osg::ref_ptr< osg::Program > _shaderProgram;

    osg::ref_ptr< osg::Uniform > _timeUniform;
     
};

#endif	/* WATERSURFACESHADER_H */

