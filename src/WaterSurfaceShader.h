/* 
 * File:   WaterSurfaceShader.h
 * Author: allanws
 *
 * Created on September 23, 2015, 3:15 PM
 */

#ifndef WATERSURFACESHADER_H
#define	WATERSURFACESHADER_H

#include <osg/StateSet>
#include <osg/Texture3D>
#include <osg/Program>
#include <osg/Uniform>
#include <osg/NodeVisitor>


class WaterSurfaceShader : public osg::Uniform::Callback
{
public:
    
    WaterSurfaceShader();
        
    virtual ~WaterSurfaceShader();    

    virtual void operator()( osg::Uniform* u, osg::NodeVisitor* nv )
    {
        float t = (float)nv->getFrameStamp()->getReferenceTime();
        u->set( t );
    }

    
    void linkStateSet( osg::ref_ptr<osg::StateSet> stateSet );        

    void loadVariables();
    
private:    
    
    static std::string readFile( const char *filePath );
    
    
    std::string _vertexProgram;

    std::string _fragmentProgram;
        
    osg::ref_ptr< osg::Program > _shaderProgram;

    osg::ref_ptr< osg::Uniform > _timeUniform;
    
    std::vector< osg::ref_ptr< osg::Uniform > > _vertexTexturesUniforms;
};

#endif	/* WATERSURFACESHADER_H */

