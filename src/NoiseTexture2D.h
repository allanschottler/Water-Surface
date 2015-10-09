/* 
 * File:   NoiseTexture2D.h
 * Author: allan
 *
 * Created on October 9, 2015, 5:58 PM
 */

#ifndef NOISETEXTURE2D_H
#define	NOISETEXTURE2D_H

#include <osg/Texture2D>

class NoiseTexture2D : public osg::Texture2D
{
public:
    
    NoiseTexture2D( unsigned int pixelSize );
    
    virtual ~NoiseTexture2D();
    
private:

    void buildImage();
    
    
    unsigned int _pixelSize;
    
    osg::ref_ptr< osg::Image > _image;
};

#endif	/* NOISETEXTURE2D_H */

