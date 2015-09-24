/* 
 * File:   PolarGridGeometry.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:03 PM
 */

#ifndef POLARGRIDGEOMETRY_H
#define	POLARGRIDGEOMETRY_H

#include <osg/Geometry>


typedef std::pair< float, float > Coordinate;

typedef std::pair< unsigned int, unsigned int > ICoordinate;

class PolarGridGeometry : public osg::Geometry
{
public:    
    
    PolarGridGeometry( unsigned int radialSize, unsigned int angularSize );
    
    virtual ~PolarGridGeometry();
    
private:
    
    ICoordinate makePolarIndex( unsigned int iRadius, unsigned int iAngle );
    
    Coordinate makePolarCoordinate( const ICoordinate& ipolar );        
    
    unsigned int getIndex( const ICoordinate& ipolar );
        
    static Coordinate polarToCartesian( const Coordinate& polar );  
    
    Coordinate polarToTexCoord( const Coordinate& polar );
    
    void buildGeometry();
    
    
    unsigned int _radialSize, _angularSize;
    
    osg::ref_ptr< osg::Vec3Array > _vertices;
    osg::ref_ptr< osg::Vec3Array > _normals;
    osg::ref_ptr< osg::Vec2Array > _texcoords;
};

#endif	/* POLARGRIDGEOMETRY_H */

