#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 lightColor;
void main()
{   float ambientStrength = 0.7;

	vec3 ambient = ambientStrength * lightColor ;
	vec3 result = ambient * texture(texture_diffuse1, TexCoords).rgb;
    FragColor = vec4(result,1.0) ;
}