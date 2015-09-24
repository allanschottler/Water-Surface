
uniform sampler3D vertexTexture0;
uniform sampler3D vertexTexture1;
uniform sampler3D vertexTexture2;
uniform sampler3D vertexTexture3;
uniform sampler3D vertexTexture4;
uniform sampler3D vertexTexture5;
uniform sampler3D vertexTexture6;
uniform sampler3D vertexTexture7;

uniform float time;

varying vec4 outcolor;

void main( void )
{  
    vec3 texcoord3d = vec3( gl_TexCoord[0].xy, mod(time, 1000.0)/1000.0 );
    vec4 heightSample = texture3D( vertexTexture7, texcoord3d );
    vec4 coord = vec4( gl_Vertex.xy, heightSample.x, 1.0 );
    gl_Position = gl_ModelViewProjectionMatrix * coord;
    outcolor = heightSample;
}