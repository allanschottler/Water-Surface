/* 
 * File:   OceanFloorShader.h
 * Author: allan
 *
 * Created on October 9, 2015, 6:13 PM
 */

#ifndef OCEANFLOORSHADER_H
#define	OCEANFLOORSHADER_H

#include <osg/StateSet>
#include <osg/Program>
#include <osg/Uniform>
#include <osg/Texture2D>


class OceanFloorShader 
{
public:
    
    OceanFloorShader();
    
    virtual ~OceanFloorShader();
    
    void linkStateSet( osg::ref_ptr< osg::StateSet > stateSet );
    
private:
    
    static std::string readFile( const char *filePath );
    
    
    std::string _vertexProgram;

    std::string _fragmentProgram;
        
    osg::ref_ptr< osg::Program > _shaderProgram;
    
    osg::ref_ptr< osg::Texture2D > _oceanFloorTexture;

};

#endif	/* OCEANFLOORSHADER_H */

