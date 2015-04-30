#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
//#include <TexProject/TexProject_Helpers.h>
//#include <TexProject/TexProject_OpenGL.h>
//#include <TexProject/TexProject_Shaders.h>
//#include <TexProject/TexProject_Textures.h>


#include<list>


namespace TexProject
{
	namespace Interface
	{
		typedef Window::Render*				PWindow;


		struct Basic;						// Базовий клас інтерфейсу
		struct Default;						// Інтерфейс засобами ОС
		struct OpenGL;						// Інтерфейс з підтримкою OpenGL
		struct DirectX;						// Інтерфейс з підтримкою DirectX
		struct Mantle;						// Інтерфейс з підтримкою MantleAPI
		struct Vulkan;						// Інтерфейс з підтримкою VulkanAPI

		typedef Interface::Basic			GUI;


		struct Creator
		{
			friend Window::RenderContext::Default;
		protected:
			template <typename T>
			static inline T*				CreateInterface(PWindow window_);
			static inline void				DeleteInterface(GUI* interface_);
		};


		struct Item;						// Базовий клас елемента інтерфейсу
		namespace Panel						// Панелі
		{
			struct Basic;					// Базовий
			struct Default;					// Звичайна
			struct Image;					// Зображення
		}
		namespace Button					// Кнопки
		{
			struct Basic;					// Базовий
			struct Default;					// Звичайна
			struct Trigger;					// Перемикач
			struct Action;					// З дією
			struct Slider;					// Повзунок
		}


		typedef Item						GUIItem;
		typedef Panel::Basic				GUIPanel;
		typedef Panel::Default				GUIPanelDefault;
		typedef Button::Basic				GUIButton;
		typedef Button::Default				GUIButtonDefault;
		typedef Button::Trigger				GUIButtonTrigger;
		typedef Button::Action				GUIButtonAction;
		typedef Button::Default				GUIButtonSlider;


		struct Item
		{
			friend Interface::Basic;
			friend Interface::Default;
		protected:
			template <typename T>
			static T*				CreateItem(GUI* interface_);
			static inline void		DeleteItem(GUIItem* item_);


			GUI * const				inter = nullptr;

									Item(GUI* interface_);
									Item(const Item&) = delete;
									Item(Item&&) = delete;
			virtual					~Item() = default;

			Item&					operator = (const Item&) = delete;
			Item&					operator = (Item&&) = delete;

			virtual void			Create();
			virtual void			Delete();
			virtual void			Loop();
		};
		namespace Panel
		{
			struct Basic: public Item
			{
				friend Item;
				friend Interface::Basic;
			protected:
				Panel::Basic*								parent = nullptr;
				std::list<Panel::Basic*>					panel;
				std::list<Button::Basic*>					button;

										Basic(GUI* interface_);
										Basic(const Basic&) = delete;
										Basic(Basic&&) = delete;
				virtual					~Basic() = default;

				Basic&					operator = (const Basic&) = delete;
				Basic&					operator = (Basic&&) = delete;

				virtual void			Create() override;
				virtual void			Delete() override;
				virtual void			Loop() override;
			};
			struct Default: public Panel::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:
										Default(GUI* interface_);
				/*						Default(const Basic&) = delete;
										Default(Default&&) = delete;
				virtual					~Default() = default;

				Default&				operator = (const Default&) = delete;
				Default&				operator = (Default&&) = delete;

				virtual void			Create() override;
				virtual void			Delete() override;
				virtual void			Loop() override;*/
			};
		}
		namespace Button
		{
			struct Basic: public Item
			{
				friend Item;
				friend Interface::Basic;
			protected:
				Panel::Basic*			parent = nullptr;

										Basic(GUI* interface_);
										Basic(const Basic&) = delete;
										Basic(Basic&&) = delete;
				virtual					~Basic() = default;

				Basic&					operator = (const Basic&) = delete;
				Basic&					operator = (Basic&&) = delete;

				virtual void			Create() override;
				virtual void			Delete() override;
				virtual void			Loop() override;
			};
			struct Default: public Button::Basic
			{
			};
			struct Trigger: public Button::Basic
			{
			};
			struct Action: public Button::Basic
			{
			};
			struct Slider: public Button::Basic
			{
			};
		}


		struct Basic
		{
			friend Creator;
		protected:

			template <typename T>
			static T*						CreateInterface(PWindow window_);
			static inline void				DeleteInterface(GUI* interface_);


			PWindow							window = nullptr;
			std::list<Panel::Basic*>		panel;
			std::list<Button::Basic*>		button;

											Basic(PWindow window_);
											Basic(const Basic&) = delete;
											Basic(Basic&&) = delete;
			virtual							~Basic() = default;

			Basic&							operator = (const Basic&) = delete;
			Basic&							operator = (Basic&&) = delete;

			template <typename T>
			T*													AddPanel();
			template <typename T>
			T*													AddButton();

		public:

			virtual void										Create();
			virtual void										Delete();
			virtual void										Loop();

			virtual GUIPanelDefault*							AddPanelDefault();
			virtual GUIButtonDefault*							AddButtonDefault();
			virtual GUIButtonTrigger*							AddButtonTrigger();
			virtual GUIButtonAction*							AddButtonAction();
			virtual GUIButtonSlider*							AddButtonSlider();

			inline void											RemovePanel(GUIPanel* source);
			inline void											RemoveButton(GUIButton* source);

			inline PWindow										GetWindow()
			{
				return window;
			}
		};

#if __TEXPROJECT_WIN__
		struct Default: public Interface::Basic
		{
			friend Creator;
		protected:

			HDC								deviceContextHandle = NULL;

											Default(PWindow window_);
											Default(const Default&) = delete;
											Default(Default&&) = delete;
			virtual							~Default() = default;

			Default&						operator = (const Default&) = delete;
			Default&						operator = (Default&&) = delete;

			struct Panel
			{
				struct Default: public Interface::Panel::Default
				{
				protected:
				public:
											Default(GUI* interface_);
											~Default() = default;

					virtual void			Create() override;
					virtual void			Delete() override;
					virtual void			Loop() override;
				};
			};

		public:

			virtual void										Create() override;
			virtual void										Delete() override;
			virtual void										Loop() override;

			virtual GUIPanelDefault*							AddPanelDefault() override;
			virtual GUIButtonDefault*							AddButtonDefault() override;
			virtual GUIButtonTrigger*							AddButtonTrigger() override;
			virtual GUIButtonAction*							AddButtonAction() override;
			virtual GUIButtonSlider*							AddButtonSlider() override;

			/*struct Button: public Interface::Basic::Button
			{
			};*/
		};
#endif
	}
}


// Interface::Creator
template <typename T>
typename T*									TexProject::Interface::Creator::CreateInterface(PWindow window_)
{
	auto t = new T(window_);
	t->Create();
	return t;
}
void										TexProject::Interface::Creator::DeleteInterface(GUI* interface_)
{
	interface_->Delete();
	delete interface_;
}



// Interface::Basic::Item
template <typename T>
typename T*									TexProject::Interface::Item::CreateItem(GUI* interface_)
{
	auto t = new T(interface_);
	t->Create();
	return t;
}
void										TexProject::Interface::Item::DeleteItem(GUIItem* item_)
{
	item_->Delete();
	delete item_;
}


// Interface::Basic
template <typename T>
typename T*									TexProject::Interface::Basic::CreateInterface(PWindow window_)
{
	auto t = new T(window_);
	t->Create();
	return t;
}
void										TexProject::Interface::Basic::DeleteInterface(GUI* interface_)
{
	if(interface_)
	{
		interface_->Delete();
		delete interface_;
	}
}

template <typename T>
typename T*									TexProject::Interface::Basic::AddPanel()
{
	auto t = Interface::Item::CreateItem<T>(this);
	panel.push_back(t);
	return t;
}
template <typename T>
typename T*									TexProject::Interface::Basic::AddButton()
{
	auto t = Interface::Basic::CreateItem<T>();
	button.push_back(t);
	return t;
}
void										TexProject::Interface::Basic::RemovePanel(GUIPanel* source)
{
	for(auto i = panel.begin(); i != panel.end(); ++i)
	{
		auto t = *i;
		if(t == source)
		{
			Item::DeleteItem((Item*)t);
			i = panel.erase(i);
		}
	}
}
void										TexProject::Interface::Basic::RemoveButton(GUIButton* source)
{
	for(auto i = button.begin(); i != button.end(); ++i)
	{
		auto t = *i;
		if(t == source)
		{
			Item::DeleteItem((Item*)t);
			i = button.erase(i);
		}
	}
}


// Interface::Basic


