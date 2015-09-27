
/*uniform sampler3D vertexTexture0;
uniform sampler3D vertexTexture1;
uniform sampler3D vertexTexture2;
uniform sampler3D vertexTexture3;
uniform sampler3D vertexTexture4;
uniform sampler3D vertexTexture5;
uniform sampler3D vertexTexture6;
uniform sampler3D vertexTexture7;*/

uniform float time;

varying vec4 outcolor;

void main( void )
{  
    vec2 tcoord = gl_TexCoord[0].st;
    float h = gl_Vertex.x * gl_Vertex.x + gl_Vertex.y * gl_Vertex.y;
    float texz = sin( time + gl_Vertex.x * gl_Vertex.y );
    vec3 texcoord3d = vec3( tcoord.st, 0.1 );
    //vec4 heightSample = texture3D( vertexTexture0, texcoord3d );
    vec4 coord = vec4( gl_Vertex.xy, texz, 1.0 );
    gl_Position = gl_ModelViewProjectionMatrix * coord;
    //outcolor = heightSample;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
