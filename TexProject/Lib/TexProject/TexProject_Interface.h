#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>


#include <list>
#include <vector>
#include <algorithm>


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
			struct Connector;				// З'єднувач
		}


		typedef Item						GUIItem;
		typedef Panel::Basic				GUIPanel;
		typedef Panel::Default				GUIPanelDefault;
		typedef Panel::Image				GUIPanelImage;
		typedef Button::Basic				GUIButton;
		typedef Button::Default				GUIButtonDefault;
		typedef Button::Trigger				GUIButtonTrigger;
		typedef Button::Slider				GUIButtonSlider;
		typedef Button::Connector			GUIButtonConnector;


		struct PanelTypes
		{
			enum Enum
			{
				Default,
				Image
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
				Close,
				InputConnector,				// З'єднувач з входом
				OutputConnector				// З'єднувач з виходом
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
					Click					= 0,
					Free					= 1,
					Refresh					= 2,
					Reserved				= 3
				};
			};
			typedef ActionTypes::Enum		ActionType;

		protected:

			struct PropertyBits
			{
				enum Enum
				{
					Default					= 0xFFFFFFFF,
					Move					= 0x00000001
				};
			};

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
			void*							userData = nullptr;
			Action*							action[ActionTypes::count];
			uint32							properties = PropertyBits::Default;

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

			virtual bool					IsConnector();

			virtual void					Refresh();

			GUIItem*						GetBase();

			virtual vec2					GetPos();
			virtual vec2					GetLocalPos();
			virtual int32					GetPriority();
			virtual int32					GetLocalPriority();

			virtual GUIItem*				IsSelect();
			virtual bool					IsLocalSelect();
			virtual bool					IsAnyButtonSelect();

			inline void						ToTop();

			inline void						SetAction(const ActionType& type_,Action* action_);

			inline void						SetUserData(void* data);
			inline void*					GetUserData();

			inline void						AddPointer(void*& pointer_);					// Додаємо у список керований вказівник
			inline void						RemovePointer(void*& pointer_);					// Видаляємо зі списку керований вказівник і занулюємо його
			inline void						ResetPointers();								// Видаляємо зі списку усі вказівники і занулуємо їх
			inline void						FlushPointers();								// Видаляємо зі списку усі вказівники

			inline void						LockMove();
			inline void						UnlockMove();
			bool							CanMove();

			inline Window::Render*			GetWindow();
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

				virtual GUIItem*			IsSelect() override;
				virtual bool				IsAnyButtonSelect() override;

				template <typename T>
				T*							AddPanel();
				template <typename T>
				T*							AddButton();

#if __TEXPROJECT_WIN__
				virtual void				_win_WMPaint() override;
#endif

			public:

				virtual void				Refresh();

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
				virtual						~Default() = default;

				Default&					operator = (const Default&) = delete;
				Default&					operator = (Default&&) = delete;
			};
			struct Image: public Panel::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

				Texture*				texture = nullptr;

										Image(GUI* interface_,Item* parent_ = nullptr);
										Image(const Basic&) = delete;
										Image(Image&&) = delete;
				virtual					~Image() = default;

				Default&				operator = (const Image&) = delete;
				Default&				operator = (Image&&) = delete;

			public:

				inline void				SetImage(Texture* texture_);
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
			};
			struct Trigger: public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

				bool					state;

										Trigger(GUI* interface_,Item* parent_ = nullptr);
										Trigger(const Trigger&) = delete;
										Trigger(Trigger&&) = delete;
				virtual					~Trigger() = default;

				Trigger&				operator = (const Trigger&) = delete;
				Trigger&				operator = (Trigger&&) = delete;

				virtual void			Loop() override;
			};
			struct Slider: public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

				bool					selected = false;
				float32					slide = 0.0f;
				vec2					border = vec2(4.0f,2.0f);

										Slider(GUI* interface_,Item* parent_ = nullptr);
										Slider(const Slider&) = delete;
										Slider(Slider&&) = delete;
				virtual					~Slider() = default;

				Slider&					operator = (const Slider&) = delete;
				Slider&					operator = (Slider&&) = delete;

				virtual void			Loop() override;
			};
			struct Connector: public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			public:
				vec2						connectDirection = vec2(0.0f);
			protected:
				bool						recipient = false;
				Connector*					target = nullptr;
				std::list<Connector*>		observers;

				static Connector*			selected;
				static Connector*			binder;
				static Connector*			oBinder;

											Connector(GUI* interface_,Item* parent_ = nullptr);
											Connector(const Connector&) = delete;
											Connector(Connector&&) = delete;
				virtual						~Connector();

				Connector&					operator = (const Connector&) = delete;
				Connector&					operator = (Connector&&) = delete;

				virtual void				Loop() override;
			public:
				virtual bool				IsConnector() override;

				inline void					SetTarget(GUIButtonConnector* connector);
				inline void					UnsetTarget();
				inline void					SetRecipient();
				inline void					UnsetRecipient();
				inline void					FlushTargeting();
				inline GUIButtonConnector*	GetTarget()
				{
					return target;
				}
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
			friend Texture;
		protected:

			struct Panel
			{
				struct Default: public Interface::Panel::Default
				{
				public:
																Default(GUI* interface_,Item* parent_ = nullptr);
																~Default() = default;

					virtual void								_win_WMPaint() override;

					virtual GUIPanel*							AddPanel(const PanelType& type_) override;
					virtual GUIButton*							AddButton(const ButtonType& type_) override;
				};
				struct Image: public Interface::Panel::Image
				{
				public:
																Image(GUI* interface_,Item* parent_ = nullptr);
																~Image() = default;

					virtual void								_win_WMPaint() override;
				};
			};
			struct Button
			{
				struct Default: public Interface::Button::Default
				{
				public:
																Default(GUI* interface_,Item* parent_ = nullptr);
																~Default() = default;

					virtual void								_win_WMPaint() override;
				};
				struct Trigger: public Interface::Button::Trigger
				{
				public:
																Trigger(GUI* interface_,Item* parent_ = nullptr);
																~Trigger() = default;

					virtual void								_win_WMPaint() override;
				};
				struct Slider: public Interface::Button::Slider
				{
				public:
																Slider(GUI* interface_,Item* parent_ = nullptr);
																~Slider() = default;

					virtual void								_win_WMPaint() override;
				};
				struct Connector: public Interface::Button::Connector
				{
				public:
																Connector(GUI* interface_,Item* parent_ = nullptr);
																~Connector() = default;

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

inline void									TexProject::Interface::Item::SetUserData(void* data)
{
	userData = data;
}
inline void*								TexProject::Interface::Item::GetUserData()
{
	return userData;
}

inline void									TexProject::Interface::Item::AddPointer(void*& pointer_)
{
	pointer_ = this;
	pointer.push_back((Item**)(&pointer_));
}
inline void									TexProject::Interface::Item::RemovePointer(void*& pointer_)
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
inline void									TexProject::Interface::Item::ResetPointers()
{
	for(auto i: pointer) *i = nullptr;
	pointer.clear();
}
inline void									TexProject::Interface::Item::FlushPointers()
{
	pointer.clear();
}

inline void									TexProject::Interface::Item::LockMove()
{
	properties &= ~PropertyBits::Move;
}
inline void									TexProject::Interface::Item::UnlockMove()
{
	properties |= PropertyBits::Move;
}

inline TexProject::Window::Render*			TexProject::Interface::Item::GetWindow()
{
	return (Window::Render*)inter->GetWindow();
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


// Interface::Panel::Image
inline void									TexProject::Interface::Panel::Image::SetImage(Texture* texture_)
{
	texture = texture_;
}


// Interface::Button::Connector
inline void									TexProject::Interface::Button::Connector::SetTarget(GUIButtonConnector* connector)
{
	if(target)
	{
		auto i = target->observers.begin();
		while(i != target->observers.end())
		{
			if(*i == this)
			{
				i = target->observers.erase(i);
				continue;
			}
			++i;
		}
	}
	target = connector;
	if(target) target->observers.push_back(this);
}
inline void									TexProject::Interface::Button::Connector::UnsetTarget()
{
	if(target)
	{
		auto i = target->observers.begin();
		while(i != target->observers.end())
		{
			if(*i == this)
			{
				i = target->observers.erase(i);
				continue;
			}
			++i;
		}
	}
	target = nullptr;
}
inline void									TexProject::Interface::Button::Connector::SetRecipient()
{
	recipient = true;
	SetTarget(nullptr);
}
inline void									TexProject::Interface::Button::Connector::UnsetRecipient()
{
	recipient = false;
	FlushTargeting();
}
inline void									TexProject::Interface::Button::Connector::FlushTargeting()
{
	for(auto i: observers) i->target = nullptr;
	observers.clear();
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


