/* 
 * File:   WaterSurfaceShader.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:15 PM
 */

#include "OSGShaderFactory.h"
#include "TimeUniformCallback.h"

#include "WaterSurfaceShader.h"

#include <osgDB/ReadFile>
#include <osg/Image>
#include <osg/Texture2D>

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
    _vertexProgram   = readFile( "shader/vertexdisplacement.vs" );
    _fragmentProgram = readFile( "shader/vertexdisplacement.fs" );
    
    _shaderProgram = OSGShaderFactory::getInstance()->createShaderProgram( _vertexProgram, _fragmentProgram );
    
    // Vertex textures   
    //_vertexTextures.push_back( noiseTexture );
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


osg::ref_ptr< osg::Texture2D > build2DTexture( unsigned int pixelSize )
{
    osg::ref_ptr< osg::Image > image = osgDB::readImageFile( "/home/v/allanws/Desktop/skylightgray.png" );
    image->scaleImage( pixelSize, pixelSize, 1 );
        
    osg::ref_ptr< osg::Texture2D > texture = new osg::Texture2D;
    
    texture->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
    texture->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
    
    texture->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::MIRROR );
    texture->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::MIRROR );   
    
    //texture->setDataVariance( osg::Object::DYNAMIC );
    texture->setImage( image );
    
    return texture;
}


osg::ref_ptr< osg::Texture2D > build2DNoiseTexture( unsigned int pixelSize )
{
    osg::ref_ptr< osg::Image > image = new osg::Image;
    image->allocateImage( pixelSize, pixelSize, 1, GL_RGBA, GL_FLOAT );
        
    const long size = pixelSize * pixelSize * 4;

    float* data = reinterpret_cast< float* >( image->data() ); 
   
    srand( static_cast< unsigned >( time( 0 ) ) );
    
    for( long i = 0; i < size; i+=4 )
    {
        float val = static_cast< float >( rand() ) / static_cast< float >( RAND_MAX );
        data[ i+0 ] = val;
        data[ i+1 ] = val;
        data[ i+2 ] = val;
        data[ i+3 ] = 1.0f;
    }
        
    osg::ref_ptr< osg::Texture2D > texture = new osg::Texture2D( image );
    
    texture->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
    texture->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
    
    texture->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::MIRROR );
    texture->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::MIRROR );   
    
    //texture->setDataVariance( osg::Object::DYNAMIC );
    texture->setImage( image );
    
    return texture;
}


osg::ref_ptr< osg::Texture3D > WaterSurfaceShader::buildNoiseTexture( unsigned int pixelSize )
{
    osg::ref_ptr< osg::Image > image = new osg::Image();    
    image->allocateImage( pixelSize, pixelSize, pixelSize, GL_RGBA, GL_FLOAT );
        
    const long size = pixelSize * pixelSize * pixelSize * 4;

    float* data = reinterpret_cast< float* >( image->data() ); 
   
    srand( static_cast< unsigned >( time( 0 ) ) );
    
    for( long i = 0; i < size; i+=4 )
    {
        float val = static_cast< float >( rand() ) / static_cast< float >( RAND_MAX );
        data[ i+0 ] = val;
        data[ i+1 ] = 0.0f;
        data[ i+2 ] = 0.0f;
        data[ i+3 ] = 1.0f;
    }
    
    
        
    /*for( unsigned int i = 0; i < pixelSize; i++ )
    {
        for( unsigned int j = 0; j < pixelSize; j++ )
        {
            for( unsigned int k = 0; k < pixelSize; k++ )
            {
                float val = static_cast< float >( rand() ) / static_cast< float >( RAND_MAX );
                image->data( k, j, i )[ 0 ] = val;
                image->data( k, j, i )[ 1 ] = val;
                image->data( k, j, i )[ 2 ] = val;
            }
        }
    }*/
        
    /*osg::ref_ptr< osg::Image > image = osgDB::readImageFile( "/home/v/allanws/Desktop/skylightgray.png" );
    image->scaleImage( pixelSize, pixelSize, 1 );
    
    osg::ref_ptr< osg::Image > image3d = new osg::Image;
    image3d->allocateImage( pixelSize, pixelSize, 1, image->getPixelFormat(), image->getDataType() );
    image3d->copySubImage( 0, 0, 0, image );
    //image3d->copySubImage( 0, 0, 1, image );
    image3d->setInternalTextureFormat( image->getInternalTextureFormat() );*/
    
    osg::ref_ptr< osg::Texture3D > texture = new osg::Texture3D( image );
    
    texture->setFilter( osg::Texture3D::MIN_FILTER, osg::Texture3D::LINEAR );
    texture->setFilter( osg::Texture3D::MAG_FILTER, osg::Texture3D::LINEAR );
    
    texture->setWrap( osg::Texture3D::WRAP_S, osg::Texture3D::MIRROR );
    texture->setWrap( osg::Texture3D::WRAP_T, osg::Texture3D::MIRROR );
    texture->setWrap( osg::Texture3D::WRAP_R, osg::Texture3D::MIRROR );    
    
    return texture;
}


void WaterSurfaceShader::linkStateSet( osg::ref_ptr< osg::StateSet > stateSet )
{           
    /*std::stringstream ss;
             
    for( unsigned int iLevel = 0; iLevel < NumHeightMapLevels; iLevel++ )
    {
        int level = (int)iLevel;
        
        ss << VertexTextureLocation << level;
        std::string vertexTextureLocation = ss.str();        
        ss.str( "" );
        
        int pixelSize = (int)pow( 2.0, (double)( level + 1 ) );    
              
        osg::ref_ptr< osg::Texture3D > noiseTexture = buildNoiseTexture( pixelSize );        
        stateSet->setTextureAttributeAndModes( level, noiseTexture, osg::StateAttribute::ON );
        
        uniform = new osg::Uniform( osg::Uniform::SAMPLER_3D, vertexTextureLocation.c_str() );                    
        uniform->set( level );
        stateSet->addUniform( uniform );        
    }*/
            
    // Time
    _timeUniform = new osg::Uniform( osg::Uniform::FLOAT, TimeLocation.c_str() );
    _timeUniform->set( 0.0f );
    _timeUniform->setUpdateCallback( new TimeUniformCallback() );
    stateSet->addUniform( _timeUniform );
            
    //_noiseTexture = buildNoiseTexture( 4 ); 
    
    //stateSet->setTextureAttributeAndModes( 0, _noiseTexture, osg::StateAttribute::ON );
    stateSet->setTextureAttributeAndModes( 0, buildNoiseTexture( 4 ), osg::StateAttribute::ON );
        
    osg::ref_ptr< osg::Uniform > uniform = new osg::Uniform( "vertexTexture0", 0 );
    stateSet->addUniform( uniform ); 
        
    // Link
    stateSet->setAttributeAndModes( _shaderProgram, osg::StateAttribute::ON );    
}


void WaterSurfaceShader::loadVariables()
{
}

