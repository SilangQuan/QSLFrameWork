#version 400

in vec4 Position;
in vec3 Normal;
in vec2 TexCoord;

struct LightInfo{
	vec4 position;
	vec3 intensity;
};

struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

uniform sampler2D Tex1; 
uniform sampler2D Tex2; 

uniform LightInfo Light;
uniform	MaterialInfo Material;

void phongModel(vec4 position, vec3 norm, out vec3 amb, out vec3 diff, out vec3 spec)
{
	vec3 tmp = vec3(0.9f, 0.5f, 0.3f);
	vec3 s = normalize(vec3(Light.position - position));
	vec3 v = normalize(-position.xyz);
	vec3 r = reflect(-s, norm);

	amb = Light.intensity * Material.Ka;
	float sDotN = max(dot(s, norm),0.0);
	diff = Light.intensity * Material.Kd * sDotN;
	spec = vec3(0.0);
	if(sDotN > 0.0)
		spec = Light.intensity *Material.Ks * pow( max( dot(r,v), 0.0 ),Material.Shininess );  
}

void main(void)
{
	vec3 amb,diff,spec;
	vec4 crateColor = texture(Tex1, TexCoord);
	vec4 mosColor = texture(Tex2, TexCoord);
	phongModel(Position, Normal, amb, diff, spec);
	
	vec4 texColor = mix(crateColor,mosColor,mosColor.a);
	//Render without light effect.
	gl_FragColor = (vec4( amb + diff, 1.0) * texColor) + vec4(spec, 1.0);

}
