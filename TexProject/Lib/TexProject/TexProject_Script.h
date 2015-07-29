#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Textures.h>


#include <vector>


#include <TexProject/TexProject_Script_Lexer.h>
#include <TexProject/TexProject_Script_Parser.h>
#include <TexProject/TexProject_Script_Checker.h>
#include <TexProject/TexProject_Script_Translator.h>


namespace TexProject
{
	struct Script
	{
	public:
		struct Input
		{
			enum class variableType
			{
				Bool,
				Int,UInt,
				Float,
				Vec2,IVec2,
				Vec3,IVec3,
				Vec4,IVec4,
				Mat2,Mat3,Mat4
			};

			struct Tex
			{
				Texture::Type	type;
				void*			location;

				Tex() = default;
				Tex(Texture::Type type_,void* location_):
					type(type_),location(location_)
				{
				}
			};
			struct Var
			{
				variableType	type;
				void*			location;

				Var() = default;
				Var(variableType type_,void* location_):
					type(type_),location(location_)
				{
				}
			};

			std::vector<Tex>				input;

			uvec3							outputSize;
			Texture::Type					outputType;
			std::vector<void*>				output;

			std::vector<Var>				varConst;
			std::vector<Var>				varExtern;
		};
		struct Output
		{
			Texture::Type					type;
			std::vector<void*>				texture;

			void* operator [] (uint32 i)
			{
				return texture[i];
			}
		};
		
	protected:

		struct Computer
		{
		public:
			struct Input
			{
				uint32	*x,*y,*z,*w,*face;		// дискретні текстурні координати
				float32	*dx,*dy,*dz,*dw;		// уніфіковані текстурні коориднати
				void**	valConst = nullptr;		// масив констант
				void**	valExtern = nullptr;	// масив зовнішніх залежностей
				void**	input = nullptr;		// масив вхідних текстур
				void**	output = nullptr;		// масив вихідних vec4
			};

			Input		input;
			void 		(*func)() = nullptr;
		};

		Input								input;
		Translator							translator;
		Computer							computer;

	public:

		inline void							AddInput(Texture::D1 tex)
		{
			input.input.push_back(Input::Tex(Texture::Type::D1,&tex));
		}
		inline void							AddInput(Texture::D2 tex)
		{
			input.input.push_back(Input::Tex(Texture::Type::D2,&tex));
		}
		inline void							AddInput(Texture::D3 tex)
		{
			input.input.push_back(Input::Tex(Texture::Type::D3,&tex));
		}
		inline void							AddInput(Texture::Cube tex)
		{
			input.input.push_back(Input::Tex(Texture::Type::Cube,&tex));
		}
		inline void							SetOutput(Texture::Type type,uvec3 size,uint32 count)
		{
			input.outputType = type;
			input.outputSize = size;

			for(uint32 i = 0; i < count; ++i)
			{
				switch(type)
				{
				case TexProject::Texture::Type::D1:
					input.output.push_back(new Texture::D1);
					//((Texture::D1*)input.output[i]);
				break;
				case TexProject::Texture::Type::D2:
					input.output.push_back(new Texture::D2);
					((Texture::D2*)input.output[i])->Create(size.xy());
				break;
				case TexProject::Texture::Type::D3:
					input.output.push_back(new Texture::D3);
					//((Texture::D3*)input.output[i]);
				break;
				case TexProject::Texture::Type::Cube:
					input.output.push_back(new Texture::Cube);
					((Texture::Cube*)input.output[i])->Create(size.x);
				break;
				}
			}
		}

		Output								Run();
		void								Compile();
	};
};





















