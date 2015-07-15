#version 330 core


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


out vec2	P_Tex;


void main()
{

	gl_Position = vec4(-1,-1,0,1);
	P_Tex = vec2(0,0);
	EmitVertex();

	gl_Position = vec4(1,-1,0,1);
	P_Tex = vec2(1,0);
	EmitVertex();

	gl_Position = vec4(-1,1,0,1);
	P_Tex = vec2(0,1);
	EmitVertex();

	gl_Position = vec4(1,1,0,1);
	P_Tex = vec2(1,1);
	EmitVertex();

    EndPrimitive();
}

