#pragma once
#pragma region TexProject Includes
#include <TexProject/TexProject_Header.h>
#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Windows.h>
#include <TexProject/TexProject_Helpers.h>
#pragma endregion
#pragma region Includes
#include <list>
#include <iterator>
#include <algorithm>
#pragma endregion


#pragma region Test
#pragma endregion


namespace TexProject
{
	class GUIBind
	{
	protected:
		GUI*const							gui;
		inline								GUIBind(GUI* gui_);
	public:
		inline GUI*							GetGUI() const;
	};
	class GraphicUserInterface:
		public ContextBind
	{
#pragma region Basic
		friend Window;
	protected:
		GraphicUserInterface(RenderContext* renderContext_);
		virtual								~GraphicUserInterface() = default;
		virtual void						Loop();
#pragma endregion
#pragma region Mouse Data
	protected:
		class Mouse:
			public GUIBind
		{
		public:
			ivec2							pos = ivec2(0),opos = ivec2(0),dpos = ivec2(0),
											locpos = ivec2(0), locopos = ivec2(0), locdpos = ivec2(0);
			bool							lstate = false,olstate = false,
											rstate = false,orstate = false,
											mstate = false,omstate = false;

			inline							Mouse(GUI* gui_);
			inline void						Process();
		};
		Mouse								mouse;
#pragma endregion
#pragma region Color Scheme
	public:
		class ColorScheme
		{
		public:
			vec4							colorBasic	= vec4(0.5f,0.5f,0.5f,1.0f),
											colorSelect	= vec4(0.8f,0.8f,0.8f,1.0f),
											colorUse	= vec4(1.0f,1.0f,1.0f,1.0f),
											colorBack	= vec4(0.4f,0.4f,0.4f,1.0f),
											colorSlider	= vec4(0.16f,0.16f,0.16f,1.0f);
		};
	public:
		ColorScheme							colorScheme;
#pragma endregion
#pragma region Items Declaration
	public:
		class Item;
		class Panel;
		class Button;
		enum class PanelTypes
		{
			Default,
			Image,
			Text
		};
		enum class ButtonTypes
		{
			Default,
			Trigger,
			Switcher,
			Slider,
			Connector
		};
		class Item:
#pragma region Inheritance
			public Helper::Prio,
			public Helper::Color4,
			public Helper::Pos2,
			public Helper::Size2
#pragma endregion
		{
#pragma region Destruction;
		protected:
			class Destruction
			{
			};
			class LocalDestruction
			{
			};
#pragma endregion
#pragma region Bind To GUI
			friend GraphicUserInterface;
		protected:
			GUI*const						gui;
		public:
			inline GUI*						GetGUI() const;
#pragma endregion
#pragma region Basic
		protected:
			enum class PropertiesBit: uint32
			{
				Enabled						= 0x0001,
				Visible						= 0x0002,
				UserDataClearing			= 0x0004,
				TopMost						= 0x0008,
				Dragging					= 0x0010,
				Scrolling					= 0x0020,
				ScrollX						= 0x0040,
				ScrollY						= 0x0080,
				Clipping					= 0x0100,
				Collapsing					= 0x0200,
				Collapsed					= 0x0400,
				Closing						= 0x0800,
				Reserved0					= 0x1000,
				Reserved1					= 0x2000,
				Reserved2					= 0x4000,
				Reserved3					= 0x8000,
				Default						= Enabled | Visible | Dragging | Clipping
			};
		protected:
			Item*							parent = nullptr;
			uint32							properties = (uint32)PropertiesBit::Default;
			void*							userData = nullptr;
			vec2							anchor = vec2(0.0f);
			vec2							scrollingValue = vec2(0.0f);
			vec2							scrollingSize = vec2(0.0f);
			vec2							border = vec2(8.0f);
			string							tip = "";
		protected:
											Item(GUI* gui_,Item* parent_ = nullptr);
											Item(const Item&) = delete;
			virtual							~Item();
			virtual void					Loop();
		protected:
			inline friend bool				operator < (Item& a,Item& b);
		public:
			inline Item*					GetParent() const;
			Item*							GetBase();
			inline void						Enable();
			inline void						Disable();
			inline bool						IsEnabled() const;
			inline void						Show();
			inline void						Hide();
			inline bool						IsVisible() const;
			inline void						EnableTopMost();
			inline void						DisableTopMost();
			inline bool						IsTopMost() const;
			inline void						EnableDragging();
			inline void						DisableDragging();
			inline bool						IsDraggable() const;
			inline void						EnableScrolling();
			inline void						DisableScrolling();
			inline bool						IsScrollable() const;
			inline void						SetScrollingSize(const vec2& size_);
			inline void						SetScrollingValue(const vec2& val_);
			inline vec2						GetScrollingSize() const;
			inline vec2						GetScrollingValue() const;
			inline void						SetBorder(const vec2& border_);
			inline vec2						GetBorder() const;
			inline void						EnableClipping();
			inline void						DisableClipping();
			inline bool						IsClippable() const;
			inline void						EnableCollapsing();
			inline void						DisableCollapsing();
			inline bool						IsCollapsable() const;
			inline void						Collapse();
			inline void						Restore();
			inline bool						IsCollapsed() const;
			inline void						EnableClosing();
			inline void						DisableClosing();
			inline bool						IsClosable() const;
			virtual vec2					GetPos() const;
			inline vec2						GetLocalPos() const;
			inline void						SetAnchor(const vec2& anchor_);
			inline vec2						GetAnchor() const;
			inline void						SetUserData(void* data_,bool clearing_ = false);
			inline void*					GetUserData() const;
			inline void						SetTip(const string& tip_);
			inline string					GetTip() const;
#pragma endregion
#pragma region Dragging
			virtual Item*					GetSelection();
			virtual bool					IsSelected() const;
			virtual bool					CanDrag() const;
#pragma endregion
#pragma region Actions
		public:
			enum class ActionType: uint32
			{
				Click						= 0,
				Refresh						= 1,
				Destruction					= 2,
				Check						= 3
			};
			typedef void					(*Action)(Item*);
		protected:
			static const uint32				actionsCount = 4;
			Action							action[actionsCount];
			inline void						CallAction(ActionType type_);
		public:
			inline void						SetAction(ActionType type_,Action action_);
			inline Action					GetAction(ActionType type_) const;
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
			virtual void					_win_Paint();
#endif
#pragma endregion
		};
		class Panel:
			public Item
		{
#pragma region Type
		public:
			enum class Type
			{
				Default,
				Image,
				Text
			};
			virtual Type					GetType() const = 0;
#pragma endregion
#pragma region Basic
											Panel(GUI* gui_,Item* parent_ = nullptr);
			virtual							~Panel() override;
			virtual void					Loop() override;
#pragma endregion
#pragma region Child
		protected:
			std::list<Item*>				item;
		public:
			virtual Panel*					AddPanel(PanelTypes type_);
			virtual Button*					AddButton(ButtonTypes type_);
			void							AttachItem(Item* item_);
			void							DetachItem(Item* item_);
			template<typename T>
			inline T*						AddItem();
			inline void						RemoveItem(Item* item_);
#pragma endregion
#pragma region Dragging
			virtual Item*					GetSelection() override;
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
			virtual void					_win_Paint() override;
#endif
#pragma endregion
		};
		class Panels
		{
		public:
			class Default:
				public Panel
			{
				friend GraphicUserInterface;
			protected:
											Default(GUI* gui_,Item* parent_ = nullptr);
				virtual void				Loop() override;
			public:
				virtual Type				GetType() const override;
			};
			class Image:
				public Panel
			{
				friend GraphicUserInterface;
			protected:
											Image(GUI* gui_,Item* parent_ = nullptr);
			public:
				virtual Type				GetType() const override;
				virtual void				SetImage(Texture::D2* image_) = 0;
			};
			class Text:
				public Panel
			{
				friend GraphicUserInterface;
			protected:
				enum class PropertiesBit: uint32
				{
					Selecting				= (uint32)Item::PropertiesBit::Reserved0,
					Editing					= (uint32)Item::PropertiesBit::Reserved1,
					Singleline				= (uint32)Item::PropertiesBit::Reserved2
				};
				uint32						textSize;
				string						text = "";
											Text(GUI* gui_,Item* parent_ = nullptr);
				virtual void				Loop() override;
			public:
				virtual Type				GetType() const override;
				inline void					SetText(const string& text_);
				inline string				GetText() const;
				inline void					SetTextSize(uint32 size_);
				inline void					EnableTextSelecting();
				inline void					DisableTextSelecting();
				inline bool					IsTextSelectable() const;
				inline void					EnableTextEditing();
				inline void					DisableTextEditing();
				inline bool					IsTextEditable() const;
				inline void					EnableTextSingleline();
				inline void					DisableTextSingleline();
				inline bool					IsTextSingleline() const;
				/*
				Set/Get Font
				Set/Get Text Size
				Enable/Disable Text Selecting
				Enable/Disable Text Editting
				Enable/Disable Singleline
				SetAlignment
				GetSelectdText
				*/
			};
		protected:
			Panels();
		};
		class Button:
			public Item
		{
#pragma region Type
		public:
			enum class Type
			{
				Default,
				Trigger,
				Switcher,
				Slider,
				Connector
			};
			virtual Type					GetType() const = 0;
#pragma endregion
#pragma region Basic
											Button(GUI* gui_,Item* parent_ = nullptr);
			virtual							~Button() = default;
#pragma endregion
		};
		class Buttons
		{
		public:
			class Default:
				public Button
			{
				friend GraphicUserInterface;
			protected:
											Default(GUI* gui_,Item* parent_ = nullptr);
			public:
				virtual Type				GetType() const override;
			};
			class Trigger:
				public Button
			{
				friend GraphicUserInterface;
			protected:
				bool						state = false;
											Trigger(GUI* gui_,Item* parent_ = nullptr);
				virtual void				Loop() override;
			public:
				virtual Type				GetType() const override;
				inline void					SetState(bool state_);
				inline bool					GetState() const;
			};
			class Switcher:
				public Button
			{
				friend GraphicUserInterface;
			protected:
				uint32						maxState = 1;
				uint32						state = 0;
											Switcher(GUI* gui_,Item* parent_ = nullptr);
				virtual void				Loop() override;
			public:
				virtual Type				GetType() const override;
				inline void					SetState(uint32 state_);
				inline uint32				GetState() const;
				inline void					SetMaxState(uint32 maxState_);
				inline uint32				GetMaxState() const;
			};
			class Slider:
				public Button
			{
				friend GraphicUserInterface;
			protected:
				enum class PropertiesBit: uint32
				{
					Lock					= (uint32)Item::PropertiesBit::Reserved0
				};
			protected:
				float32						value = 0.0f;
											Slider(GUI* gui_,Item* parent_ = nullptr);
				virtual void				Loop() override;
			public:
				virtual Type				GetType() const override;
				inline void					SetValue(float32 value_);
				inline float32				GetValue() const;
			};
			class Connector:
				public Button
			{
				friend GraphicUserInterface;
			protected:
				enum class PropertiesBit: uint32
				{
					Recipient				= (uint32)Item::PropertiesBit::Reserved0
				};
			protected:
				static Connector*			selected;
				static Connector*			binder;
				static Connector*			oBinder;
			protected:
				Connector*					target = nullptr;
				std::list<Connector*>		observers;
			public:
				static Connector*			checkConnector;
				static bool					checkValidate;
			protected:
											Connector(GUI* gui_,Item* parent_ = nullptr);
				virtual						~Connector();
				virtual void				Loop() override;
			public:
				vec2						direction = vec2(0.0f);
				virtual Type				GetType() const override;

				inline void					SetTarget(Connector* connector);
				inline void					UnsetTarget();
				inline void					SetRecipient();
				inline void					UnsetRecipient();
				inline bool					IsRecipient() const;
				inline void					FlushTargeting();
				inline Connector*			GetTarget() const;
				inline void					RefreshObservers();
			};
		private:
			Buttons();
		};
#pragma endregion
#pragma region Items Processing
	protected:
		std::list<Item*>					item;
	public:
		virtual Panel*						AddPanel(PanelTypes type_);
		virtual Button*						AddButton(ButtonTypes type_);
		template<typename T>
		inline T*							AddItem();
		inline void							RemoveItem(Item* item_);
#pragma endregion
#pragma region Dragging
		friend Item;
	protected:
		bool						draggingCan = false;
		Item*						draggingSelection = nullptr;
		Item*						draggingPick = nullptr;
		inline void					DraggingProcess();
		inline void					ToTop(Item* item_);
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
		virtual void						_win_Paint();
#endif
#pragma endregion
	};
}


#pragma region GUI
#pragma region Item
#pragma region Bind To GUI
inline TexProject::GUI*						TexProject::GUI::Item::GetGUI() const
{
	return gui;
}
#pragma endregion
#pragma region Basic
inline bool									TexProject::operator < (TexProject::GUI::Item& a,TexProject::GUI::Item& b)
{
	if(a.IsTopMost())
	{
		if(!b.IsTopMost()) return false;
	}
	else
	{
		if(b.IsTopMost()) return true;
	}
	//return a.GetPriority() < b.GetPriority();
	if(a.GetBase() == b.GetBase())
	{
		return a.GetPriority() < b.GetPriority();
	}
	else
	{
		return a.GetBase()->GetPriority() < b.GetBase()->GetPriority();
	}
}
inline TexProject::GUI::Item*				TexProject::GUI::Item::GetParent() const
{
	return parent;
}
inline void									TexProject::GUI::Item::Enable()
{
	properties |= (uint32)PropertiesBit::Enabled;
}
inline void									TexProject::GUI::Item::Disable()
{
	properties &= ~(uint32)PropertiesBit::Enabled;
}
inline bool									TexProject::GUI::Item::IsEnabled() const
{
	return (properties & (uint32)PropertiesBit::Enabled) > 0;
}
inline void									TexProject::GUI::Item::Show()
{
	properties |= (uint32)PropertiesBit::Visible;
}
inline void									TexProject::GUI::Item::Hide()
{
	properties &= ~(uint32)PropertiesBit::Visible;
}
inline bool									TexProject::GUI::Item::IsVisible() const
{
	return (properties & (uint32)PropertiesBit::Visible) > 0;
}
inline void									TexProject::GUI::Item::EnableTopMost()
{
	properties |= (uint32)PropertiesBit::TopMost;
}
inline void									TexProject::GUI::Item::DisableTopMost()
{
	properties &= ~(uint32)PropertiesBit::TopMost;
}
inline bool									TexProject::GUI::Item::IsTopMost() const
{
	return (properties & (uint32)PropertiesBit::TopMost) > 0;
}
inline void									TexProject::GUI::Item::EnableDragging()
{
	properties |= (uint32)PropertiesBit::Dragging;
}
inline void									TexProject::GUI::Item::DisableDragging()
{
	properties &= ~(uint32)PropertiesBit::Dragging;
}
inline bool									TexProject::GUI::Item::IsDraggable() const
{
	//return (properties & (uint32)PropertiesBit::Dragging) > 0;
	return ((properties & (uint32)PropertiesBit::Dragging) > 0) && ((properties & (uint32)PropertiesBit::Visible) > 0);
}
inline void									TexProject::GUI::Item::EnableScrolling()
{
	properties |= (uint32)PropertiesBit::Scrolling;
}
inline void									TexProject::GUI::Item::DisableScrolling()
{
	properties &= ~(uint32)PropertiesBit::Scrolling;
}
inline bool									TexProject::GUI::Item::IsScrollable() const
{
	return (properties & (uint32)PropertiesBit::Scrolling) > 0;
}
inline void									TexProject::GUI::Item::SetScrollingSize(const vec2& size_)
{
	scrollingSize = size_;
}
inline void									TexProject::GUI::Item::SetScrollingValue(const vec2& val_)
{
	scrollingValue = val_;
}
inline TexProject::vec2						TexProject::GUI::Item::GetScrollingSize() const
{
	return scrollingSize;
}
inline TexProject::vec2						TexProject::GUI::Item::GetScrollingValue() const
{
	return scrollingValue;
}
inline void									TexProject::GUI::Item::SetBorder(const vec2& border_)
{
	border = border_;
}
inline TexProject::vec2						TexProject::GUI::Item::GetBorder() const
{
	return border;
}
inline void									TexProject::GUI::Item::EnableClipping()
{
	properties |= (uint32)PropertiesBit::Clipping;

}
inline void									TexProject::GUI::Item::DisableClipping()
{
	properties &= ~(uint32)PropertiesBit::Clipping;
}
inline bool									TexProject::GUI::Item::IsClippable() const
{
	return (properties & (uint32)PropertiesBit::Clipping) > 0;
}
inline void									TexProject::GUI::Item::EnableCollapsing()
{
	properties |= (uint32)PropertiesBit::Collapsing;
}
inline void									TexProject::GUI::Item::DisableCollapsing()
{
	properties &= ~(uint32)PropertiesBit::Collapsing;
}
inline bool									TexProject::GUI::Item::IsCollapsable() const
{
	return (properties & (uint32)PropertiesBit::Collapsing) > 0;
}
inline void									TexProject::GUI::Item::Collapse()
{
	properties |= (uint32)PropertiesBit::Collapsed;
}
inline void									TexProject::GUI::Item::Restore()
{
	properties &= ~(uint32)PropertiesBit::Collapsed;
}
inline bool									TexProject::GUI::Item::IsCollapsed() const
{
	return (properties & (uint32)PropertiesBit::Collapsed) > 0;
}
inline void									TexProject::GUI::Item::EnableClosing()
{
	properties |= (uint32)PropertiesBit::Closing;
}
inline void									TexProject::GUI::Item::DisableClosing()
{
	properties &= ~(uint32)PropertiesBit::Closing;
}
inline bool									TexProject::GUI::Item::IsClosable() const
{
	return (properties & (uint32)PropertiesBit::Closing) > 0;
}
inline TexProject::vec2						TexProject::GUI::Item::GetLocalPos() const
{
	return Helper::Pos2::GetPos();
}
inline void									TexProject::GUI::Item::SetAnchor(const vec2& anchor_)
{
	anchor = anchor_;
}
inline vec2									TexProject::GUI::Item::GetAnchor() const
{
	return anchor;
}
inline void									TexProject::GUI::Item::SetUserData(void* data_,bool clearing_)
{
	if(userData)
	{
		if((properties & (uint32)PropertiesBit::UserDataClearing) > 0) delete userData;
		userData = nullptr;
	}

	userData = data_;

	if(clearing_) properties |= (uint32)PropertiesBit::UserDataClearing;
	else properties &= ~(uint32)PropertiesBit::UserDataClearing;
}
inline void*								TexProject::GUI::Item::GetUserData() const
{
	return userData;
}
inline void									TexProject::GUI::Item::SetTip(const string& tip_)
{
	tip = tip_;
}
inline TexProject::string					TexProject::GUI::Item::GetTip() const
{
	return tip;
}
#pragma endregion
#pragma region Actions
inline void									TexProject::GUI::Item::CallAction(ActionType type_)
{
	if(action[(uint32)type_]) action[(uint32)type_](this);
}
inline void									TexProject::GUI::Item::SetAction(ActionType type_,Action action_)
{
	action[(uint32)type_] = action_;
}
inline TexProject::GUI::Item::Action		TexProject::GUI::Item::GetAction(ActionType type_) const
{
	return action[(uint32)type_];
}
#pragma endregion
#pragma endregion
#pragma region Panel
#pragma region Child
template<typename T>
inline typename T*							TexProject::GUI::Panel::AddItem()
{
	T* t = new T(gui,this);
	item.push_back((Item*)t);
	return t;
}
inline void									TexProject::GUI::Panel::RemoveItem(Item* item_)
{
	auto t = std::find(item.begin(),item.end(),item_);
	if(t != item.end())
	{
		delete *t;
		item.erase(t);
	}
}
#pragma endregion
#pragma endregion
#pragma region Panels
#pragma region Default
#pragma endregion
#pragma region Image
#pragma endregion
#pragma region Text
inline void														TexProject::GUI::Panels::Text::SetTextSize(uint32 size_)
{
	textSize = size_;
}
inline void														TexProject::GUI::Panels::Text::SetText(const string& text_)
{
	text = text_;
}
inline TexProject::string										TexProject::GUI::Panels::Text::GetText() const
{
	return "";//text;
}
inline void														TexProject::GUI::Panels::Text::EnableTextSelecting()
{
	properties |= (uint32)PropertiesBit::Selecting;
}
inline void														TexProject::GUI::Panels::Text::DisableTextSelecting()
{
	properties &= ~(uint32)PropertiesBit::Selecting;
}
inline bool														TexProject::GUI::Panels::Text::IsTextSelectable() const
{
	return (properties & (uint32)PropertiesBit::Selecting) > 0;
}
inline void														TexProject::GUI::Panels::Text::EnableTextEditing()
{
	properties |= (uint32)PropertiesBit::Editing;
}
inline void														TexProject::GUI::Panels::Text::DisableTextEditing()
{
	properties &= ~(uint32)PropertiesBit::Editing;
}
inline bool														TexProject::GUI::Panels::Text::IsTextEditable() const
{
	return (properties & (uint32)PropertiesBit::Editing) > 0;
}
inline void														TexProject::GUI::Panels::Text::EnableTextSingleline()
{
	properties |= (uint32)PropertiesBit::Singleline;
}
inline void														TexProject::GUI::Panels::Text::DisableTextSingleline()
{
	properties &= ~(uint32)PropertiesBit::Singleline;
}
inline bool														TexProject::GUI::Panels::Text::IsTextSingleline() const
{
	return (properties & (uint32)PropertiesBit::Singleline) > 0;
}
#pragma endregion
#pragma endregion
#pragma region Buttons
#pragma region Default
#pragma endregion
#pragma region Trigger
inline void									TexProject::GUI::Buttons::Trigger::SetState(bool state_)
{
	state = state_;
}
inline bool									TexProject::GUI::Buttons::Trigger::GetState() const
{
	return state;
}
#pragma endregion
#pragma region Switcher
inline void									TexProject::GUI::Buttons::Switcher::SetState(uint32 state_)
{
	if(state_ < maxState) state = state_;
}
inline uint32								TexProject::GUI::Buttons::Switcher::GetState() const
{
	return state;
}
inline void									TexProject::GUI::Buttons::Switcher::SetMaxState(uint32 maxState_)
{
	if(maxState > 0) maxState = maxState_;
	if(state >= maxState) state = 0;
}
inline uint32								TexProject::GUI::Buttons::Switcher::GetMaxState() const
{
	return maxState;
}
#pragma endregion
#pragma region Slider
inline void									TexProject::GUI::Buttons::Slider::SetValue(float32 value_)
{
	value = value_;
}
inline float32								TexProject::GUI::Buttons::Slider::GetValue() const
{
	return value;
}
#pragma endregion
#pragma region Connector
inline void														TexProject::GUI::Buttons::Connector::SetTarget(Connector* connector)
{
	SetRecipient();
	if(target) target->observers.remove(this);
	target = nullptr;
	if(connector)
	{
		checkConnector = connector;
		checkValidate = true;
		CallAction(ActionType::Check);
		if(checkValidate)
		{
			target = connector;
		}
		checkConnector = nullptr;
		checkValidate = false;
	}
	else
	{
		target = connector;
	}
	if(target) target->observers.push_back(this);
}
inline void														TexProject::GUI::Buttons::Connector::UnsetTarget()
{
	if(target) target->observers.remove(this);
	target = nullptr;
}
inline void														TexProject::GUI::Buttons::Connector::SetRecipient()
{
	//if(!recipient)
	if(!IsRecipient())
	{
		FlushTargeting();
		//recipient = true;
		properties |= (uint32)PropertiesBit::Recipient;
		target = nullptr;
	}
}
inline void														TexProject::GUI::Buttons::Connector::UnsetRecipient()
{
	//if(recipient)
	if(IsRecipient())
	{
		properties &= ~(uint32)PropertiesBit::Recipient;
		FlushTargeting();
	}
}
inline bool														TexProject::GUI::Buttons::Connector::IsRecipient() const
{
	return (properties & (uint32)PropertiesBit::Recipient) > 0;
}
inline void														TexProject::GUI::Buttons::Connector::FlushTargeting()
{
	for(auto i: observers) i->target = nullptr;
	observers.clear();
}
inline TexProject::GUI::Buttons::Connector*						TexProject::GUI::Buttons::Connector::GetTarget() const
{
	//return recipient ? target : nullptr;
	return IsRecipient() ? target : nullptr;
}
inline void														TexProject::GUI::Buttons::Connector::RefreshObservers()
{
	for(auto i: observers) i->CallAction(ActionType::Refresh);
}
#pragma endregion
#pragma endregion
#pragma region GUIBind
inline										TexProject::GUIBind::GUIBind(GUI* gui_):
	gui(gui_)
{
}
inline TexProject::GUI*						TexProject::GUIBind::GetGUI() const
{
	return gui;
}
#pragma endregion
#pragma region Mouse
inline										TexProject::GraphicUserInterface::Mouse::Mouse(GUI* gui_):
	GUIBind(gui_)
{
}
inline void									TexProject::GraphicUserInterface::Mouse::Process()
{
	opos = pos;
	pos = MousePos();
	dpos = pos - opos;

	olstate = lstate; lstate = MouseLState();
	orstate = rstate; rstate = MouseRState();
	omstate = mstate; mstate = MouseMState();

	auto p = gui->GetRenderContext()->GetWindow()->GetPos();

	locopos = opos - p;
	locpos = pos - p;
	locdpos = dpos - p;
}
#pragma endregion
#pragma region GUI
#pragma region Item Processing
template<typename T>
inline typename T*							TexProject::GraphicUserInterface::AddItem()
{
	T* t = new T(this);
	item.push_back((Item*)t);
	return t;
}
inline void									TexProject::GraphicUserInterface::RemoveItem(Item* item_)
{
	auto t = std::find(item.begin(),item.end(),item_);
	if(t != item.end())
	{
		delete *t;
		item.erase(t);
	}
}
#pragma endregion
#pragma region Dragging
inline void									TexProject::GraphicUserInterface::DraggingProcess()
{
	draggingSelection = nullptr;

	for(auto i: item)
	{
		auto t = i->GetSelection();
		if(t)
		if(!draggingSelection || (*draggingSelection->GetBase() < *t->GetBase()))	//t->GetBase()->GetPriority() > draggingSelection->GetBase()->GetPriority())
		{
			draggingSelection = t;
		}
	}

	if(draggingPick)
	{
		if(renderContext->GetWindow()->IsActive() && mouse.lstate && draggingCan && draggingPick->IsDraggable() && draggingPick->GetBase()->IsDraggable())
		{
			draggingPick->GetBase()->AddPos(vec2(mouse.dpos));
		}
		else
		{
			draggingPick = nullptr;
		}
	}
	else
	{
		if(mouse.lstate && !mouse.olstate)
		if(draggingSelection && draggingSelection->IsDraggable())
		{
			draggingPick = draggingSelection;
			draggingCan = draggingPick->CanDrag();
			ToTop(draggingPick);
		}
	}
}
inline void									TexProject::GraphicUserInterface::ToTop(Item* item_)
{
	auto t = item_;
	if(item_->IsTopMost())
	{
		for(auto i: item) if(i->IsTopMost() && i->GetPriority() > t->GetPriority()) t = i;
	}
	else
	{
		for(auto i: item) if(!i->IsTopMost() && i->GetPriority() > t->GetPriority()) t = i;
	}
	if((t->GetPriority()-item_->GetPriority()) >= 0) item_->SetPriority(t->GetPriority() + 1);
}
#pragma endregion
#pragma endregion
#pragma endregion


















