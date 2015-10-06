#pragma once
#pragma region TexProject Includes
#include <TexProject/TexProject_Header.h>
#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Windows.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>
#include <TexProject/TexProject_GUI.h>
#include <TexProject/TexProject_Textures.h>
#include <TexProject/TexProject_OpenGL.h>
#pragma endregion
#pragma region Includes
#pragma endregion


#pragma region
#pragma endregion


namespace TexProject
{
#pragma region Declaration
	class Tool;
	class ToolSet;
	namespace Tools
	{
		namespace Generator
		{
			namespace Noise
			{
				class Simple;
				class Worley;
			}
		}
		namespace Filter
		{
			namespace Correction
			{
				class Grayscale;
				class Blur;
			}
			class HeightToNormal;
		}
		namespace Viewer
		{
			class Simple;
		}
	}
#pragma endregion

	class ToolSet:
		public WindowBind
	{
		friend Tool;
	protected:
		Tool*								focus = nullptr;
	protected:
		void								FocusSet(Tool* tool);
	protected:
		GUI::Panels::Default*				panelConfig = nullptr;
		GUI::Panels::Default*				panelTools = nullptr;
	protected:
		std::list<Tool*>					tool;
		vec2								anchor = vec2(0.0f);
		vec2								oMouse = vec2(0.0f),nMouse = vec2(0.0f);
	public:
											ToolSet(Window* window_);
											~ToolSet();
	public:
		void								Loop();
	};
	class ToolSetBind
	{
	protected:
		ToolSet*const						toolSet;
	public:
											ToolSetBind(ToolSet* toolSet_);
	public:
		inline ToolSet*						GetToolSet() const;
	};
	class Tool:
		public ToolSetBind
	{
		friend ToolSet;
	protected:
		class Destruction
		{

		};
		class OutputData
		{
		public:
			enum class Type
			{
				None,
				Texture1D,
				Texture2D,
				Texture3D,
				TextureCube
			};
		public:
			Type							type;
			void*							data;
		};
	protected:
		GUI::Panels::Default*				panelFieldBase = nullptr;
		GUI::Panels::Text*					panelFieldTitle = nullptr;
		GUI::Panels::Image*					panelFieldImage = nullptr;
		GUI::Buttons::Default*				buttonFieldRefresh = nullptr;
	protected:
		GUI::Panels::Default*				panelConfigBase = nullptr;
	public:
											Tool(ToolSet* toolSet_);
		virtual								~Tool();
	public:
		virtual void						Loop();
		virtual void						FocusInit();
		virtual void						FocusFree();
	};
	namespace Tools
	{
		namespace Generator
		{
			namespace Noise
			{
				class Simple:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				public:
																Simple(ToolSet* toolSet_);
					virtual										~Simple() override;
				protected:
					void										Refresh();
				};
				class Worley:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
					uint32										generationDotsNumber = 64;
				public:
																Worley(ToolSet* toolSet_);
					virtual										~Worley() override;
				protected:
					void										Refresh();
				};
			}
		}
		namespace Filter
		{
			namespace Correction
			{
				class Grayscale:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonInput = nullptr;
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				public:
																Grayscale(ToolSet* toolSet_);
					virtual										~Grayscale() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInput();
				};
				class Blur:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonInput = nullptr;
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				public:
																Blur(ToolSet* toolSet_);
					virtual										~Blur() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInput();
				};
			}			
			namespace Physics
			{
				class HeightToNormal:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonInput = nullptr;
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				public:
																HeightToNormal(ToolSet* toolSet_);
					virtual										~HeightToNormal() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInput();
				};
			}
		}
		namespace Viewer
		{
			class Simple:
				public Tool
			{
			protected:
				static void									FuncWindowInit(Window* window);
				static void									FuncWindowFree(Window* window);
				static void									FuncWindowLoop(Window* window);
			protected:
				GUI::Buttons::Connector*					buttonInput = nullptr;
			protected:
				Texture::D2*								texture = new Texture::D2();
				Texture::D2*								texturePreview = new Texture::D2();
			protected:
				Helper::VPMat								vpMat;
				Helper::MMat								mMat;
			protected:
				Window*										windowRender = new Window;
			protected:
				Geometry::Mesh*								mesh = new Geometry::Mesh;
			protected:
				OpenGL::Shader*								oglShader = nullptr;
				OpenGL::Mesh*								oglMesh = nullptr;
				OpenGL::Texture*							oglTexture = nullptr;
			public:
															Simple(ToolSet* toolSet_);
				virtual										~Simple() override;
			protected:
				void										Refresh();
				Texture::D2*								GetInput();
			};
		}
	}
}


#pragma region ToolSetBind
inline TexProject::ToolSet*					TexProject::ToolSetBind::GetToolSet() const
{
	return toolSet;
}
#pragma endregion


















