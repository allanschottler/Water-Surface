/* 
 * File:   PolarGridGeometry.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:03 PM
 */

#include <math.h>

#include "PolarGridGeometry.h"


PolarGridGeometry::PolarGridGeometry( unsigned int radialSize, unsigned int angularSize ) 
{
    _radialSize = radialSize;
    _angularSize = angularSize;
    
    setUseVertexBufferObjects( true );
}


PolarGridGeometry::~PolarGridGeometry() 
{
}


void PolarGridGeometry::buildGeometry()
{
    for( unsigned int iRadius = 0; iRadius < _radialSize; iRadius++ )
    {
        for( unsigned int iAngle = 0; iAngle < _angularSize; iAngle++ )
        {
            Coordinate polarCoordinate = std::make_pair( (float)iRadius, (float)(360.f/_angularSize) * iAngle );
            Coordinate cartesianCoordinate = polarToCartesian( polarCoordinate );
            
            osg::Vec3 cartesianPoint( cartesianCoordinate.first, cartesianCoordinate.second, 0.0f );
            _vertices->push_back( cartesianPoint );
        }
    }
}


Coordinate PolarGridGeometry::polarToCartesian( const Coordinate& polar )
{
    Coordinate cartesianCoordinate = std::make_pair( polar.first * cos( polar.second ), polar.first * sin( polar.second ) );
    return cartesianCoordinate;
}