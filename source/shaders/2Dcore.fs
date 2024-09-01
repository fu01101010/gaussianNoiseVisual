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
in vec2 vsOutColor;

uniform material Material;
uniform light Light;

uniform vec3 viewPos;

void main() {

	fragmentColor = vec4(0.3f, 0.3f, 0.3f, 1.0f);

	//AMBIENT light
/*
	vec3 AMBIENT = Light.Ambient * Material.Ambient;

	//DIFFUSED light
	vec3 NORMAL = normalize(VertCoreOutNormal);
	vec3 LightDir = normalize(Light.Position - VertCoreOutFragPos);

	float DIFFComponent = max(dot(NORMAL, LightDir), 0.0);
	//vec3 DIFFUSE = Light.Diffuse * (DIFFComponent * Material.Diffuse); //if Diffuse -> vec3
	vec3 DIFFUSE = Light.Diffuse * (DIFFComponent * vec3(texture(Material.Diffuse, VertCoreOutTexCoord)));


	//SPECULAR light
	vec3 ViewDir	= normalize(ViewPos - VertCoreOutFragPos);
	vec3 ReflectDir = reflect(-LightDir, NORMAL);

	float SPECComponent = pow(max(dot(ViewDir, ReflectDir), 0.0), Material.Reflectivity * 128);
	vec3 SPECULAR = Light.Specular * (SPECComponent * Material.Specular);

	FragmentColor = vec4(vec3(AMBIENT + DIFFUSE + SPECULAR), 1.0); 
*/
	
}
