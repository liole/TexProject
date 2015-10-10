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
//#include <random>
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
			class Empty;
			namespace Noise
			{
				class Simple;
				class Perlin;
				class Worley;
			}
		}
		namespace Filter
		{
			namespace Correction
			{
				class Grayscale;
				class Blur;
				class Function;
				class Mix;
			}
			namespace Physics
			{
				class HeightToNormal;
			}
		}
		namespace Viewer
		{
			class Simple;
			class BumpMapping;
		}
	}
#pragma endregion

	class ToolSet:
		public WindowBind
	{
		friend Tool;
		friend Tools::Generator::Empty;
		friend Tools::Generator::Noise::Simple;
		friend Tools::Generator::Noise::Perlin;
		friend Tools::Generator::Noise::Worley;
		friend Tools::Filter::Correction::Grayscale;
		friend Tools::Filter::Correction::Blur;
		friend Tools::Filter::Correction::Function;
		friend Tools::Filter::Correction::Mix;
		friend Tools::Filter::Physics::HeightToNormal;
		friend Tools::Viewer::Simple;
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
		GUI::Panels::Text*					panelConfigTitle = nullptr;
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
		struct SizerData
		{
			GUI::Panels::Default*	panelBase = nullptr;
			GUI::Buttons::Slider*	buttonSlider = nullptr;
			int32					minVal = 128;
			int32					maxVal = 1024;
			int32					val = 512;
		};
		GUI::Item*							CreateSizer(GUI* gui);

		struct SizerFloatData
		{
			GUI::Panels::Default*	panelBase = nullptr;
			GUI::Buttons::Slider*	buttonSlider = nullptr;
			float32					minVal = 128;
			float32					maxVal = 1024;
			float32					val = 512;
		};
		GUI::Item*							CreateFloatSizer(GUI* gui);

		namespace Generator
		{
			class Empty:
				public Tool
			{
			protected:
				GUI::Buttons::Connector*					buttonOutput = nullptr;
			protected:
				Texture::D2*								texture = new Texture::D2();
			public:
															Empty(ToolSet* toolSet_);
				virtual										~Empty() override;
			protected:
				void										Refresh();
			};
			namespace Noise
			{
				class Simple:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					GUI::Buttons::Trigger*						buttonConfigMonochrome = nullptr;
					GUI::Panels::Default*						panelConfigSizerX = nullptr;
					GUI::Panels::Default*						panelConfigSizerY = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
					bool										paramMonochrome = false;
					uvec2										paramSize = uvec2(128);
				public:
																Simple(ToolSet* toolSet_);
					virtual										~Simple() override;
				public:
					virtual void								FocusInit() override;
				protected:
					void										Refresh();
				};
				class Perlin:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonOutput = nullptr;
				protected:
					GUI::Panels::Default*						panelConfigSizerX = nullptr;
					GUI::Panels::Default*						panelConfigSizerY = nullptr;
					GUI::Panels::Default*						panelConfigBasisCount = nullptr;
					GUI::Panels::Default*						panelConfigNoiseSize = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
					uvec2										paramSize = uvec2(128);
					uint32										paramBasisCount = 16;
					float32										paramNoiseSize = 10.0f;
				public:
																Perlin(ToolSet* toolSet_);
					virtual										~Perlin() override;
				public:
					virtual void								FocusInit() override;
				protected:
					void										Refresh();
				};
				class Worley:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonOutput = nullptr;
					GUI::Panels::Default*						panelConfigSizerX = nullptr;
					GUI::Panels::Default*						panelConfigSizerY = nullptr;
					GUI::Panels::Default*						panelConfigCount = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				protected:
					uint32										paramDotsCount = 64;
					uvec2										paramSize = uvec2(128);
				public:
																Worley(ToolSet* toolSet_);
					virtual										~Worley() override;
				public:
					virtual void								FocusInit() override;
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
					GUI::Buttons::Connector*					buttonFieldInput = nullptr;
					GUI::Buttons::Connector*					buttonFieldOutput = nullptr;
					GUI::Panels::Default*						panelConfigSizer = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				protected:
					float32										paramRadius = 5.0f;
				public:
																Blur(ToolSet* toolSet_);
					virtual										~Blur() override;
				public:
					virtual void								FocusInit() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInput();
				};
				class Function:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonFieldInput = nullptr;
					GUI::Buttons::Connector*					buttonFieldOutput = nullptr;
					GUI::Panels::Default*						panelConfigAdd = nullptr;
					GUI::Panels::Default*						panelConfigMul = nullptr;
					GUI::Panels::Default*						panelConfigPow = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				protected:
					float32										paramAdd = 0.0f;
					float32										paramMul = 1.0f;
					float32										paramPow = 1.0f;
				public:
																Function(ToolSet* toolSet_);
					virtual										~Function() override;
				public:
					virtual void								FocusInit() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInput();
				};
				class Mix:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonFieldInputA = nullptr;
					GUI::Buttons::Connector*					buttonFieldInputB = nullptr;
					GUI::Buttons::Connector*					buttonFieldInputMix = nullptr;
					GUI::Buttons::Connector*					buttonFieldOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				public:
																Mix(ToolSet* toolSet_);
					virtual										~Mix() override;
				public:
					virtual void								FocusInit() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInputA();
					Texture::D2*								GetInputB();
					Texture::D2*								GetInputMix();
				};
			}
			namespace Physics
			{
				class HeightToNormal:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonFieldInput = nullptr;
					GUI::Buttons::Connector*					buttonFieldOutput = nullptr;
					GUI::Panels::Default*						panelConfigSizer = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				protected:
					float32										paramScaleFactor = 128.0f;
				public:
																HeightToNormal(ToolSet* toolSet_);
					virtual										~HeightToNormal() override;
				public:
					virtual void								FocusInit() override;
				protected:
					void										Refresh();
					Texture::D2*								GetInput();
				};
				class NormalsToSlopeFactor:
					public Tool
				{
				protected:
					GUI::Buttons::Connector*					buttonFieldInput = nullptr;
					GUI::Buttons::Connector*					buttonFieldOutput = nullptr;
				protected:
					Texture::D2*								texture = new Texture::D2();
				public:
																NormalsToSlopeFactor(ToolSet* toolSet_);
					virtual										~NormalsToSlopeFactor() override;
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
			class BumpMapping:
				public Tool
			{
			protected:
				static void									FuncWindowInit(Window* window);
				static void									FuncWindowFree(Window* window);
				static void									FuncWindowLoop(Window* window);
			protected:
				GUI::Buttons::Connector*					buttonFieldInputDiffuse = nullptr;
				GUI::Buttons::Connector*					buttonFieldInputNormals = nullptr;
			protected:
				Texture::D2*								textureDiffuse = new Texture::D2();
				Texture::D2*								textureNormals = new Texture::D2();
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
				OpenGL::Texture*							oglTextureDiffuse = nullptr;
				OpenGL::Texture*							oglTextureNormals = nullptr;
			public:
															BumpMapping(ToolSet* toolSet_);
				virtual										~BumpMapping() override;
			protected:
				void										Refresh();
				Texture::D2*								GetInputDiffuse();
				Texture::D2*								GetInputNormals();
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


















