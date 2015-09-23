/* 
 * File:   WaterSurfaceShader.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 3:15 PM
 */

#include "WaterSurfaceShader.h"

WaterSurfaceShader::WaterSurfaceShader() {
}


WaterSurfaceShader::~WaterSurfaceShader() {
}


void WaterSurfaceShader::linkStateSet( osg::ref_ptr<osg::StateSet> stateSet )
{
    stateSet->addUniform( _vertexTexturesUniform );
    
    stateSet->setAttributeAndModes( _shaderProgram, osg::StateAttribute::ON );
}


void WaterSurfaceShader::loadVariables()
{
    
}


void WaterSurfaceShader::setVertexTextures( std::vector< osg::ref_ptr< osg::Texture3D > > vertexTextures3D )
{
    _vertexTextures3D = vertexTextures3D;
}

