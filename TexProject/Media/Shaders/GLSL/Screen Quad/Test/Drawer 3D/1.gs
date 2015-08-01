#version 330 core


uniform float stage;


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


out vec3	P_Tex;


void main()
{

	gl_Position = vec4(-1,-1,0,1);
	P_Tex = vec3(0,0,stage);
	EmitVertex();

	gl_Position = vec4(1,-1,0,1);
	P_Tex = vec3(1,0,stage);
	EmitVertex();

	gl_Position = vec4(-1,1,0,1);
	P_Tex = vec3(0,1,stage);
	EmitVertex();

	gl_Position = vec4(1,1,0,1);
	P_Tex = vec3(1,1,stage);
	EmitVertex();

    EndPrimitive();
}

