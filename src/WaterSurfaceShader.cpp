/* 
 * File:   WaterSurfaceShader.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:15 PM
 */

#include "OSGShaderFactory.h"
#include "TimeUniformCallback.h"

#include "WaterSurfaceShader.h"
#include "NoiseTexture3D.h"

#include <osgDB/ReadFile>

#include <sys/param.h>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


const unsigned int NumHeightMapLevels = 8;
const std::string VertexTextureLocation = "vertexTexture";
const std::string TimeLocation = "time";

WaterSurfaceShader::WaterSurfaceShader() 
{ 
    _vertexProgram   = readFile( "shader/watersurface.vs" );
    _fragmentProgram = readFile( "shader/watersurface.fs" );
    
    _shaderProgram = OSGShaderFactory::getInstance()->createShaderProgram( _vertexProgram, _fragmentProgram );    
}


WaterSurfaceShader::~WaterSurfaceShader() 
{
}


std::string WaterSurfaceShader::readFile( const char *filePath ) 
{
    std::string content;
    std::ifstream fileStream( filePath, std::ios::in );

    if( !fileStream.is_open() ) 
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while( !fileStream.eof() ) 
    {
        std::getline( fileStream, line );
        content.append( line + "\n" );
    }

    fileStream.close();
    return content;
}


void WaterSurfaceShader::linkStateSet( osg::ref_ptr< osg::StateSet > stateSet )
{           
    std::stringstream ss;
             
    // Vertex Textures
    for( unsigned int iLevel = 0; iLevel < NumHeightMapLevels; iLevel++ )
    {
        int level = (int)iLevel;
        
        ss << VertexTextureLocation << level;
        std::string vertexTextureLocation = ss.str();        
        ss.str( "" );
        
        int pixelSize = (int)pow( 2.0, (double)( level + 1 ) );    
                     
        stateSet->setTextureAttributeAndModes( level, new NoiseTexture3D( pixelSize ), osg::StateAttribute::ON );
        
        osg::Uniform* uniform = new osg::Uniform( vertexTextureLocation.c_str(), level );     
        stateSet->addUniform( uniform );        
    }
            
    // Time
    _timeUniform = new osg::Uniform( osg::Uniform::FLOAT, TimeLocation.c_str() );
    _timeUniform->set( 0.0f );
    _timeUniform->setUpdateCallback( new TimeUniformCallback() );
    stateSet->addUniform( _timeUniform );
        
    // Link
    stateSet->setAttributeAndModes( _shaderProgram, osg::StateAttribute::ON );    
}

