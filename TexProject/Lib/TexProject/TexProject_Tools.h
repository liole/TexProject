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
			virtual								~Basic();

			virtual void						Loop();
			virtual void						Refresh();
			virtual bool						IsClean();		// Is object ready to be deleted?
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

					bool										generationFlag = false;
					volatile std::atomic<bool>					generationFinish = false;
					std::thread									generationThread;
					Texture::D2*								generationTexture = nullptr;

					Texture::D2*								texture = nullptr;

					Blank(Window::Render* window_);
					~Blank();

					virtual void								Loop() override;
					virtual void								Refresh() override;
					virtual bool								IsClean() override;
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



		template<typename T>
		static T*							Add(Window::Render* window);
		static inline void					Remove(Basic* source);

		static void Init();
		static void Free();
		static void Loop();
	};
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
		tool.erase(source->iter); source->iter = tool.end();
		clean.push_back(source);
		//delete source;
	}
}























