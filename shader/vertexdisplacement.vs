//#version 140

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
const ivec3 off = ivec3( -1, 0, 1 );

const float factor0 = 0.5;
const float factor1 = 0.25;
const float factor2 = 0.125;
const float factor3 = 0.1;
const float factor6 = 0.025;

const float pixelSize0 = 2;
const float pixelSize1 = 4;
const float pixelSize2 = 8;
const float pixelSize3 = 16;
const float pixelSize6 = 128;

vec4 calculateNormalAndHeight( sampler3D tex, vec3 t3coord, float pixelSize, float heightScale )
{
    /*float s11 = texture3D( tex, t3coord ).x * heightScale;
    float texelSize = 1.0 / pixelSize;

    float s01 = texture3D( tex, vec3( t3coord.x - texelSize, t3coord.y, t3coord.z ) ).x * heightScale;
    float s21 = texture3D( tex, vec3( t3coord.x + texelSize, t3coord.y, t3coord.z ) ).x * heightScale;
    float s10 = texture3D( tex, vec3( t3coord.x, t3coord.y - texelSize, t3coord.z ) ).x * heightScale;
    float s12 = texture3D( tex, vec3( t3coord.x, t3coord.y + texelSize, t3coord.z ) ).x * heightScale;*/

    float s11 = textureOffset( tex, t3coord, off.yyy ).x * heightScale;
    float s01 = textureOffset( tex, t3coord, off.xyy ).x * heightScale;
    float s21 = textureOffset( tex, t3coord, off.zyy ).x * heightScale;
    float s10 = textureOffset( tex, t3coord, off.yxy ).x * heightScale;
    float s12 = textureOffset( tex, t3coord, off.yzy ).x * heightScale;

    if( s21-s01 == 0.0 || s12-s10 )
        return vec4( 0.0,0.0,0.0,s11);

    /*ivec3 it3coord = ivec3( int(t3coord.x * pixelSize), int(t3coord.y * pixelSize), int(t3coord.z * pixelSize) );

    float s01 = texelFetch( tex, ivec3( it3coord.x - 1, it3coord.y, it3coord.z ), 0 ).x;
    float s21 = texelFetch( tex, ivec3( it3coord.x + 1, it3coord.y, it3coord.z ), 0 ).x;
    float s10 = texelFetch( tex, ivec3( it3coord.x, it3coord.y - 1, it3coord.z ), 0 ).x;
    float s12 = texelFetch( tex, ivec3( it3coord.x, it3coord.y + 1, it3coord.z ), 0 ).x;*/
    
    vec3 va = normalize( vec3( 1.0, 0.0, s21 ) - vec3( -1.0, 0.0, s01 ) );
    vec3 vb = normalize( vec3( 0.0, 1.0, s12 ) - vec3( 0.0, -1.0, s10 ) );

    return vec4( cross( va, vb ), s11 );
}

void main( void )
{ 
    float dtime = time/1.0;

    vec2 t2coord  = gl_MultiTexCoord0.xy;

    vec3 t3coord0 = vec3( t2coord, dtime/37.0 );
    vec3 t3coord1 = vec3( t2coord, dtime/29.0 );
    vec3 t3coord2 = vec3( t2coord, dtime/22.0 );
    vec3 t3coord3 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord4 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord5 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord6 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord7 = vec3( t2coord, dtime/16.0 );

    vec4 bump0 = calculateNormalAndHeight( vertexTexture0, t3coord0, pixelSize0, factor0 );
    vec4 bump1 = calculateNormalAndHeight( vertexTexture1, t3coord1, pixelSize1, factor1 );
    vec4 bump2 = calculateNormalAndHeight( vertexTexture2, t3coord2, pixelSize2, factor2 );
    vec4 bump3 = calculateNormalAndHeight( vertexTexture3, t3coord3, pixelSize3, factor3 );
    vec4 bump4 = calculateNormalAndHeight( vertexTexture4, t3coord4, 1.0, 1.0 );
    vec4 bump5 = calculateNormalAndHeight( vertexTexture5, t3coord5, 1.0, 1.0 );
    vec4 bump6 = calculateNormalAndHeight( vertexTexture6, t3coord6, pixelSize6, factor6 );
    vec4 bump7 = calculateNormalAndHeight( vertexTexture7, t3coord7, 1.0, 1.0 );

    float height = ( 
                   bump0.a +
                   bump1.a +
                   bump2.a +
                   bump3.a +                   
                   bump6.a 
                   );

    vec3 normal = normalize(
                  bump0.xyz //+ 
                  /*bump1.xyz + 
                  bump2.xyz + 
                  bump3.xyz +                    
                  bump6.xyz*/
                  );

    vec4 coord = vec4( gl_Vertex.xy, verticalScale * height, 1.0 );

    outheight = height;
    outnormal = normal;
    gl_Position = gl_ModelViewProjectionMatrix * coord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
