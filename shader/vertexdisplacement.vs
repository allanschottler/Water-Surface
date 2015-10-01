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
const ivec3 off = ivec3( -1, 0, 1 );

vec4 calculateNormalAndHeight( sampler3D tex, vec3 t3coord )
{
    float s11 = texture3D( tex, t3coord ).x;
    float s01 = textureOffset( tex, t3coord, off.xyy ).x;
    float s21 = textureOffset( tex, t3coord, off.zyy ).x;
    float s10 = textureOffset( tex, t3coord, off.yxy ).x;
    float s12 = textureOffset( tex, t3coord, off.yzy ).x;
    vec3 va = normalize( vec3( size.xy, s21-s01 ) );
    vec3 vb = normalize( vec3( size.yx, s12-s10 ) );

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

    vec4 bump0 = calculateNormalAndHeight( vertexTexture0, t3coord0 );
    vec4 bump1 = calculateNormalAndHeight( vertexTexture1, t3coord1 );
    vec4 bump2 = calculateNormalAndHeight( vertexTexture2, t3coord2 );
    vec4 bump3 = calculateNormalAndHeight( vertexTexture3, t3coord3 );
    vec4 bump4 = calculateNormalAndHeight( vertexTexture4, t3coord4 );
    vec4 bump5 = calculateNormalAndHeight( vertexTexture5, t3coord5 );
    vec4 bump6 = calculateNormalAndHeight( vertexTexture6, t3coord6 );
    vec4 bump7 = calculateNormalAndHeight( vertexTexture7, t3coord7 );

    float height = ( 
                   0.5 * bump0.a +
                   0.25 * bump1.a +
                   0.125 * bump2.a +
                   0.1 * bump3.a +
                   /*bump4.a +
                   bump5.a +
                   bump6.a +*/
                   0.025 * bump6.a + 
                   0.0 );// / 4.0; //4ismagic

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

    float s01 = textureOffset( vertexTexture6, t3coord6, off.xyy ).x;
    float s21 = textureOffset( vertexTexture6, t3coord6, off.zyy ).x;
    float s10 = textureOffset( vertexTexture6, t3coord6, off.yxy ).x;
    float s12 = textureOffset( vertexTexture6, t3coord6, off.yzy ).x;

    vec3 va = normalize( vec3( size.xy, s21-s01 ) );
    vec3 vb = normalize( vec3( size.yx, s12-s10 ) );

    normal = vec3( vb );
    vec4 coord = vec4( gl_Vertex.xy, verticalScale * height, 1.0 );

    outheight = height;
    outnormal = normal;
    gl_Position = gl_ModelViewProjectionMatrix * coord;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
