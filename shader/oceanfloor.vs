#version 130

uniform sampler2D vertexTexture0;
uniform sampler2D vertexTexture1;
uniform sampler2D vertexTexture2;

varying float outheight;
varying vec3 outnormal;
varying vec4 outpos;

const float verticalScale = 15.0;
const vec2 size = vec2( 2.0, 0.0 );

const float factor0 = 0.5;
const float factor1 = 0.25;
const float factor2 = 0.25;

const float pixelSize0 = 2.0;
const float pixelSize1 = 4.0;
const float pixelSize2 = 8.0;


float calculateHeight( vec2 t2coord, vec2 d )
{    
    vec2 t2coord0 = t2coord + d/pixelSize2;
    vec2 t2coord1 = t2coord + d/pixelSize2;
    vec2 t2coord2 = t2coord + d/pixelSize2;

    float h0 = texture2D( vertexTexture0, t2coord0 ).x * factor0;
    float h1 = texture2D( vertexTexture1, t2coord1 ).x * factor1;
    float h2 = texture2D( vertexTexture2, t2coord2 ).x * factor2;

    return h0+h1+h2;
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

    vec4 coord = vec4( gl_Vertex.xy, verticalScale * (h11 - 1.0), 1.0 );

    outheight = h11;
    outnormal = normal;
    outpos = coord;

    gl_Position = gl_ModelViewProjectionMatrix * coord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
