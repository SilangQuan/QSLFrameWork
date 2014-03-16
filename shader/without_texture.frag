#version 400
in vec3 LightIntensity;
out vec4 outputColor;

void main(void)
{
	vec4 lightColor = vec4(LightIntensity, 1.0);
	outputColor = lightColor;
	//outputColor = vec4(1.0,1.0,0.0,1.0);

}
