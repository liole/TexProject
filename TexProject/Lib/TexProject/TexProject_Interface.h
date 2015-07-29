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


		struct Basic;						// ������� ���� ����������
		struct Default;						// ��������� �������� ��
		struct OpenGL;						// ��������� � ��������� OpenGL
		struct Direct3D;					// ��������� � ��������� Direct3D
		struct Mantle;						// ��������� � ��������� MantleAPI
		struct Vulkan;						// ��������� � ��������� VulkanAPI

		typedef Interface::Basic			GUI;


		struct Creator
		{
			friend Window::RenderContext::Default;
		protected:
			template <typename T>
			static inline T*				CreateInterface(PWindow window_);
			static inline void				DeleteInterface(GUI* interface_);
		};


		struct Item;						// ������� ���� �������� ����������
		namespace Panel						// �����
		{
			struct Basic;					// �������
			struct Default;					// ��������
			struct Text;					// �����
			struct Image;					// ����������
		}
		namespace Button					// ������
		{
			struct Basic;					// �������
			struct Default;					// ��������
			struct Trigger;					// ���������
			struct Slider;					// ��������
			struct Connector;				// �'�������
		}


		typedef Item						GUIItem;
		typedef Panel::Basic				GUIPanel;
		typedef Panel::Default				GUIPanelDefault;
		typedef Panel::Image				GUIPanelImage;
		typedef Panel::Text					GUIPanelText;
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
				Image,
				Text
			};
		};
		typedef PanelTypes::Enum			PanelType;

		struct ButtonTypes
		{
			enum Enum
			{
				Default,
				Trigger,
				Switcher,
				Slider,
				Close,
				InputConnector,				// �'������� � ������
				OutputConnector				// �'������� � �������
			};
		};
		typedef ButtonTypes::Enum			ButtonType;


		struct Item:
			public TexProject::Helper::Prio,
			public TexProject::Helper::Pos2,
			public TexProject::Helper::Size2,
			public TexProject::Helper::Color4
		{
			friend Interface::Basic;
			friend Interface::Default;
		public:

			typedef void(Action)(Item*);

			struct ActionTypes
			{
				static const uint32			count = 8;
				enum Enum
				{
					Click					= 0,
					Free					= 1,
					Refresh					= 2,
					Destruction				= 3,		// Close button pressed
					Clamp					= 4,		// Clamped Button
					Reserved5				= 5,
					Reserved6				= 6,
					Reserved7				= 7
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
			bool							userDataRemove = false;
			Action*							action[ActionTypes::count];
			uint32							properties = PropertyBits::Default;
			bool							clamped = false;
			uint32							clampLock = 0;
			vec2							anchor = vec2(0.0f);					// Anchor point for position

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

			/*������, ���������� ��� �� Windows*/
#if __TEXPROJECT_WIN__
			/*
			�� ������� ��������� ���� ��������� ��� ������� ����������� WM_PAINT � �� _win_WMPaint
			�������� hDC, ���� ��������� � ��������� � ���� - ������������ � ��������� �����, ��� �����쳿 ���������
			*/
			virtual void					_win_WMPaint();
#endif
		public:

			virtual bool					IsConnector();

			virtual void					Refresh();

			GUIItem*						GetBase();

			inline void						SetAnchor(const vec2& anchor_)
			{
				anchor = anchor_;
			}
			inline vec2						GetAnchor() const
			{
				return anchor;
			}

			virtual vec2					GetPos();
			virtual vec2					GetLocalPos();
			virtual int32					GetPriority();
			virtual int32					GetLocalPriority();

			virtual GUIItem*				IsSelect();
			virtual bool					IsLocalSelect();
			virtual bool					IsAnyButtonSelect();

			inline void						ToTop();

			inline void						SetAction(const ActionType& type_,Action* action_);

			inline void						SetUserData(void* data_, bool remove_ = false);
			inline void*					GetUserData();

			inline void						AddPointer(void** pointer_);					// ������ � ������ ��������� ��������
			inline void						RemovePointer(void** pointer_);					// ��������� � ������ ��������� �������� � ��������� ����
			inline void						ResetPointers();								// ��������� � ������ �� ��������� � �������� ��
			inline void						FlushPointers();								// ��������� � ������ �� ���������

			inline void						LockMove();
			inline void						UnlockMove();
			bool							CanMove();

			inline Window::Render*			GetWindow();
		};
		namespace Panel
		{
			struct Basic:
				public Item
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
				inline void					RemoveButton(Button::Basic* button_);
				inline void					RemovePanel(Panel::Basic* panel_);
				/*inline void					AttachButton(Button::Basic* button_);
				inline void					AttachPanel(Panel::Basic* panel_);
				inline void					DetachButton(Button::Basic* button_);
				inline void					DetachPanel(Panel::Basic* panel_);*/

			};
			struct Default:
				public Panel::Basic
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
			struct Text:
				public Panel::Basic
			{
				friend Item;
				friend Interface::Basic;
			public:

				enum class Alignment
				{
					Default,
					LeftTop,
					LeftCenter,
					LeftBottom,
					CenterTop,
					CenterCenter,
					CenterBottom,
					RightTop,
					RightCenter,
					RightBottom
				};

			protected:

				string						text = "";
				Alignment					alignment = Alignment::Default;

											Text(GUI* interface_,Item* parent_ = nullptr);
											Text(const Text&) = delete;
											Text(Text&&) = delete;
				virtual						~Text() = default;

				Text&						operator = (const Text&) = delete;
				Text&						operator = (Text&&) = delete;

			public:

				virtual void				SetText(const string& text_);
				virtual string				GetText() const;
				virtual void				SetAlignment(Alignment alignment_);
			};
			struct Image:
				public Panel::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

											Image(GUI* interface_,Item* parent_ = nullptr);
											Image(const Basic&) = delete;
											Image(Image&&) = delete;
				virtual						~Image() = default;

				Image&					operator = (const Image&) = delete;
				Image&					operator = (Image&&) = delete;

			public:

				virtual void				SetImage(Texture::D2* texture_);
			};
		}
		namespace Button
		{
			struct Basic:
				public Item
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
			struct Default:
				public Button::Basic
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
			struct Trigger:
				public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

				bool					state;
				vec4					colorActive = vec4(1.0f,0.0f,0.0f,1.0f);

										Trigger(GUI* interface_,Item* parent_ = nullptr);
										Trigger(const Trigger&) = delete;
										Trigger(Trigger&&) = delete;
				virtual					~Trigger() = default;

				Trigger&				operator = (const Trigger&) = delete;
				Trigger&				operator = (Trigger&&) = delete;

				virtual void			Loop() override;

				inline void				SetColorActive(const vec4& color_)
				{
					colorActive = color_;
				}
				inline vec4				GetColorActive()
				{
					return colorActive;
				}
			};
			struct Switcher:
				public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

				uint32					state = 0;
				uint32					maxState = 1;
				vec4					colorActive = vec4(1.0f,0.0f,0.0f,1.0f);

										Switcher(GUI* interface_,Item* parent_ = nullptr);
										Switcher(const Switcher&) = delete;
										Switcher(Switcher&&) = delete;
				virtual					~Switcher() = default;

				Switcher&				operator = (const Switcher&) = delete;
				Switcher&				operator = (Switcher&&) = delete;

				virtual void			Loop() override;

			public:

				inline void				SetColorActive(const vec4& color_)
				{
					colorActive = color_;
				}
				inline vec4				GetColorActive()
				{
					return colorActive;
				}

				inline void				SetState(uint32 state_)
				{
					if(state_ < maxState) state = state_;
				}
				inline uint32			GetState() const
				{
					return state;
				}
				inline void				SetMaxState(uint32 maxState_)
				{
					if(maxState > 0) maxState = maxState_;
					if(state >= maxState) state = 0;
				}
				inline uint32			GetMaxState() const
				{
					return maxState;
				}
			};
			struct Slider: public Button::Basic
			{
				friend Item;
				friend Interface::Basic;
			protected:

				bool					selected = false;
				float32					slide = 0.0f;
				vec2					border = vec2(4.0f,2.0f);
				vec4					colorInner = vec4(0.32f,0.32f,0.32f,1.0f),
										colorRail = vec4(1.0f,1.0f,1.0f,1.0f),
										colorSlider = vec4(0.0f,0.0f,1.0f,1.0f);

										Slider(GUI* interface_,Item* parent_ = nullptr);
										Slider(const Slider&) = delete;
										Slider(Slider&&) = delete;
				virtual					~Slider() = default;

				Slider&					operator = (const Slider&) = delete;
				Slider&					operator = (Slider&&) = delete;

				virtual void			Loop() override;

			public:
				inline float32			GetValue() const;
				inline void				SetValue(float32 value_);
				inline void				SetColorInner(const vec4& color_)
				{
					colorInner = color_;
				}
				inline vec4				GetColorInner()
				{
					return colorInner;
				}
				inline void				SetColorRail(const vec4& color_)
				{
					colorRail = color_;
				}
				inline vec4				GetColorRail()
				{
					return colorRail;
				}
				inline void				SetColorSlider(const vec4& color_)
				{
					colorSlider = color_;
				}
				inline vec4				GetColorSlider()
				{
					return colorSlider;
				}
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

				virtual void				Refresh() override;
				inline void					RefreshObservers()
				{
					for(auto i: observers) i->Refresh();
				}

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
				ivec2						pos = ivec2(0,0),oPos = ivec2(0,0),dPos = ivec2(0,0),
											localPos = ivec2(0,0);

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

			bool							dragging = true;


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

			inline void											EnableDragging()
			{
				dragging = true;
			}
			inline void											DisableDragging()
			{
				dragging = false;
			}

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

			/*������, ���������� ��� �� Windows*/
#if __TEXPROJECT_WIN__
			/*
			�� ������� �������� ���� ��������� ��� ������� ����������� WM_PAINT � �� _win_WMPaint
			*/
			virtual void									_win_WMPaint(HDC hDC);
#endif
		};

#if __TEXPROJECT_WIN__
		struct Default:
			public Interface::Basic
		{
			friend Creator;
			friend Windows::Texture;
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
				struct Text:
					public Interface::Panel::Text
				{
				protected:

					enum class _win_Alignment: UINT
					{
						Default					= DT_LEFT | DT_TOP,
						LeftTop					= DT_LEFT | DT_TOP,
						LeftCenter				= DT_LEFT | DT_VCENTER | DT_SINGLELINE,
						LeftBottom				= DT_LEFT | DT_RIGHT | DT_SINGLELINE,
						CenterTop				= DT_CENTER | DT_TOP,
						CenterCenter			= DT_CENTER | DT_VCENTER | DT_SINGLELINE,
						CenterBottom			= DT_CENTER | DT_RIGHT | DT_SINGLELINE,
						RightTop				= DT_RIGHT | DT_TOP,
						RightCenter				= DT_RIGHT | DT_VCENTER | DT_SINGLELINE,
						RightBottom				= DT_RIGHT | DT_RIGHT | DT_SINGLELINE,
						/*DT_TOP                      0x00000000
						DT_LEFT                     0x00000000
						DT_CENTER                   0x00000001
						DT_RIGHT                    0x00000002
						DT_VCENTER                  0x00000004
						DT_BOTTOM                   0x00000008
						DT_WORDBREAK                0x00000010
						DT_SINGLELINE               0x00000020
						DT_EXPANDTABS               0x00000040
						DT_TABSTOP                  0x00000080
						DT_NOCLIP                   0x00000100
						DT_EXTERNALLEADING          0x00000200
						DT_CALCRECT                 0x00000400
						DT_NOPREFIX                 0x00000800
						DT_INTERNAL                 0x00001000*/
					};
					_win_Alignment								_win_alignment = _win_Alignment::Default;

				public:
																Text(GUI* interface_,Item* parent_ = nullptr);
																~Text() = default;

					virtual void								SetAlignment(Alignment alignment_) override;

					virtual void								_win_WMPaint() override;
				};
				struct Image: public Interface::Panel::Image
				{
					Windows::Texture*							image = nullptr;

				public:
																Image(GUI* interface_,Item* parent_ = nullptr);
																~Image();

					virtual void								SetImage(Texture::D2* texture_) override;

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
				struct Switcher:
					public Interface::Button::Switcher
				{
				public:
																Switcher(GUI* interface_,Item* parent_ = nullptr);
																~Switcher() = default;

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

inline void									TexProject::Interface::Item::CallAction(const ActionType& type_)
{
	if(action[type_]) action[type_](this);
}
inline void									TexProject::Interface::Item::SetAction(const ActionType& type_,Action* action_)
{
	action[type_] = action_;
}

inline void									TexProject::Interface::Item::SetUserData(void* data_,bool remove_)
{
	if(userDataRemove && userData)
	{
		delete userData;
	}
	userData = data_;
	userDataRemove = remove_;
}
inline void*								TexProject::Interface::Item::GetUserData()
{
	return userData;
}

inline void									TexProject::Interface::Item::AddPointer(void** pointer_)
{
	*pointer_ = this;
	pointer.push_back((Item**)(&pointer_));
}
inline void									TexProject::Interface::Item::RemovePointer(void** pointer_)
{
	auto i = pointer.begin();
	while(i != pointer.end())
	{
		auto t = *i;
		if(t == (Item**)(pointer_))
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
inline void									TexProject::Interface::Panel::Basic::RemoveButton(Button::Basic* button_)
{
	auto i = button.begin();
	while(i != button.end())
	{
		if(*i == button_)
		{
			//auto t = *i;
			Item::DeleteItem(*i);
			i = button.erase(i);
			continue;
		}
		++i;
	}
}
inline void									TexProject::Interface::Panel::Basic::RemovePanel(Panel::Basic* panel_)
{
	auto i = panel.begin();
	while(i != panel.end())
	{
		if(*i == panel_)
		{
			Item::DeleteItem(*i);
			i = panel.erase(i);
			continue;
		}
		++i;
	}
}


// Interface::Button::Slider
inline TexProject::float32					TexProject::Interface::Button::Slider::GetValue() const
{
	return slide;
}
inline void									TexProject::Interface::Button::Slider::SetValue(float32 value_)
{
	slide = value_;
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
	auto i = item.begin();
	while(i != item.end())
	{
		auto t = *i;
		if(t == source)
		{
			Item::DeleteItem((Item*)t);
			i = item.erase(i);
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


