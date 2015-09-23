/* 
 * File:   PolarGridGeometry.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:03 PM
 */

#ifndef POLARGRIDGEOMETRY_H
#define	POLARGRIDGEOMETRY_H

#include <osg/Geometry>


class PolarGridGeometry : public osg::Geometry
{
public:
    
    typedef std::pair< float, float > Coordinate;
    
    PolarGridGeometry( int radialSize, int angularSize );
    
    virtual ~PolarGridGeometry();
    
private:
    
    void buildGeometry();
    
    Coordinate polarToCartesian( const Coordinate& polar );
    
    
    int _radialSize, _angularSize;

};

#endif	/* POLARGRIDGEOMETRY_H */

