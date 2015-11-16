#version 420

#define LIGHT_COUNT 25

in vec2 tc;
in vec3 toCamera;
in vec3	surfaceNormal;
in vec3	toLight[LIGHT_COUNT];
in float visibility;

uniform sampler2D bgTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

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
	vec4 blendMapColor = texture(blendMap, tc);

	float bgTextureAmount = 1.0 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tileTexCoords = tc * 40.0;

	vec4 bgTextureColor = texture(bgTexture, tileTexCoords) * bgTextureAmount;
	vec4 rTextureColor = texture(rTexture, tileTexCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(gTexture, tileTexCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(bTexture, tileTexCoords) * blendMapColor.b;

	vec4 color = bgTextureColor + rTextureColor + gTextureColor + bTextureColor;


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

	//outColor = texture(rTexture, tileTexCoords);
}