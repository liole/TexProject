#version 330 core


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


out float	P_Tex;


void main()
{

	gl_Position = vec4(-1,-1,0,1);
	P_Tex = 0.0f;
	EmitVertex();

	gl_Position = vec4(1,-1,0,1);
	P_Tex = 1.0f;
	EmitVertex();

	gl_Position = vec4(-1,1,0,1);
	P_Tex = 0.0f;
	EmitVertex();

	gl_Position = vec4(1,1,0,1);
	P_Tex = 1.0f;
	EmitVertex();

    EndPrimitive();
}

