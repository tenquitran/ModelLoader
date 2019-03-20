#version 440 core
#pragma debug(on)
#pragma optimize(off)

uniform sampler2D texDiffuse;

in vec3 texCoord;

out vec4 outColor;

void main()
{
	// TODO: for now, use only two texture coordinate component
	outColor = texture(texDiffuse, texCoord.xy);
	//outColor = texture(texDiffuse, texCoord);

	//outColor = vec4(0.0f, 0.2f, 0.8f, 1.0f);
}
