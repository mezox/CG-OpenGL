#version 420

#define LIGHT_COUNT 25

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightPosition[LIGHT_COUNT];

uniform int useFakeLighting;

out float	visibility;
out vec2	tc;
out vec3	toCamera;
out vec3	surfaceNormal;
out vec3	toLight[LIGHT_COUNT];

const float density = 0.007;
const float gradient = 1.5;

void main(void)
{
	vec4 worldPosition = modelMatrix * vec4(position, 1.0);
	vec4 viewSpacePosition = viewMatrix * worldPosition;

	float dist = length(viewSpacePosition.xyz);
	visibility = exp(-pow((dist * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);

	vec3 normalOrig = normal;

	if(useFakeLighting == 1)
		normalOrig = vec3(0.0,1.0,0.0);

	surfaceNormal = (modelMatrix * vec4(normalOrig,0.0)).xyz;

	for(int i = 0; i < LIGHT_COUNT; i++)
		toLight[i] = lightPosition[i] - worldPosition.xyz;


	gl_Position = projectionMatrix * viewSpacePosition;
	
	//Pass variables to fragment shader
	tc = texCoord;
	toCamera = cameraPosition - worldPosition.xyz;
}