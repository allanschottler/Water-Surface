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

const float verticalScale = 20.0;
const vec2 size = vec2( 2.0, 0.0 );
const ivec3 off = ivec3( -1, 0, 1 );

vec4 calculateNormalAndHeight( sampler3D tex, vec3 t3coord )
{
    float s11 = texture3D( tex, t3coord ).x;
    float s01 = textureOffset( tex, t3coord, off.xyy ).x;
    float s21 = textureOffset( tex, t3coord, off.zyy ).x;
    float s10 = textureOffset( tex, t3coord, off.yxy ).x;
    float s12 = textureOffset( tex, t3coord, off.yzy ).x;
    vec3 va = normalize( vec3( size.x, s21-s01, size.y ) );
    vec3 vb = normalize( vec3( size.y, s12-s10, -size.x ) );

    return vec4( cross( va, vb ), s11 );
}

void main( void )
{ 
    float dtime = time/2.0;

    vec2 t2coord  = gl_MultiTexCoord0.xy;

    vec3 t3coord0 = vec3( t2coord, dtime/37.0 );
    vec3 t3coord1 = vec3( t2coord, dtime/29.0 );
    vec3 t3coord2 = vec3( t2coord, dtime/22.0 );
    vec3 t3coord3 = vec3( t2coord, dtime/16.0 );
    vec3 t3coord4 = vec3( t2coord, dtime/11.0 );
    vec3 t3coord5 = vec3( t2coord, dtime/7.0 );
    vec3 t3coord6 = vec3( t2coord, dtime/4.0 );
    vec3 t3coord7 = vec3( t2coord, dtime/2.0 );

    float factor0 = 1.00;
    float factor1 = 0.95;
    float factor2 = 0.90;
    float factor3 = 0.85;
    float factor4 = 0.80;
    float factor5 = 0.75;
    float factor6 = 0.70;
    float factor7 = 0.65;

    /*float height0 = texture3D( vertexTexture0, t3coord0 ).x;// * factor0;
    float height1 = texture3D( vertexTexture1, t3coord1 ).x;// * factor1;
    float height2 = texture3D( vertexTexture2, t3coord2 ).x;// * factor2;
    float height3 = texture3D( vertexTexture3, t3coord3 ).x;// * factor3;
    float height4 = texture3D( vertexTexture4, t3coord4 ).x;// * factor4;
    float height5 = texture3D( vertexTexture5, t3coord5 ).x;// * factor5;
    float height6 = texture3D( vertexTexture6, t3coord6 ).x;// * factor6;
    float height7 = texture3D( vertexTexture7, t3coord7 ).x;// * factor7;*/

    vec4 bump0 = calculateNormalAndHeight( vertexTexture0, t3coord0 );
    vec4 bump1 = calculateNormalAndHeight( vertexTexture1, t3coord1 );
    vec4 bump2 = calculateNormalAndHeight( vertexTexture2, t3coord2 );
    vec4 bump3 = calculateNormalAndHeight( vertexTexture3, t3coord3 );
    vec4 bump4 = calculateNormalAndHeight( vertexTexture4, t3coord4 );
    vec4 bump5 = calculateNormalAndHeight( vertexTexture5, t3coord5 );
    vec4 bump6 = calculateNormalAndHeight( vertexTexture6, t3coord6 );
    vec4 bump7 = calculateNormalAndHeight( vertexTexture7, t3coord7 );

    float height = ( 
                   bump0.a +
                   /*bump1.a +
                   bump2.a +
                   bump3.a +
                   bump4.a +
                   bump5.a +
                   bump6.a +
                   bump7.a + */
                   0.0 ) / 1.0; //4ismagic

    vec3 normal = normalize(
                  bump0.xyz + 
                  /*bump1.xyz + 
                  bump2.xyz + 
                  bump3.xyz + 
                  bump4.xyz + 
                  bump5.xyz + 
                  bump6.xyz + 
                  bump7.xyz + */
                  vec3(0.0,0.0,0.0)
                  );

    vec4 coord = vec4( gl_Vertex.xy, verticalScale * height, 1.0 );

    outheight = height;
    outnormal = normal;
    gl_Position = gl_ModelViewProjectionMatrix * coord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
