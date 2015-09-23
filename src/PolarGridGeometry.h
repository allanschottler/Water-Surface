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


class PolarGridGeometry : public osg::Geometry
{
public:    
    
    PolarGridGeometry( unsigned int radialSize, unsigned int angularSize );
    
    virtual ~PolarGridGeometry();
    
private:
    
    void buildGeometry();
    
    static Coordinate polarToCartesian( const Coordinate& polar );
    
    
    unsigned int _radialSize, _angularSize;
    
    osg::ref_ptr< osg::Vec3Array > _vertices;
    osg::ref_ptr< osg::Vec3Array > _normals;
};

#endif	/* POLARGRIDGEOMETRY_H */

