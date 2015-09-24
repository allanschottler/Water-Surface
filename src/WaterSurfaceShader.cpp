/* 
 * File:   WaterSurfaceShader.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:15 PM
 */

#include "WaterSurfaceShader.h"
#include "OSGShaderFactory.h"

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
    std::stringstream ss;
    
    for( unsigned int iUniform = 0; iUniform < NumHeightMapLevels; iUniform++ )
    {
        ss << VertexTextureLocation << iUniform;
        const char * vertexTextureLocation = ss.str().c_str();
        ss.str( "" );
        
        osg::ref_ptr< osg::Uniform > uniform = new osg::Uniform( osg::Uniform::SAMPLER_3D, vertexTextureLocation );
        uniform->set( (int)iUniform );
        
        _vertexTexturesUniforms.push_back( uniform );        
    }
    
    _timeUniform = new osg::Uniform( osg::Uniform::FLOAT, TimeLocation.c_str() );
    _timeUniform->set( 0.0f );
    _timeUniform->setUpdateCallback( this );
    
    _vertexProgram   = readFile( "shader/vertexdisplacement.vs" );
    _fragmentProgram = readFile( "shader/vertexdisplacement.fs" );
    
    _shaderProgram = OSGShaderFactory::getInstance()->createShaderProgram( _vertexProgram, _fragmentProgram );
}


WaterSurfaceShader::~WaterSurfaceShader() 
{
}


std::string WaterSurfaceShader::readFile( const char *filePath ) 
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

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


void WaterSurfaceShader::linkStateSet( osg::ref_ptr<osg::StateSet> stateSet )
{
    std::vector< osg::ref_ptr< osg::Uniform > >::iterator it;
    
    for( it = _vertexTexturesUniforms.begin(); it != _vertexTexturesUniforms.end(); ++it )
        stateSet->addUniform( *it );
    
    stateSet->setAttributeAndModes( _shaderProgram, osg::StateAttribute::ON );
}


void WaterSurfaceShader::loadVariables()
{
    
}

