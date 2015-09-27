/* 
 * File:   PolarGridGeometry.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:03 PM
 */

#ifndef POLARGRIDGEOMETRY_H
#define	POLARGRIDGEOMETRY_H

#include <osg/Geometry>

#include "WaterSurfaceShader.h"


typedef std::pair< float, float > Coordinate;

typedef std::pair< unsigned int, unsigned int > ICoordinate;

class PolarGridGeometry : public osg::Geometry
{
public:    
    
    PolarGridGeometry( unsigned int radialSize, unsigned int angularSize );
    
    virtual ~PolarGridGeometry();    

    void linkShader();

    /*virtual void drawImplementation( osg::RenderInfo& renderInfo );
    
    virtual osg::BoundingBox computeBound() const;*/


    
private:
    
    ICoordinate makePolarIndex( unsigned int iRadius, unsigned int iAngle );
    
    Coordinate makePolarCoordinate( const ICoordinate& ipolar );        
    
    unsigned int getIndex( const ICoordinate& ipolar );
        
    static Coordinate polarToCartesian( const Coordinate& polar );  
    
    Coordinate cartesianToTexCoord( const Coordinate& cartesian );
    
    void buildGeometry();
    
    
    unsigned int _radialSize, _angularSize;
    
    osg::ref_ptr< osg::Vec3Array > _vertices;
    osg::ref_ptr< osg::Vec3Array > _normals;
    osg::ref_ptr< osg::Vec3Array > _texcoords;    
    
    WaterSurfaceShader _shader;
};

#endif	/* POLARGRIDGEOMETRY_H */

