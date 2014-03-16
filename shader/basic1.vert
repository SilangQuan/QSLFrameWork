#version 400
layout (location = 0) in vec3 VertexPosition;  
layout (location = 2) in vec2 VertexUv;  
layout (location = 2) in vec3 VertexNormal;  

out vec3 LightIntensity;

uniform vec4 LightPosition; // Light position in eye coords.
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;


void main()
{
	vec3 tnorm = normalize(NormalMatrix * VertexNormal);
	//vec3 tnorm = normalize(NormalMatrix * vec3(0.1,0.0,0.0));
	vec4 eyeCoords = ModelViewMatrix * vec4(VertexPosition, 1.0);
	vec3 s = normalize(vec3(LightPosition - eyeCoords));
	LightIntensity = Ld * Kd * max(dot(s,tnorm),0.0);
	gl_Position = MVP * vec4( VertexPosition, 1.0);
}
