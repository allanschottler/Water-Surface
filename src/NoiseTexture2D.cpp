/* 
 * File:   NoiseTexture2D.cpp
 * Author: allan
 * 
 * Created on October 9, 2015, 5:58 PM
 */

#include "NoiseTexture2D.h"

#include <stdlib.h>
#include <time.h>

NoiseTexture2D::NoiseTexture2D( unsigned int pixelSize ) 
{
    _pixelSize = pixelSize;
    _image = new osg::Image();
        
    buildImage();
    
    setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
    setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
    
    setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::MIRROR );
    setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::MIRROR ); 
    
    setBorderWidth( 0 );
    
    setInternalFormat( GL_LUMINANCE32F_ARB );
}


NoiseTexture2D::~NoiseTexture2D() 
{
}


void NoiseTexture2D::buildImage()
{
    _image->allocateImage( _pixelSize, _pixelSize, 1, GL_RGBA, GL_FLOAT );
        
    const long size = _pixelSize * _pixelSize * 4;

    float* data = reinterpret_cast< float* >( _image->data() ); 
   
    srand( static_cast< unsigned >( time( 0 ) ) );
    
    for( long i = 0; i < size; i+=4 )
    {
        float val = static_cast< float >( rand() ) / static_cast< float >( RAND_MAX );
        data[ i+0 ] = val;
        data[ i+1 ] = 0.0f;
        data[ i+2 ] = 0.0f;
        data[ i+3 ] = 1.0f;
    }
    
    setImage( _image );
}

