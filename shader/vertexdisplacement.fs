
uniform sampler3D vertexTexture0;

uniform float time;

varying vec4 outcolor;

void main( void )
{
    gl_FragColor = texture3D( vertexTexture0, vec3( gl_TexCoord[0].xy, ( sin( time ) + 1 )/2.0 ) ); 
    //gl_FragColor = vec4( gl_TexCoord[0].xyz, 1.0 );
    //gl_FragColor = vec4( 1.0,0.0,0.0, 1.0 );
}
