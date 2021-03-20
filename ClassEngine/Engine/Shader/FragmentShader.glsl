#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;
in vec3 FragPosition;

uniform sampler2D inputTexture;

out vec4 fColor;

struct Light {
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 color;
};

uniform Light light;

uniform vec3 viewPos;


void main(){
	fColor = texture(inputTexture, TexCoords);

	vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.color;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoords).rgb* light.color;

	vec3 viewDir = normalize(viewPos - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specular) * light.color;
	
	vec3 result = ambient + diffuse + specular;
	fColor = vec4(result, 1.0f);
}