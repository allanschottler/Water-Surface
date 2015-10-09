#version 130

uniform float time;

varying float outheight;
varying vec3 outnormal;
varying vec4 outpos;

const vec3 lightPos = vec3( 0.0, 0.0, 30.0 );
const float lightRadius = 80.0;
//const vec4 lightColor = vec4( 1.0, 0.843, 0.0, 1.0 ); 
const vec4 lightColor = vec4( 1.0, 1.0, 1.0, 1.0 ); 
const vec4 waterColor = vec4( 0.2, 0.3, 0.8, 1.0 ); 
const vec4 specColor = vec4( 1.0, 1.0, 1.0, 1.0 ); 
const float shininess = 0.7f;

void main( void )
{
    vec3 lightRotPos = lightPos + vec3( sin( time/8.0 ) * lightRadius, cos( time/8.0 ) * lightRadius, 0.0 );
    float distance = length( lightRotPos - outpos.xyz );
    vec3 lightDir = normalize( lightRotPos - outpos.xyz );
    float lambda = max( dot( lightDir, outnormal ), 0.0f );
    
    vec4 diffuse = mix( waterColor, lightColor, 0.5 ); 
    float specular = 0.0;

    if( lambda > 0.0 ) 
    {
        vec3 viewDir = normalize( -outpos.xyz );

        vec3 halfDir = normalize( lightDir + viewDir );
        float specAngle = max( dot( halfDir, outnormal ), 0.0 );
        specular = pow( specAngle, shininess );        
    }

    vec3 colorLinear = vec3( 0.1, 0.1, 0.1 ) + lambda * waterColor.xyz + specular * lightColor.xyz;

    gl_FragColor = vec4( colorLinear, 0.92 );
    
    //gl_FragColor = vec4( normalize( outnormal ), 1.0 ); 
    //gl_FragColor = vec4( outheight, outheight, outheight, 1.0 ); 
}
