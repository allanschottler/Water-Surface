#version 130

uniform sampler2D oceanFloorTexture;

varying float outheight;
varying vec3 outnormal;
varying vec4 outpos;

const vec3 lightPos = vec3( 0.0, 0.0, 30.0 );
const float lightRadius = 80.0;
const vec4 lightColor = vec4( 1.0, 0.843, 0.0, 1.0 ); 
const vec4 specColor = vec4( 1.0, 1.0, 1.0, 1.0 ); 
const float shininess = 1.0f;

void main( void )
{
    vec4 oceanFloorDiffuse = texture2D( oceanFloorTexture, gl_TexCoord[0].xy );

    vec3 lightRotPos = lightPos;
    float distance = length( lightRotPos - outpos.xyz );
    vec3 lightDir = normalize( lightRotPos - outpos.xyz );
    float lambda = max( dot( lightDir, outnormal ), 0.0f );
    
    vec4 diffuse = mix( oceanFloorDiffuse, lightColor, 0.5 ); 
    float specular = 0.0;

    if(lambda > 0.0) 
    {
        vec3 viewDir = normalize(-outpos.xyz);

        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, outnormal), 0.0);
        specular = pow(specAngle, shininess);        
    }    

    vec3 colorLinear = vec3( 0.1, 0.1, 0.1 ) + lambda * oceanFloorDiffuse.xyz + specular * lightColor.xyz;

    //gl_FragColor = vec4( colorLinear, 1.0 );
    gl_FragColor = vec4( oceanFloorDiffuse.xyz, 1.0 );
}
