/* 
 * File:   PolarGridGeometry.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:03 PM
 */

#include <math.h>
#include <iostream>

#include "PolarGridGeometry.h"
#include "WaterSurfaceShader.h"


PolarGridGeometry::PolarGridGeometry( unsigned int radialSize, unsigned int angularSize ) 
{
    _radialSize  = radialSize;
    _angularSize = angularSize;
    
    _vertices  = new osg::Vec3Array;
    _normals   = new osg::Vec3Array;
    _texcoords = new osg::Vec3Array;
        
    setUseDisplayList( false );
    setUseVertexBufferObjects( true );
    
    buildGeometry();     
}


PolarGridGeometry::~PolarGridGeometry() 
{
}


void PolarGridGeometry::linkShader()
{
    _shader.linkStateSet( getOrCreateStateSet() );
}


ICoordinate PolarGridGeometry::makePolarIndex( unsigned int iRadius, unsigned int iAngle )
{
    return std::make_pair( iRadius, iAngle );
}


Coordinate PolarGridGeometry::makePolarCoordinate( const ICoordinate& ipolar )
{
    return std::make_pair( (float)ipolar.first, 
                           (float)( ( 360.f/_angularSize ) * ipolar.second ) );
}


unsigned int PolarGridGeometry::getIndex( const ICoordinate& ipolar )
{
    unsigned int iRadius = ipolar.first  > _radialSize  ? _radialSize   : ipolar.first;
    //unsigned int iRadius = ipolar.first;
    unsigned int iAngle  = ipolar.second >= _angularSize ? ipolar.second - _angularSize : ipolar.second;
    
    return iAngle + iRadius * _angularSize;
}


Coordinate PolarGridGeometry::polarToCartesian( const Coordinate& polar )
{
    return std::make_pair( polar.first * cos( polar.second * M_PI/180.f ), 
                           polar.first * sin( polar.second * M_PI/180.f ) );
}


Coordinate PolarGridGeometry::cartesianToTexCoord( const Coordinate& cartesian )
{    
    return std::make_pair( (float)( ( cartesian.first  + _radialSize ) / ( 2 * _radialSize ) ), 
                           (float)( ( cartesian.second + _radialSize ) / ( 2 * _radialSize ) ) );
}


void PolarGridGeometry::buildGeometry()
{    
    for( unsigned int iRadius = 0; iRadius <= _radialSize; iRadius++ )
    {
        for( unsigned int iAngle = 0; iAngle < _angularSize; iAngle++ )
        {
            ICoordinate i1 = makePolarIndex( iRadius, iAngle );
            ICoordinate i2 = makePolarIndex( iRadius, iAngle + 1 );
            ICoordinate i3 = makePolarIndex( iRadius + 1, iAngle );
            ICoordinate i4 = makePolarIndex( iRadius + 1, iAngle + 1 ); 
            
            Coordinate p   = makePolarCoordinate( i1 );
            Coordinate c   = polarToCartesian( p );
            Coordinate t   = cartesianToTexCoord( c );
            
            // Vertex array
            _vertices->push_back( osg::Vec3( c.first, c.second, 0.0f ) );
            
            // TexCoord array
            _texcoords->push_back( osg::Vec3( t.first, t.second, 0.0f ) );
            
            if( iRadius == _radialSize )
                continue;
            
            // Index array
            osg::ref_ptr< osg::DrawElementsUInt > triangle1 = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0 );
            triangle1->push_back( getIndex( i1 ) );
            triangle1->push_back( getIndex( i3 ) );
            triangle1->push_back( getIndex( i4 ) );
            
            addPrimitiveSet( triangle1 );
            
            osg::ref_ptr< osg::DrawElementsUInt > triangle2 = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0 );
            triangle2->push_back( getIndex( i1 ) );
            triangle2->push_back( getIndex( i4 ) );
            triangle2->push_back( getIndex( i2 ) );
            
            addPrimitiveSet( triangle2 ); 
        }
    }
    
    setVertexArray( _vertices );    
    setTexCoordArray( 0, _texcoords );
}
