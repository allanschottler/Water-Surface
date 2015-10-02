#version 130

uniform sampler3D vertexTexture3;

uniform float time;

varying float outheight;
varying vec3 outnormal;

const float verticalScale = 15.0;
const vec2 size = vec2( 2.0, 0.0 );
const ivec3 off = ivec3( -1, 0, 1 );

/*vec4 calculateNormalAndHeight( sampler3D tex, vec3 t3coord, float pixelSize, float heightScale )
{
    float s11 = textureOffset( tex, t3coord, off.yyy ).x * heightScale;
    float s01 = textureOffset( tex, t3coord, off.xyy ).x * heightScale;
    float s21 = textureOffset( tex, t3coord, off.zyy ).x * heightScale;
    float s10 = textureOffset( tex, t3coord, off.yxy ).x * heightScale;
    float s12 = textureOffset( tex, t3coord, off.yzy ).x * heightScale;
    
    vec3 va = normalize( vec3( 1.0, 0.0, s21 ) - vec3( -1.0, 0.0, s01 ) );
    vec3 vb = normalize( vec3( 0.0, 1.0, s12 ) - vec3( 0.0, -1.0, s10 ) );

    return vec4( cross( va, vb ), s11 );
}*/

void main( void )
{
    gl_FragColor = vec4( normalize( outnormal ), 1.0 ); 
    //gl_FragColor = vec4( outheight, outheight, outheight, 1.0 ); 

    //vec3 tcoord = vec3( gl_TexCoord[0].xy, time/10.0 );
    //gl_FragColor = texture3D( vertexTexture0, tcoord ); 
    //gl_FragColor = vec4( gl_TexCoord[0].xyz, 1.0 );
    //gl_FragColor = vec4( 1.0,0.0,0.0, 1.0 );
}
