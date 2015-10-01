#version 130

uniform sampler3D vertexTexture0;

uniform float time;

varying float outheight;
varying vec3 outnormal;

void main( void )
{
    gl_FragColor = vec4( normalize( outnormal ), 1.0 ); 
    //gl_FragColor = vec4( outheight, outheight, outheight, 1.0 ); 

    //vec3 tcoord = vec3( gl_TexCoord[0].xy, time/10.0 );
    //gl_FragColor = texture3D( vertexTexture0, tcoord ); 
    //gl_FragColor = vec4( gl_TexCoord[0].xyz, 1.0 );
    //gl_FragColor = vec4( 1.0,0.0,0.0, 1.0 );
}
