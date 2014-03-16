#version 400
in vec3 LightIntensity;
in vec2 TexCoord;
out vec4 outputColor;

uniform sampler2D Tex1;

void main(void)
{
	vec4 textureColor = texture(Tex1, TexCoord);
	vec4 lightColor = vec4(LightIntensity, 1.0);
	
	outputColor = mix(textureColor, lightColor, 0.1);
	//outputColor = textureColor;
	//outputColor = vec4(TexCoord,0.0,0.0);
	//outputColor = vec4(1.0,1.0,0.5, 1.0);
}
