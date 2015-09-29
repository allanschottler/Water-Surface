
uniform sampler2D vertexTexture0;
/*uniform sampler3D vertexTexture1;
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
    float rndmZ = sin( time + gl_Vertex.x * gl_Vertex.y );
    
    vec2 tcoord = gl_MultiTexCoord0.st;
    //vec3 texcoord3d = vec3( tcoord.st, 0.1 );
    vec4 heightSample = texture2D( vertexTexture0, tcoord );
    //float height = 0.3 * heightSample.x + 0.59 * heightSample.y + 0.11 * heightSample.z;
    vec4 coord = vec4( gl_Vertex.xy, heightSample.x, 1.0 );

    gl_Position = gl_ModelViewProjectionMatrix * coord;

    //outcolor = heightSample;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
