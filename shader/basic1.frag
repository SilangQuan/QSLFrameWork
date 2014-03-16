#version 400

in vec3 LightIntensity;
in vec2 TexCoord;
out vec4 outputColor;

uniform sampler2D Tex1; 

void main(void)
{
	//vec4 textureColor = texture(Tex1, TexCoord);
	outputColor = vec4(LightIntensity, 1.0);
	//outputColor = vec4(textureColor, 1.0);
	//outputColor = vec4(1.0,1.0,0.5, 1.0);
}
