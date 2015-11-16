#version 420

#define LIGHT_COUNT 25

in vec2 tc;
in vec3 toCamera;
in vec3	surfaceNormal;
in vec3	toLight[LIGHT_COUNT];
in float visibility;


uniform sampler2D diffuseTex;
uniform sampler2D alphaTex;
uniform int hasTextures;
uniform int hasTransparency;

//Light properties
uniform vec3	lColor[LIGHT_COUNT];
uniform vec3	lAttenuation[LIGHT_COUNT];
uniform float	lAmIntensity = 0.0;

uniform vec3	skyColor;
uniform float	shineDamper;
uniform float	reflectivity;

out vec4 outColor;

void main(void)
{
	vec4 color;

	if(hasTextures == 1)
	{
		if(hasTransparency == 1)
		{
			float alpha = texture(alphaTex, tc).r;
			color = texture(diffuseTex, tc);
	
			if(alpha < 0.9)
				discard;
		}
		else
			color = texture(diffuseTex, tc);
	}

	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitToCamera = normalize(toCamera);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);
	 
	for(int i = 0; i < LIGHT_COUNT; i++)
	{
		//Get distance from fragment to light
		float dist = length(toLight[i]);

		//Compute attenuation
		float attFactor = lAttenuation[i].x + (lAttenuation[i].y * dist) + (lAttenuation[i].z * dist * dist);
		
		//diffuse lighting
		vec3 unitToLight = normalize(toLight[i]);
		float nDotl = dot(unitNormal,unitToLight);
		float brightness = max(nDotl, 0.0);

		vec3 lDirection = -unitToLight;
		vec3 reflectedDirection = reflect(lDirection, unitNormal);

		float specFactor = dot(reflectedDirection, unitToCamera);
		specFactor = max(specFactor, 0.0);

		float dampedFactor = pow(specFactor, shineDamper);

		totalDiffuse += (brightness * lColor[i])/attFactor; 
		totalSpecular += (dampedFactor * reflectivity * lColor[i])/attFactor;
	}

	//Add ambient lighting
	totalDiffuse = max(totalDiffuse, lAmIntensity);

	outColor = vec4(totalDiffuse, 1.0) * color + vec4(totalSpecular, 1.0);
	outColor = mix(vec4(skyColor,1.0), outColor, visibility);
}