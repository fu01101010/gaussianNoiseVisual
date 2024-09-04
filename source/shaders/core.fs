#version 330 core

vec3 calculatePointLight(int IDx, vec3 normal, vec3 viewDir);
vec3 calculateDirectLight(vec3 normal, vec3 viewDir);
vec3 calculateSpotLight(vec3 normal, vec3 viewDir);

struct material {

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float reflectivity;
};

#define maxPointLights 10
struct pointLight {

	vec3 position;

	float k0;
	float k1;
	float k2;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform pointLight PointLights[maxPointLights];
uniform int nPointLights;

struct directLight {

	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform directLight DirectLight;

struct spotLight {

	vec3 position;
	vec3 direction;

	float k0;
	float k1;
	float k2;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform spotLight SpotLight;

out vec4 fragmentColor;

in vec3 vsOutFragPos;
in vec3 vsOutNormal;
in vec3 vsOutColor;

uniform material Material;

uniform vec3 viewPos;

void main() {

	vec3 normal	= normalize(vsOutNormal);
	vec3 viewDir	= normalize(viewPos - vsOutFragPos);

	vec3 retval;

	//DirectLight
	retval = calculateDirectLight(normal, viewDir);

	//PointLight
	for (int i = 0; i < nPointLights; ++i) {

		retval += calculatePointLight(i, normal, viewDir);
	}

	//SpotLight	
	retval += calculateSpotLight(normal, viewDir);

	fragmentColor = vec4(retval, 1.0); 
}

vec3 calculatePointLight(int IDx, vec3 normal, vec3 viewDir)  {

	//ambient PointLight
	vec3 ambient = PointLights[IDx].ambient * Material.ambient;


	//diffused PointLight
	vec3 pointLightDir = normalize(PointLights[IDx].position - vsOutFragPos);

	float diffComponent = max(dot(normal, pointLightDir), 0.0);

	vec3 diffuse = PointLights[IDx].diffuse * (diffComponent * Material.diffuse); //if diffuse -> vec3


	//specular PointLight
	vec3 reflectDir = reflect(-pointLightDir, normal);

	float specComponent = pow(max(dot(viewDir, reflectDir), 0.0), Material.reflectivity * 128);

	vec3 specular = PointLights[IDx].specular * (specComponent * Material.specular); //if specular -> vec3


	//attenuation
	float distance = length(PointLights[IDx].position - vsOutFragPos);
	float attenuation = 1.0 / (PointLights[IDx].k0 + PointLights[IDx].k1 * distance + PointLights[IDx].k2 * (distance * distance));

	return vec3(ambient + diffuse + specular) * attenuation;
}

vec3 calculateDirectLight(vec3 normal, vec3 viewDir) {

	//ambient DirectLight
	vec3 ambient = DirectLight.ambient * Material.ambient;


	//diffused DirectLight
	vec3 directLightDir = normalize(-DirectLight.direction);

	float diffComponent = max(dot(normal, directLightDir), 0.0);

	vec3 diffuse = DirectLight.diffuse * (diffComponent * Material.diffuse); //if diffuse -> vec3


	//specular 
	vec3 reflectDir = reflect(-directLightDir, normal);

	float specComponent = pow(max(dot(viewDir, reflectDir), 0.0), Material.reflectivity * 128);

	vec3 specular = DirectLight.specular * (specComponent * Material.specular); //if specular -> vec3


	return vec3(ambient + diffuse + specular);
}

vec3 calculateSpotLight(vec3 normal, vec3 viewDir) {

	//ambient SpotLight
	vec3 ambient = SpotLight.ambient * Material.ambient;

	vec3 spotLightDir = normalize(SpotLight.position - vsOutFragPos);

	float theta0 = dot(spotLightDir, normalize(-SpotLight.direction));

	if (theta0 > SpotLight.outerCutOff) {
		//if in cutOff -> RENDER

		//diffused SpotLight
		float diffComponent = max(dot(normal, spotLightDir), 0.0);
		vec3 diffuse = SpotLight.diffuse * (diffComponent * Material.diffuse);


		//specular SpotLight
		vec3 reflectDir = reflect(-spotLightDir, normal);

		float specComponent = pow(max(dot(viewDir, reflectDir), 0.0), Material.reflectivity * 128);
		vec3 specular = SpotLight.specular * (specComponent * Material.specular);


		//intensity
		float intensity = (theta0 - SpotLight.outerCutOff) / (SpotLight.cutOff - SpotLight.outerCutOff);
		intensity = clamp(intensity, 0.0, 1.0);

		diffuse *= intensity;
		specular *= intensity;


		//attenuation
		float distance = length(SpotLight.position - vsOutFragPos);
		float attenuation = 1.0 / (SpotLight.k0 + SpotLight.k1 * distance + SpotLight.k2 * (distance * distance));

		diffuse *= attenuation;
		specular *= attenuation;


		return vec3(ambient + diffuse + specular);
	}
	else {

		return ambient;
	}
}
