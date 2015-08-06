#pragma once
#include <TexProject/TexProject_Header.h>
#include <TexProject/TexProject_Textures.h>
#include <TexProject/TexProject_Interface.h>

#include <TexProject/TexProject_Geometry.h>
#include <TexProject/TexProject_Shaders.h>
#include <TexProject/TexProject_Buffers.h>

#include <list>
#include <iterator>

#include <atomic>
#include <thread>


namespace TexProject
{
	class Tool
	{
	protected:

		struct Destruction {};

		struct Basic
		{
			friend Tool;
		protected:
			struct OutputData
			{
				Basic*						tool = nullptr;
				Texture::Type				textureType = Texture::Type::D2;
				void*						texture = nullptr;

				inline OutputData(Basic* tool_,Texture::Type texType_,void* tex_):
					tool(tool_),
					textureType(texType_),
					texture(tex_)
				{
				}
			};

			TexProject::Window::Render*const					window;
			std::list<Basic*>::iterator							iter;
			bool												destruction = false;

			Basic(Window::Render* window_);
			virtual							~Basic();

			virtual void					Loop();
			virtual void					Refresh();
			virtual bool					IsClean();		// Is object ready to be deleted?

			inline void						FlushFocus();
			virtual void					InitFocus(Interface::Panel::Default* panel);
			virtual void					FreeFocus(Interface::Panel::Default* panel);
		};
		struct D2:
			public Basic
		{
			friend Tool;
		protected:

			D2(Window::Render* window_):
				Basic(window_)
			{
			}
		};


		static std::list<Basic*>			tool;
		static std::list<Basic*>			clean;

		static vec2							panAnchor;

		static Window::Render*				window;
		static Interface::Panel::Default*	panelConfig;
		static Interface::Panel::Default*	panelTools;

		static Basic*						focus;

	public:


		struct Generator
		{
			friend Tool;
		public:

			struct D2
			{
				friend Tool;
			public:

				struct Blank:
					private Tool::D2
				{
					friend Tool;
				private:
					Interface::Panel::Default*					panelBase = nullptr;
					Interface::Panel::Text*						panelTitle = nullptr;
					Interface::Panel::Image*					panelImage = nullptr;
					Interface::Button::Default*					buttonRefresh = nullptr;
					Interface::Button::Connector*				buttonConnectorOut = nullptr;
					Interface::Button::Default*					buttonClose = nullptr;

					Interface::Panel::Default*					focusPanel = nullptr;
					Interface::Panel::Default*					focusPanelSizeX = nullptr;
					Interface::Panel::Default*					focusPanelSizeY = nullptr;
					Interface::Panel::Text*						focusPanelSizeXText = nullptr;
					Interface::Panel::Text*						focusPanelSizeYText = nullptr;
					Interface::Button::Default*					focusButtonRefresh = nullptr;
					Interface::Button::Slider*					focusButtonSliderColorRed = nullptr;
					Interface::Button::Slider*					focusButtonSliderColorGreen = nullptr;
					Interface::Button::Slider*					focusButtonSliderColorBlue = nullptr;
					Interface::Button::Slider*					focusButtonSliderColorAlpha = nullptr;

					uvec2										generationSize;
					vec4										generationColor;
					bool										generationFlag = false;
					volatile std::atomic<bool>					generationFinish = false;
					std::thread									generationThread;
					Texture::D2*								generationTexture = nullptr;

					uvec2										size = uvec2(128,128);
					vec4										color = vec4(1.0f,0.5f,0.0f,1.0f);
					Texture::D2*								texture = nullptr;

					Blank(Window::Render* window_);
					~Blank();

					virtual void								Loop() override;
					virtual void								Refresh() override;
					virtual bool								IsClean() override;

					virtual void								InitFocus(Interface::Panel::Default* panel) override;
					virtual void								FreeFocus(Interface::Panel::Default* panel) override;
				};

				struct Noise
				{
					friend Tool;
				public:

					struct Simple:
						private Tool::D2
					{
						friend Tool;
					private:
						Interface::Panel::Default*					panelBase = nullptr;
						Interface::Panel::Text*						panelTitle = nullptr;
						Interface::Panel::Image*					panelImage = nullptr;
						Interface::Button::Default*					buttonRefresh = nullptr;
						Interface::Button::Connector*				buttonConnectorOut = nullptr;
						Interface::Button::Default*					buttonClose = nullptr;

						Interface::Panel::Default*					focusPanel = nullptr;
						Interface::Panel::Default*					focusPanelSizeX = nullptr;
						Interface::Panel::Default*					focusPanelSizeY = nullptr;
						Interface::Panel::Text*						focusPanelSizeXText = nullptr;
						Interface::Panel::Text*						focusPanelSizeYText = nullptr;
						Interface::Button::Default*					focusButtonRefresh = nullptr;

						uvec2										size = uvec2(128,128);
						Texture::D2*								texture = nullptr;

						Simple(Window::Render* window_);
						~Simple();

						virtual void								Loop() override;
						virtual void								Refresh() override;
						//virtual bool								IsClean() override;

						virtual void								InitFocus(Interface::Panel::Default* panel) override;
						virtual void								FreeFocus(Interface::Panel::Default* panel) override;
					};
					struct Perlin:
						private Tool::D2
					{
					};
					struct Worley:
						private Tool::D2
					{
						friend Tool;
					private:
						Interface::Panel::Default*					panelBase = nullptr;
						Interface::Panel::Text*						panelTitle = nullptr;
						Interface::Panel::Image*					panelImage = nullptr;
						Interface::Button::Default*					buttonRefresh = nullptr;
						Interface::Button::Connector*				buttonConnectorOut = nullptr;
						Interface::Button::Default*					buttonClose = nullptr;

						Interface::Panel::Default*					focusPanel = nullptr;
						Interface::Panel::Default*					focusPanelSizeX = nullptr;
						Interface::Panel::Default*					focusPanelSizeY = nullptr;
						Interface::Panel::Text*						focusPanelSizeXText = nullptr;
						Interface::Panel::Text*						focusPanelSizeYText = nullptr;
						Interface::Button::Default*					focusButtonRefresh = nullptr;
						Interface::Button::Slider*					focusButtonSliderDotsNumber = nullptr;

						uvec2										generationSize;
						uint32										generationDotsNumber;
						bool										generationFlag = false;
						volatile std::atomic<bool>					generationFinish = false;
						std::thread									generationThread;
						Texture::D2*								generationTexture = nullptr;

						uint32										DotsNumber = 50;
						uvec2										size = uvec2(128, 128);
						Texture::D2*								texture = nullptr;

						Worley(Window::Render* window_);
						~Worley(){}

						
						virtual void								Loop() override;
						virtual void								Refresh() override;
						//virtual bool								IsClean() override;

						virtual void								InitFocus(Interface::Panel::Default* panel) override;
						virtual void								FreeFocus(Interface::Panel::Default* panel) override;
					};
					struct Simplex:
						private Tool::D2
					{
					};
				};
			};
		};
		struct Filter
		{
			friend Tool;
		public:

			struct D2
			{
				friend Tool;
			public:

				struct NormalsGenerator:
					private Tool::D2
				{
				};
				struct OcclusionGenerator:
					private Tool::D2
				{
				};

				struct Correction:
					public Tool::D2
				{
					friend Tool;
				public:

					struct Grayscale:
						private Tool::D2
					{
						friend Tool;
					private:
						Interface::Panel::Default*				panelBase = nullptr;
						Interface::Panel::Text*					panelTitle = nullptr;
						Interface::Panel::Image*				panelImage = nullptr;
						Interface::Button::Default*				buttonRefresh = nullptr;
						Interface::Button::Connector*			buttonConnectorIn = nullptr;
						Interface::Button::Connector*			buttonConnectorOut = nullptr;
						Interface::Button::Default*				buttonClose = nullptr;

						Texture::D2*							texture = nullptr;

						Texture::D2*							GetInput();

						Grayscale(Window::Render* window_);
						~Grayscale();

						virtual void							Loop() override;
						virtual void							Refresh() override;
					};
					struct Color:
						private Tool::D2
					{
						friend Tool;
					private:
						Interface::Panel::Default*				panelBase = nullptr;
						Interface::Panel::Text*					panelTitle = nullptr;
						Interface::Panel::Image*				panelImage = nullptr;
						Interface::Button::Default*				buttonRefresh = nullptr;
						Interface::Button::Connector*			buttonConnectorIn = nullptr;
						Interface::Button::Connector*			buttonConnectorOut = nullptr;
						Interface::Button::Default*				buttonClose = nullptr;

						bool									generationFlag = false;
						volatile std::atomic<bool>				generationFinish = false;
						std::thread								generationThread;
						Texture::D2*							generationInputTexture = nullptr;
						Texture::D2*							generationTexture = nullptr;

						Texture::D2*							texture = nullptr;

						Texture::D2*							GetInput();

						Color(Window::Render* window_);
						~Color();

						virtual void							Loop() override;
						virtual void							Refresh() override;
						virtual bool							IsClean() override;
					};
					struct Blur:
						private Tool::D2
					{
					};
				};
			};
		};
		struct Viewer
		{
			friend Tool;
		public:
			struct Default:
				private Tool::Basic
			{
				friend Tool;
			protected:

				enum class PrimitiveType
				{
					Box,
					Sphere,
					Cylinder
				};

				static void										funcWindowInit(Window::Render* window);
				static void										funcWindowFree(Window::Render* window);
				static void										funcWindowLoop(Window::Render* window);

				Interface::Panel::Default*						panelBase = nullptr;
				Interface::Panel::Text*							panelTitle = nullptr;
				Interface::Panel::Image*						panelImage = nullptr;
				Interface::Button::Default*						buttonRefresh = nullptr;
				Interface::Button::Connector*					buttonConnectorIn = nullptr;
				Interface::Button::Default*						buttonClose = nullptr;

				Interface::Panel::Default*						focusPanel = nullptr;
				Interface::Button::Switcher*					focusButtonPrimitiveSwitcher = nullptr;
				Interface::Panel::Text*							focusPanelPrimitiveText[3];

				PrimitiveType									currentPrimitiveType = PrimitiveType::Box;
				PrimitiveType									primitiveType = PrimitiveType::Box;
				bool											oWindowActive = false;
				ivec2											oMousePos = ivec2(0);
				vec3											viewAng = vec3(0.0f);
				float32											viewDist = 3.0f;
				Helper::VMat									vMat;
				Helper::MMat									mMat;

				Window::Render*									renderWindow = nullptr;

				OpenGL::Shader*									skyGLShader = nullptr;
				OpenGL::Shader*									renderGLShader = nullptr;
				OpenGL::Model*									renderGLModel = nullptr;
				OpenGL::Texture*								renderGLTextureDiffuse = nullptr;
				OpenGL::Texture*								renderGLTextureNormals = nullptr;
				OpenGL::Texture*								renderGLTextureMaterial = nullptr;
				OpenGL::Texture*								renderGLTextureEnvironment = nullptr;

				Texture::D2*									GetInput();

			public:
											Default(Window::Render* window_);
				virtual						~Default();

				virtual void									Loop() override;
				virtual void									Refresh() override;
				//virtual bool									IsClean() override;

				virtual void									InitFocus(Interface::Panel::Default* panel) override;
				virtual void									FreeFocus(Interface::Panel::Default* panel) override;
			};
		};


		static void							SetFocus(Basic* source);
		static void							UnsetFocus(Basic* source);

		template<typename T>
		static T*							Add(Window::Render* window);
		static inline void					Remove(Basic* source);

		static void Init(Window::Render* window_);
		static void Free();
		static void Loop();

		static inline vec2					GetAnchor()
		{
			return panAnchor;
		}
	};
}


// Tool::Basic
inline void									TexProject::Tool::Basic::FlushFocus()
{
	UnsetFocus(this);	//if(focus == this) focus = nullptr;
}


template<typename T>
typename T*				TexProject::Tool::Add(Window::Render* window)
{
	auto result = new T(window);
	result->iter = tool.insert(tool.begin(),result);
	return result;
}
inline void				TexProject::Tool::Remove(TexProject::Tool::Basic* source)
{
	if(source && source->iter != tool.end())
	{
		source->FlushFocus();
		tool.erase(source->iter); source->iter = tool.end();
		clean.push_back(source);
		//delete source;
	}
}























