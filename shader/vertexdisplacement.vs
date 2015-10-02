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

vec4 calculateNormalAndHeight( sampler3D tex, vec3 t3coord, float pixelSize, float heightScale )
{
    /*float s11 = textureOffset( tex, t3coord, ivec3( 0, 0, 0 ) ).x * heightScale;
    float s01 = textureOffset( tex, t3coord, ivec3( -1, 0, 0 ) ).x * heightScale;
    float s21 = textureOffset( tex, t3coord, ivec3( 1, 0, 0 ) ).x * heightScale;
    float s10 = textureOffset( tex, t3coord, ivec3( 0, -1, 0 ) ).x * heightScale;
    float s12 = textureOffset( tex, t3coord, ivec3( 0, 1, 0 ) ).x * heightScale;*/

    vec3 d = vec3( -1.0/pixelSize, 1.0/pixelSize, 0.0 );

    float s11 = texture3D( tex, t3coord ).x * heightScale;
    float s01 = texture3D( tex, t3coord + d.xzz ).x * heightScale;
    float s21 = texture3D( tex, t3coord + d.yzz ).x * heightScale;
    float s10 = texture3D( tex, t3coord + d.zxz ).x * heightScale;
    float s12 = texture3D( tex, t3coord + d.zyz ).x * heightScale; 
    
    vec3 va = normalize( vec3( 1.0, 0.0, s21 ) - vec3( -1.0, 0.0, s01 ) );
    vec3 vb = normalize( vec3( 0.0, 1.0, s12 ) - vec3( 0.0, -1.0, s10 ) );

    return vec4( cross( va, vb ), s11 );
}

float calculateHeight( vec2 t2coord, vec2 d )
{
    float dtime = time/1.0;
    
    vec3 t3coord0 = vec3( t2coord + vec2( d.x/pixelSize0, d.y/pixelSize0), dtime/37.0 );
    vec3 t3coord1 = vec3( t2coord + vec2( d.x/pixelSize1, d.y/pixelSize1), dtime/29.0 );
    vec3 t3coord2 = vec3( t2coord + vec2( d.x/pixelSize2, d.y/pixelSize2), dtime/22.0 );
    vec3 t3coord3 = vec3( t2coord + vec2( d.x/pixelSize3, d.y/pixelSize3), dtime/16.0 );
    vec3 t3coord4 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord5 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord6 = vec3( t2coord + vec2( d.x/pixelSize6, d.y/pixelSize6), dtime/16.0 );
    vec3 t3coord7 = vec3( t2coord, dtime/16.0 );

    vec4 bump0 = calculateNormalAndHeight( vertexTexture0, t3coord0, pixelSize0, factor0 );
    vec4 bump1 = calculateNormalAndHeight( vertexTexture1, t3coord1, pixelSize1, factor1 );
    vec4 bump2 = calculateNormalAndHeight( vertexTexture2, t3coord2, pixelSize2, factor2 );
    vec4 bump3 = calculateNormalAndHeight( vertexTexture3, t3coord3, pixelSize3, factor3 );
    vec4 bump4 = calculateNormalAndHeight( vertexTexture4, t3coord4, 1.0, 1.0 );
    vec4 bump5 = calculateNormalAndHeight( vertexTexture5, t3coord5, 1.0, 1.0 );
    vec4 bump6 = calculateNormalAndHeight( vertexTexture6, t3coord6, pixelSize6, factor6 );
    vec4 bump7 = calculateNormalAndHeight( vertexTexture7, t3coord7, 1.0, 1.0 );

    return bump0.a +
                   bump1.a +
                   bump2.a +
                   bump3.a +                   
                   bump6.a ;
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

    vec3 v1 = (gl_ModelViewProjectionMatrix * vec4( 1.0, 0.0, verticalScale * h21, 1.0 )).xyz;
    vec3 v2 = (gl_ModelViewProjectionMatrix * vec4( -1.0, 0.0, verticalScale * h01, 1.0 )).xyz;
    vec3 v3 = (gl_ModelViewProjectionMatrix * vec4( 0.0, 1.0, verticalScale * h12, 1.0 )).xyz;
    vec3 v4 = (gl_ModelViewProjectionMatrix * vec4( 0.0, -1.0, verticalScale * h10, 1.0 )).xyz;

    vec3 va = normalize( v1 - v2 );
    vec3 vb = normalize( v3 - v4 );

    vec3 normal = cross( va, vb );

    vec4 coord = vec4( gl_Vertex.xy, verticalScale * h11, 1.0 );

    outheight = h11;
    outnormal = normal;
    gl_Position = gl_ModelViewProjectionMatrix * coord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
