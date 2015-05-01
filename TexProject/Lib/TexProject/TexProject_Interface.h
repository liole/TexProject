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
			struct Slider;					// Повзунок
		}


		typedef Item						GUIItem;
		typedef Panel::Basic				GUIPanel;
		typedef Panel::Default				GUIPanelDefault;
		typedef Button::Basic				GUIButton;
		typedef Button::Default				GUIButtonDefault;
		typedef Button::Trigger				GUIButtonTrigger;
		typedef Button::Slider				GUIButtonSlider;


		struct PanelTypes
		{
			enum Enum
			{
				Default
			};
		};
		typedef PanelTypes::Enum			PanelType;

		struct ButtonTypes
		{
			enum Enum
			{
				Default,
				Trigger,
				Slider,
				Close
			};
		};
		typedef ButtonTypes::Enum			ButtonType;


		struct Item:
			public TexProject::Helper::Prio,
			public TexProject::Helper::Pos2,
			public TexProject::Helper::Size2
		{
			friend Interface::Basic;
			friend Interface::Default;
		public:

			typedef void(Action)(Item*);

			struct ActionTypes
			{
				static const uint32			count = 4;
				enum Enum
				{
					Select					= 0,
					Unselect				= 1,
					Click					= 2,
					Free					= 3
				};
			};
			typedef ActionTypes::Enum		ActionType;

		protected:

			struct Exception_Destruction
			{
			};
			struct Exception_LocalDestruction
			{
			};

			template <typename T>
			static T*						CreateItem(GUI* interface_,Item* parent_ = nullptr);
			static inline void				DeleteItem(GUIItem* item_);


			Item*							parent = nullptr;
			GUI * const						inter = nullptr;
			std::list<Item**>				pointer;
			Action*							action[ActionTypes::count];

											Item(GUI* interface_,Item* parent_ = nullptr);
											Item(const Item&) = delete;
											Item(Item&&) = delete;
			virtual							~Item();

			Item&							operator = (const Item&) = delete;
			Item&							operator = (Item&&) = delete;

			virtual void					Create();
			virtual void					Delete();
			virtual void					Loop();

			inline void						CallAction(const ActionType& type_);

			/*Методи, специфічні для ОС Windows*/
#if __TEXPROJECT_WIN__
			/*
			Цю функцію інтерфейс буде викликати при обробці повідомлення WM_PAINT зі своєї _win_WMPaint
			Параметр hDC, який приходить в інтерфейс з вікна - зберігатимемо у внутрішніх полях, для економії аргументів
			*/
			virtual void					_win_WMPaint();
#endif
		public:

			GUIItem*						GetBase();

			virtual vec2					GetPos();
			virtual vec2					GetLocalPos();
			virtual int32					GetPriority();
			virtual int32					GetLocalPriority();

			virtual bool					IsSelect();
			virtual bool					IsAnyButtonSelect();				// Без урахування поверхні кнопок

			inline void						ToTop();

			inline void						SetAction(const ActionType& type_,Action* action_);

			inline void						AddPointer(void*& pointer_);					// Додаємо у список керований вказівник
			inline void						RemovePointer(void*& pointer_);					// Видаляємо зі списку керований вказівник і занулюємо його
			inline void						ResetPointers();								// Видаляємо зі списку усі вказівники і занулуємо їх
			inline void						FlushPointers();								// Видаляємо зі списку усі вказівники
		};
		namespace Panel
		{
			struct Basic: public Item
			{
				friend Item;
				friend Interface::Basic;
			protected:
				std::list<Panel::Basic*>	panel;
				std::list<Button::Basic*>	button;

											Basic(GUI* interface_,Item* parent_ = nullptr);
											Basic(const Basic&) = delete;
											Basic(Basic&&) = delete;
				virtual						~Basic() = default;

				Basic&						operator = (const Basic&) = delete;
				Basic&						operator = (Basic&&) = delete;

				virtual void				Create() override;
				virtual void				Delete() override;
				virtual void				Loop() override;

				template <typename T>
				T*							AddPanel();
				template <typename T>
				T*							AddButton();

#if __TEXPROJECT_WIN__
				virtual void				_win_WMPaint() override;
#endif

			public:

				inline void					ToTop();

				virtual GUIPanel*			AddPanel(const PanelType& type_);
				virtual GUIButton*			AddButton(const ButtonType& type_);

			};
			struct Default: public Panel::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:
										Default(GUI* interface_,Item* parent_ = nullptr);
										Default(const Basic&) = delete;
										Default(Default&&) = delete;
				virtual					~Default() = default;

				Default&				operator = (const Default&) = delete;
				Default&				operator = (Default&&) = delete;

				/*virtual void			Create() override;
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
				friend Interface::Panel::Basic;
			protected:
										Basic(GUI* interface_,Item* parent_ = nullptr);
										Basic(const Basic&) = delete;
										Basic(Basic&&) = delete;
				virtual					~Basic() = default;

				Basic&					operator = (const Basic&) = delete;
				Basic&					operator = (Basic&&) = delete;

				virtual void			Create() override;
				virtual void			Delete() override;
				virtual void			Loop() override;

			public:

				inline void				ToTop();

			};
			struct Default: public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:
										Default(GUI* interface_,Item* parent_ = nullptr);
										Default(const Basic&) = delete;
										Default(Default&&) = delete;
				virtual					~Default() = default;

				Default&				operator = (const Default&) = delete;
				Default&				operator = (Default&&) = delete;

				/*virtual void			Create() override;
				virtual void			Delete() override;
				virtual void			Loop() override;*/

			};
			struct Trigger: public Button::Basic
			{
			};
			struct Slider: public Button::Basic
			{
			};
		}


		struct Basic
		{
			friend Creator;

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

		protected:

			template <typename T>
			static T*						CreateInterface(PWindow window_);
			static inline void				DeleteInterface(GUI* interface_);

			Item*							picked = nullptr;
			Item*							selected = nullptr;
			Item*							top = nullptr;
			void							RefreshPicked();
			void							RefreshSelected();


			PWindow							window = nullptr;
			std::list<Item*>				item;

											Basic(PWindow window_);
											Basic(const Basic&) = delete;
											Basic(Basic&&) = delete;
			virtual							~Basic() = default;

			Basic&							operator = (const Basic&) = delete;
			Basic&							operator = (Basic&&) = delete;

			template <typename T>
			T*													AddItem();

		public:

			virtual void										Create();
			virtual void										Delete();
			virtual void										Loop();

			virtual GUIPanel*									AddPanel(const PanelType& type_);
			virtual GUIButton*									AddButton(const ButtonType& type_);

			inline void											RemoveItem(GUIItem* source);

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
																Default(GUI* interface_,Item* parent_ = nullptr);
																~Default() = default;

					virtual void								Create() override;
					virtual void								Delete() override;
					virtual void								Loop() override;

					virtual bool								IsSelect() override;
					virtual bool								IsAnyButtonSelect() override;

					virtual void								_win_WMPaint() override;

					virtual GUIPanel*							AddPanel(const PanelType& type_) override;
					virtual GUIButton*							AddButton(const ButtonType& type_) override;
				};
			};
			struct Button
			{
				struct Default: public Interface::Button::Default
				{
				protected:
				public:
																Default(GUI* interface_,Item* parent_ = nullptr);
																~Default() = default;

					virtual void								Create() override;
					virtual void								Delete() override;
					virtual void								Loop() override;

					virtual bool								IsSelect() override;

					virtual void								_win_WMPaint() override;
				};
			};

			friend Panel::Default;
			friend Button::Default;


			HDC								renderDeviceContextHandle = NULL;
			RECT							renderRect;

			HBRUSH							renderBrushRed = NULL;
			HBRUSH							renderBrushGreen = NULL;
			HBRUSH							renderBrushBlue = NULL;

											Default(PWindow window_);
											Default(const Default&) = delete;
											Default(Default&&) = delete;
			virtual							~Default() = default;

			Default&						operator = (const Default&) = delete;
			Default&						operator = (Default&&) = delete;

		public:

			virtual void					Create() override;
			virtual void					Delete() override;
			virtual void					Loop() override;

			virtual GUIPanel*				AddPanel(const PanelType& type_);
			virtual GUIButton*				AddButton(const ButtonType& type_);

			virtual void					_win_WMPaint(HDC hDC);
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
typename T*									TexProject::Interface::Item::CreateItem(GUI* interface_,Item* parent_)
{
	auto t = new T(interface_,parent_);
	t->Create();
	return t;
}
void										TexProject::Interface::Item::DeleteItem(GUIItem* item_)
{
	item_->Delete();
	delete item_;
}

void										TexProject::Interface::Item::ToTop()
{
	inter->ToTop(this);
}

void										TexProject::Interface::Item::CallAction(const ActionType& type_)
{
	if(action[type_]) action[type_](this);
}
void										TexProject::Interface::Item::SetAction(const ActionType& type_,Action* action_)
{
	action[type_] = action_;
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


// Interface::Panel::Basic
void										TexProject::Interface::Panel::Basic::ToTop()
{
	if(parent)
	{
		parent->ToTop();
	}
	else
	{
		inter->ToTop(this);
	}
}

template <typename T>
typename T*									TexProject::Interface::Panel::Basic::AddPanel()
{
	auto t = Item::CreateItem<T>(inter,this);
	panel.push_back((Panel::Basic*)t);
	return t;
}
template <typename T>
typename T*									TexProject::Interface::Panel::Basic::AddButton()
{
	auto t = Item::CreateItem<T>(inter,this);
	button.push_back((Button::Basic*)t);
	return t;
}


// Interface::Button::Basic
void										TexProject::Interface::Button::Basic::ToTop()
{
	if(parent)
	{
		parent->ToTop();
	}
	else
	{
		inter->ToTop(this);
	}
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

/*
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
*/
template <typename T>
typename T*									TexProject::Interface::Basic::AddItem()
{
	auto t = Interface::Item::CreateItem<T>(this);
	item.push_back((Item*)t);
	return t;
}
void										TexProject::Interface::Basic::RemoveItem(GUIItem* source)
{
	for(auto i = item.begin(); i != item.end(); ++i)
	{
		auto t = *i;
		if(t == source)
		{
			Item::DeleteItem((Item*)t);
			i = item.erase(i);
		}
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


