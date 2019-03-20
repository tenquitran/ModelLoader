#version 440 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 texCoordIn;

layout(location = 0) uniform mat4 MVP;
//layout(location = 1) uniform mat4 ModelView;
//layout(location = 2) uniform mat3 Normal;

out vec3 texCoord;

void main(void) 
{
	//gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	gl_Position = MVP * vec4(pos, 1.0);

	texCoord = texCoordIn;
}
