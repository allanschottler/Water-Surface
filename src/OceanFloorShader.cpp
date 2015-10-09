/* 
 * File:   OceanFloorShader.cpp
 * Author: allan
 * 
 * Created on October 9, 2015, 6:13 PM
 */

#include "OSGShaderFactory.h"

#include "OceanFloorShader.h"
#include "NoiseTexture2D.h"

#include <osgDB/ReadFile>

#include <sys/param.h>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


const unsigned int NumHeightMapLevels = 3;
const std::string VertexTextureLocation = "vertexTexture";
const std::string OceanFloorTextureLocation = "oceanFloorTexture";

OceanFloorShader::OceanFloorShader()
{
    _vertexProgram   = readFile( "shader/oceanfloor.vs" );
    _fragmentProgram = readFile( "shader/oceanfloor.fs" );
    
    osg::ref_ptr< osg::Image > oceanFloorImage = osgDB::readImageFile( "data/oceanfloor.png" );
    
    if( oceanFloorImage )
    {
        _oceanFloorTexture = new osg::Texture2D( oceanFloorImage );
        
        _oceanFloorTexture->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
        _oceanFloorTexture->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
    
        _oceanFloorTexture->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT );
        _oceanFloorTexture->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT );   
    
        _oceanFloorTexture->setBorderWidth( 0 );
    }
    
    _shaderProgram = OSGShaderFactory::getInstance()->createShaderProgram( _vertexProgram, _fragmentProgram );    
}


std::string OceanFloorShader::readFile( const char *filePath ) 
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


OceanFloorShader::~OceanFloorShader()
{
}


void OceanFloorShader::linkStateSet( osg::ref_ptr< osg::StateSet > stateSet )
{
    std::stringstream ss;
    int uniqueTextureID = 0;
    
    // Vertex Textures
    for( unsigned int iLevel = 0; iLevel < NumHeightMapLevels; iLevel++ )
    {
        int level = (int)iLevel;
        
        ss << VertexTextureLocation << level;
        std::string vertexTextureLocation = ss.str();        
        ss.str( "" );
        
        int pixelSize = (int)pow( 2.0, (double)( level + 1 ) );    
                     
        stateSet->setTextureAttributeAndModes( uniqueTextureID, new NoiseTexture2D( pixelSize ), osg::StateAttribute::ON );
        
        osg::Uniform* uniform = new osg::Uniform( vertexTextureLocation.c_str(), uniqueTextureID );     
        stateSet->addUniform( uniform );     
        
        uniqueTextureID++;
    }
    
    // ocean floor texture
    stateSet->setTextureAttributeAndModes( uniqueTextureID, _oceanFloorTexture, osg::StateAttribute::ON );

    osg::Uniform* uniform = new osg::Uniform( OceanFloorTextureLocation.c_str(), uniqueTextureID );     
    stateSet->addUniform( uniform );
        
    // Link
    stateSet->setAttributeAndModes( _shaderProgram, osg::StateAttribute::ON );    
}