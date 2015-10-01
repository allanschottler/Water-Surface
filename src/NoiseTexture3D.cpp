/* 
 * File:   NoiseTexture3D.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:44 PM
 */

#include "NoiseTexture3D.h"

#include <stdlib.h>
#include <time.h>

NoiseTexture3D::NoiseTexture3D( unsigned int pixelSize ) 
{
    _pixelSize = pixelSize;
    _image = new osg::Image();
        
    buildImage();
    
    setFilter( osg::Texture3D::MIN_FILTER, osg::Texture3D::LINEAR );
    setFilter( osg::Texture3D::MAG_FILTER, osg::Texture3D::LINEAR );
    
    setWrap( osg::Texture3D::WRAP_S, osg::Texture3D::MIRROR );
    setWrap( osg::Texture3D::WRAP_T, osg::Texture3D::MIRROR );
    setWrap( osg::Texture3D::WRAP_R, osg::Texture3D::MIRROR );    
    
    setBorderWidth( 0 );
    
    setInternalFormat( GL_LUMINANCE32F_ARB );
}


NoiseTexture3D::~NoiseTexture3D() 
{
}


void NoiseTexture3D::buildImage()
{   
    _image->allocateImage( _pixelSize, _pixelSize, _pixelSize, GL_RGBA, GL_FLOAT );
        
    const long size = _pixelSize * _pixelSize * _pixelSize * 4;

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
