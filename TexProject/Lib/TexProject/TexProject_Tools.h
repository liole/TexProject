#pragma once
#include <TexProject/TexProject_Header.h>
#include <TexProject/TexProject_Textures.h>
#include <TexProject/TexProject_Interface.h>


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


		static std::list<Basic*> tool;
		static std::list<Basic*> clean;

		static Window::Render*				window;
		static Interface::Panel::Default*	panelConfig;

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

				struct Correction
				{
					friend Tool;
				public:

					struct Color:
						private Tool::D2
					{
						friend Tool;
					private:
						Interface::Panel::Default*				panelBase = nullptr;
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
				};
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























