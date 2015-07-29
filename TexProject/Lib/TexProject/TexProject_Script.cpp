#include "TexProject_Script.h"
using namespace TexProject;


TexProject::Script::Output					TexProject::Script::Run()
{
	uint32 x,y,z,w,face;
	float32 dx,dy,dz,dw;

	computer.input.x = &x;
	computer.input.y = &y;
	computer.input.z = &z;
	computer.input.w = &w;
	computer.input.dx = &dx;
	computer.input.dy = &dy;
	computer.input.dz = &dz;
	computer.input.dw = &dw;
	computer.input.face = &face;

	auto color = new vec4[input.output.size()];

	switch(input.outputType)
	{
	case Texture::Type::D2:
	{
		for(x = 0; x < input.outputSize.x; ++x)
		{
			dx = float32(x)/float32(input.outputSize.x);
			for(y = 0; y < input.outputSize.y; ++y)
			{
				dy = float32(y)/float32(input.outputSize.y);

				for(uint32 i = 0; i < input.output.size(); ++i)
				{
					computer.input.output[i] = &color[i];
				}

				computer.func();

				for(uint32 i = 0; i < input.output.size(); ++i)
				{
					((Texture::D2*)input.output[i])->SetPixel(uvec2(x,y),color[i]);
				}
			}
		}
	}
	break;
	}

	delete[] color;

	Output output;

	output.type = input.outputType;
	for(uint32 i = 0; i < input.output.size(); ++i)
	{
		output.texture.push_back(input.output[i]);
	}

	return output;
}
void										TexProject::Script::Compile()
{
	computer.input.input = new void*[input.input.size()];
	for(uint32 i = 0; i < input.input.size(); ++i)
	{
		computer.input.input[i] = input.input[i].location;
	}

	// array of pointers to output vec4 at runtime
	computer.input.output = new void*[input.output.size()];
	for(uint32 i = 0; i < input.output.size(); ++i)
	{
		computer.input.output[i] = nullptr;//input.output[i];
	}

	auto varFace	= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Int,&computer.input.face);

	auto varX		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Int,&computer.input.x);
	auto varY		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Int,&computer.input.y);
	auto varZ		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Int,&computer.input.z);
	auto varW		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Int,&computer.input.w);

	auto varDX		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Float,&computer.input.dx);
	auto varDY		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Float,&computer.input.dy);
	auto varDZ		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Float,&computer.input.dz);
	auto varDW		= new Instructions::Expressions::Storages::In(Instructions::Expressions::Storage::Type::Float,&computer.input.dw);

	auto root = new Instructions::Block;

	auto lit1 = new Instructions::Expressions::Storages::Literal(Instructions::Expressions::Storage::Type::Vec4,new vec4);
	*((vec4*)lit1->value) = vec4(0.0f,1.0f,0.0,1.0f);

	auto out1 = new Instructions::Expressions::Storages::Out(Instructions::Expressions::Storage::Type::Texture2D,&computer.input.output[0]);

	auto asg1 = new Instructions::Expressions::Operators::Binary::Assignment(out1,lit1);

	root->content = std::vector<Instruction*>
	{
		asg1
	};

	auto code = translator.TranslateToASM86(root);

	auto data = (uint8*)VirtualAlloc(NULL,code.size(),MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	for(uint32 i = 0; i < code.size(); ++i) data[i] = code[i];
		
	computer.func = reinterpret_cast<void(*)()>(data);
}































