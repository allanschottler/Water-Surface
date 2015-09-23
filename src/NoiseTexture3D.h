/* 
 * File:   NoiseTexture3D.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:44 PM
 */

#ifndef NOISETEXTURE3D_H
#define	NOISETEXTURE3D_H

#include <osg/Texture3D>


class NoiseTexture3D : public osg::Texture3D
{
public:
    
    NoiseTexture3D( unsigned int pixelSize );
    
    virtual ~NoiseTexture3D();
    
private:
    
    void buildTexture();
    
    
    unsigned int _pixelSize;
    
    osg::ref_ptr< osg::Image > _image;

};

#endif	/* NOISETEXTURE3D_H */

