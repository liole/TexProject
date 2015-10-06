#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

void main()
{

	gl_Position = vec4(-1,-1,1,1);
	EmitVertex();

	gl_Position = vec4(1,-1,1,1);
	EmitVertex();

	gl_Position = vec4(-1,1,1,1);
	EmitVertex();

	gl_Position = vec4(1,1,1,1);
	EmitVertex();

    EndPrimitive();
}

