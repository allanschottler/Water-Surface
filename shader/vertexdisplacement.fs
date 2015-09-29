
uniform sampler2D vertexTexture0;

varying vec4 outcolor;

void main( void )
{
    gl_FragColor = texture2D( vertexTexture0, gl_TexCoord[0].xy ); 
    //gl_FragColor = vec4( gl_TexCoord[0].xyz, 1.0 );
    //gl_FragColor = vec4( 1.0,0.0,0.0, 1.0 );
}
