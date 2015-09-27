
uniform sampler3D vertexTexture0;
uniform sampler3D vertexTexture1;
uniform sampler3D vertexTexture2;
uniform sampler3D vertexTexture3;
uniform sampler3D vertexTexture4;
uniform sampler3D vertexTexture5;
uniform sampler3D vertexTexture6;
uniform sampler3D vertexTexture7;

varying vec4 outcolor;

void main( void )
{
    gl_FragColor = texture3D( vertexTexture1, gl_TexCoord[0].xyz ); 
    //gl_FragColor = vec4( gl_TexCoord[0].xyz, 1.0);
}
