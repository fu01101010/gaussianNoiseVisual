#version 330 core

struct material {

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float reflectivity;
};

struct light {

	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 fragmentColor;

in vec3 vsOutFragPos;
in vec3 vsOutNormal;
in vec3 vsOutColor;

uniform material Material;
uniform light Light;

uniform vec3 viewPos;

void main() {

	fragmentColor = vec4(vsOutColor, 1.0f);

	//ambient light
	vec3 ambient = Light.ambient * Material.ambient;

	//diffused light
	vec3 normal = normalize(vsOutNormal);
	vec3 lightDir = normalize(Light.position - vsOutFragPos);

	float diffComponent = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = Light.diffuse * (diffComponent * Material.diffuse); //if diffuse -> vec3

	//specular light
	vec3 viewDir	= normalize(viewPos - vsOutFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specComponent = pow(max(dot(viewDir, reflectDir), 0.0), Material.reflectivity * 128);
	vec3 specular = Light.specular * (specComponent * Material.specular);

	fragmentColor = vec4(vec3(ambient + diffuse + specular), 1.0); 
}
