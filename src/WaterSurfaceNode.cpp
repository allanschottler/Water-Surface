/* 
 * File:   WaterSurfaceNode.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 2:52 PM
 */

#include <sys/param.h>

#include "WaterSurfaceNode.h"
#include "NoiseTexture3D.h"

WaterSurfaceNode::WaterSurfaceNode( unsigned int heightMapLevels ) 
{
    _heightMapLevels = heightMapLevels;
}


WaterSurfaceNode::~WaterSurfaceNode() 
{
}


void WaterSurfaceNode::buildVertexTextures()
{
    for( unsigned int iLevel = 0; iLevel < _heightMapLevels; iLevel++ )
    {
        _vertexTextures3D.push_back( new NoiseTexture3D( powerof2( iLevel ) ) );
    }
}