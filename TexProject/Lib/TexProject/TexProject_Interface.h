#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>
//#include <TexProject/TexProject_OpenGL.h>
//#include <TexProject/TexProject_Shaders.h>
//#include <TexProject/TexProject_Textures.h>


#include<list>
#include<vector>


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


		struct Item:
			public TexProject::Helper::Prio,
			public TexProject::Helper::Pos2,
			public TexProject::Helper::Size2
		{
			friend Interface::Basic;
			friend Interface::Default;
		protected:
			template <typename T>
			static T*				CreateItem(GUI* interface_);
			static inline void		DeleteItem(GUIItem* item_);


			GUI * const				inter = nullptr;
			std::list<Item**>		pointer;

									Item(GUI* interface_);
									Item(const Item&) = delete;
									Item(Item&&) = delete;
			virtual					~Item();

			Item&					operator = (const Item&) = delete;
			Item&					operator = (Item&&) = delete;

			virtual void			Create();
			virtual void			Delete();
			virtual void			Loop();

			/*Методи, специфічні для ОС Windows*/
#if __TEXPROJECT_WIN__
			/*
			Цю функцію інтерфейс буде викликати при обробці повідомлення WM_PAINT зі своєї _win_WMPaint
			Параметр hDC, який приходить в інтерфейс з вікна - зберігатимемо у внутрішніх полях, для економії аргументів
			*/
			virtual void									_win_WMPaint();
#endif
		public:

			virtual bool			IsSelect();

			inline void				AddPointer(void*& pointer_);					// Додаємо у список керований вказівник
			inline void				RemovePointer(void*& pointer_);					// Видаляємо зі списку керований вказівник і занулюємо його
			inline void				ResetPointers();								// Видаляємо зі списку усі вказівники і занулуємо їх
			inline void				FlushPointers();								// Видаляємо зі списку усі вказівники
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

			struct Mouse
			{
				bool						stateL = false,stateM = false,stateR = false,
											stateOL = false,stateOM = false,stateOR = false,
											pressL = false,pressM = false,pressR = false;
				ivec2						pos = ivec2(0,0),oPos = ivec2(0,0),dPos = ivec2(0,0);

				inline void					Update()
				{
					//stateL = 
				}
			};
			Mouse							mouse;

			template <typename T>
			static T*						CreateInterface(PWindow window_);
			static inline void				DeleteInterface(GUI* interface_);

			Item*							picked = nullptr;
			Item*							selected = nullptr;
			Item*							top = nullptr;
			void							RefreshPicked();
			void							RefreshSelected();


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

			inline void											ToTop(Item* item_);
			inline Item*										GetPicked();
			inline Item*										GetSelected();
			inline Item*										GetTop();
			inline void											ResetPicked();
			inline void											ResetSelected();
			inline void											ResetTop();

			/*Методи, специфічні для ОС Windows*/
#if __TEXPROJECT_WIN__
			/*
			Цю функцію контекст буде викликати при обробці повідомлення WM_PAINT зі своєї _win_WMPaint
			*/
			virtual void									_win_WMPaint(HDC hDC);
#endif
		};

#if __TEXPROJECT_WIN__
		struct Default: public Interface::Basic
		{
			friend Creator;
		protected:

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

					virtual bool			IsSelect() override;

					virtual void			_win_WMPaint() override;
				};
			};
			struct Button
			{
			};


			HDC								renderDeviceContextHandle = NULL;
			RECT							renderRect;

											Default(PWindow window_);
											Default(const Default&) = delete;
											Default(Default&&) = delete;
			virtual							~Default() = default;

			Default&						operator = (const Default&) = delete;
			Default&						operator = (Default&&) = delete;

		public:

			virtual void										Create() override;
			virtual void										Delete() override;
			virtual void										Loop() override;

			virtual GUIPanelDefault*							AddPanelDefault() override;
			virtual GUIButtonDefault*							AddButtonDefault() override;
			virtual GUIButtonTrigger*							AddButtonTrigger() override;
			virtual GUIButtonAction*							AddButtonAction() override;
			virtual GUIButtonSlider*							AddButtonSlider() override;

			virtual void									_win_WMPaint(HDC hDC);
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

void										TexProject::Interface::Item::AddPointer(void*& pointer_)
{
	pointer_ = this;
	pointer.push_back((Item**)(&pointer_));
}
void										TexProject::Interface::Item::RemovePointer(void*& pointer_)
{
	auto i = pointer.begin();
	while(i != pointer.end())
	{
		auto t = *i;
		if(t == (Item**)(&pointer_))
		{
			i = pointer.erase(i);
			pointer_ = nullptr;
			continue;
		}
		++i;
	}
}
void										TexProject::Interface::Item::ResetPointers()
{
	for(auto i: pointer) *i = nullptr;
	pointer.clear();
}
void										TexProject::Interface::Item::FlushPointers()
{
	pointer.clear();
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
	auto i = button.begin();
	while(i != button.end())
	{
		auto t = *i;
		if(t == source)
		{
			Item::DeleteItem((Item*)t);
			i = button.erase(i);
			continue;
		}
		++i;
	}
}

TexProject::Interface::Item*				TexProject::Interface::Basic::GetPicked()
{
	return picked;
}
TexProject::Interface::Item*				TexProject::Interface::Basic::GetSelected()
{
	return selected;
}
TexProject::Interface::Item*				TexProject::Interface::Basic::GetTop()
{
	return top;
}
void										TexProject::Interface::Basic::ResetPicked()
{
	picked = nullptr;
}
void										TexProject::Interface::Basic::ResetSelected()
{
	selected = nullptr;
}
void										TexProject::Interface::Basic::ResetTop()
{
	top = nullptr;
}

void										TexProject::Interface::Basic::ToTop(Item* item_)
{
	if(item_)
	{
		if(top)
		{
			item_->SetPriority(top->GetPriority() + 1);
		}
	}
}


