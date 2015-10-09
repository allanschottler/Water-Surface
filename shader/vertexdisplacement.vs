#version 130

uniform sampler3D vertexTexture0;
uniform sampler3D vertexTexture1;
uniform sampler3D vertexTexture2;
uniform sampler3D vertexTexture3;
uniform sampler3D vertexTexture4;
uniform sampler3D vertexTexture5;
uniform sampler3D vertexTexture6;
uniform sampler3D vertexTexture7;

uniform float time;

varying float outheight;
varying vec3 outnormal;
varying vec4 outpos;

const float verticalScale = 15.0;
const vec2 size = vec2( 2.0, 0.0 );

const float factor0 = 0.5;
const float factor1 = 0.25;
const float factor2 = 0.125;
const float factor3 = 0.1;
const float factor6 = 0.025;

const float pixelSize0 = 2.0;
const float pixelSize1 = 4.0;
const float pixelSize2 = 8.0;
const float pixelSize3 = 16.0;
const float pixelSize6 = 128.0;


float calculateHeight( vec2 t2coord, vec2 d )
{
    float dtime = time/1.0;
    
    vec3 t3coord0 = vec3( t2coord + d/pixelSize6, dtime/37.0 );
    vec3 t3coord1 = vec3( t2coord + d/pixelSize6, dtime/29.0 );
    vec3 t3coord2 = vec3( t2coord + d/pixelSize6, dtime/22.0 );
    vec3 t3coord3 = vec3( t2coord + d/pixelSize6, dtime/22.0 );
    vec3 t3coord4 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord5 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord6 = vec3( t2coord + d/pixelSize6, dtime/22.0 );
    vec3 t3coord7 = vec3( t2coord, dtime/16.0 );

    float h0 = texture3D( vertexTexture0, t3coord0 ).x * factor0;
    float h1 = texture3D( vertexTexture1, t3coord1 ).x * factor1;
    float h2 = texture3D( vertexTexture2, t3coord2 ).x * factor2;
    float h3 = texture3D( vertexTexture3, t3coord3 ).x * factor3;
    float h6 = texture3D( vertexTexture6, t3coord6 ).x * factor6;

    return h0+h1+h2+h3+h6;
}

void main( void )
{ 
    vec2 v11 = gl_MultiTexCoord0.xy;
    vec3 d = vec3( -1.0, 1.0, 0.0 );

    float h11 = calculateHeight( v11, d.zz );
    float h01 = calculateHeight( v11, d.xz );
    float h21 = calculateHeight( v11, d.yz );
    float h10 = calculateHeight( v11, d.zx );
    float h12 = calculateHeight( v11, d.zy );

    vec3 v1 = (vec4( 1.0, 0.0, h21 * verticalScale, 1.0 )).xyz;
    vec3 v2 = (vec4( -1.0, 0.0, h01 * verticalScale, 1.0 )).xyz;
    vec3 v3 = (vec4( 0.0, 1.0, h12 * verticalScale, 1.0 )).xyz;
    vec3 v4 = (vec4( 0.0, -1.0, h10 * verticalScale, 1.0 )).xyz;

    vec3 va = normalize( v1 - v2 );
    vec3 vb = normalize( v3 - v4 );

    vec3 normal = cross( va, vb );

    vec4 coord = vec4( gl_Vertex.xy, verticalScale * h11, 1.0 );

    outheight = h11;
    outnormal = normal;
    outpos = coord;

    gl_Position = gl_ModelViewProjectionMatrix * coord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
