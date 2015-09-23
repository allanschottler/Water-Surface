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
    _image->allocateImage( pixelSize, pixelSize, pixelSize, GL_RGB, GL_FLOAT );
    
    buildTexture();
}


NoiseTexture3D::~NoiseTexture3D() 
{
}


float randomFloat()
{
    return static_cast< float >( rand() ) / static_cast< float >( RAND_MAX );
}


void NoiseTexture3D::buildTexture()
{
    srand( static_cast< unsigned >( time( 0 ) ) );
    
    for( unsigned int i = 0; i < _pixelSize; i++ )
    {
        for( unsigned int j = 0; j < _pixelSize; j++ )
        {
            for( unsigned int k = 0; k < _pixelSize; k++ )
            {
                float val = randomFloat();
                _image->data( k, j, i )[ 0 ] = val;
                _image->data( k, j, i )[ 1 ] = val;
                _image->data( k, j, i )[ 2 ] = val;
            }
        }
    }
    
    setImage( _image );
}