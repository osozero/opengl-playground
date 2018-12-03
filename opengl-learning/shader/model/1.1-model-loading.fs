#version 330 core
out vec4 FragColor;

struct	DirectionLight{
	vec3 direction;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct PointLight{
	vec3 position;
	
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	//attenuation
	float constant;
	float linear;
	float quadratic;
};

vec3 CalculateDirectionLight(DirectionLight light, vec3 Normal, vec3 viewDir);

vec3 CalculatePointLight(PointLight light,vec3 normal, vec3 fragPos, vec3 viewDir);

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform DirectionLight directionLight;
uniform PointLight pointLight;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


void main()
{   
	vec3 norm = normalize(Normal);

	vec3 viewDir = normalize(viewPos-FragPos);

	vec3 result = CalculateDirectionLight(directionLight,norm,viewDir);

	result += CalculatePointLight(pointLight,norm,FragPos,viewDir);

    FragColor = vec4(result,1.0) ;
}

vec3 CalculateDirectionLight(DirectionLight light, vec3 Normal, vec3 viewDir)
{
	vec3 lightDirection = normalize(-light.direction);

	//diffuse shading
	float diff = max(dot(Normal,lightDirection),0.0);

	//specular

	//shininess parameter should be configurable...
	float spec = pow(max(dot(Normal,viewDir),0.0),32);

	//combine results

	vec3 ambient = light.ambientColor* vec3(texture(texture_diffuse1,TexCoords));

	vec3 diffuse = light.diffuseColor * vec3(texture(texture_diffuse1,TexCoords));

	vec3 specular = light.specularColor * vec3(texture(texture_specular1,TexCoords));

	vec3 result = ambient + diffuse + specular;

	return result;
}

vec3 CalculatePointLight(PointLight light,vec3 normal, vec3 fragPos, vec3 viewDir){

	  vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambientColor * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuseColor * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specularColor * spec * vec3(texture(texture_specular1, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
