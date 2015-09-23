/* 
 * File:   OSGShaderFactory.cpp
 * Author: leomaia
 * 
 * Created on December 2, 2014, 8:39 AM
 */

#include <map>

#include "OSGShaderFactory.h"

OSGShaderFactory* OSGShaderFactory::_instance = 0;

OSGShaderFactory::OSGShaderFactory() 
{
}

OSGShaderFactory::~OSGShaderFactory() 
{
}

OSGShaderFactory* OSGShaderFactory::getInstance()
{
    if( !_instance )
    {
        _instance = new OSGShaderFactory();
    }
    
    return _instance;
}


void OSGShaderFactory::destroy()
{
    delete _instance;
    _instance = 0;
}


osg::ref_ptr<osg::Program> OSGShaderFactory::createShaderProgram( const std::string& vertexProgram, const std::string& geometryProgram, const std::string& fragmentProgram, int verticesOutEnum, int inputeTypeEnum, int outputTypeEnum )
{
    osg::ref_ptr<osg::Program> program = createShaderProgram( vertexProgram, fragmentProgram );
    
    osg::ref_ptr<osg::Shader> geometryShader = getShader( geometryProgram, osg::Shader::GEOMETRY );
    
    program->addShader( geometryShader );
    
    program->setParameter( GL_GEOMETRY_VERTICES_OUT_EXT, verticesOutEnum );
    program->setParameter( GL_GEOMETRY_INPUT_TYPE_EXT, inputeTypeEnum );
    program->setParameter( GL_GEOMETRY_OUTPUT_TYPE_EXT, outputTypeEnum );
    
    return program;
}

osg::ref_ptr<osg::Program> OSGShaderFactory::createShaderProgram( const std::string& vertexProgram, const std::string& fragmentProgram )
{
    osg::ref_ptr<osg::Program> program = new osg::Program;
    
    osg::ref_ptr<osg::Shader> vertexShader = getShader( vertexProgram, osg::Shader::VERTEX );
    osg::ref_ptr<osg::Shader> fragmentShader = getShader( fragmentProgram, osg::Shader::FRAGMENT );
    
    program->addShader( vertexShader );
    program->addShader( fragmentShader );
    
    return program;
}


osg::ref_ptr<osg::Shader> OSGShaderFactory::getShader( const std::string& shaderProgram, osg::Shader::Type type )
{
    std::pair< std::string, osg::Shader::Type > key( shaderProgram, type );
    
    if( _shaderMap.count( key ) == 0 )
    {
        _shaderMap[key] = new osg::Shader( type, shaderProgram );
    }
    
    return _shaderMap[key];
}

