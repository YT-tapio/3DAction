#include<memory>
#include"DxLib.h"
#include"popup_ui_holder_base.h"
#include"popup_ui.h"

PopupUIHolderBase::PopupUIHolderBase()
	: popup_ui_(std::make_shared<PopupUI>())
{
	
}

PopupUIHolderBase::~PopupUIHolderBase()
{

}

void PopupUIHolderBase::Init()
{
	popup_ui_->Init();
}

void PopupUIHolderBase::Update()
{
	popup_ui_->Update();
}

const void PopupUIHolderBase::Draw() const
{
	popup_ui_->Draw();
}

const int PopupUIHolderBase::GetIsActive() const
{
	return popup_ui_->GetIsActive();
}
