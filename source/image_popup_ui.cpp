#include<string>
#include<memory>
#include"DxLib.h"
#include"image_popup_ui.h"
#include<unordered_map>
#include"image_repository.h"
#include"popup_ui.h"

ImagePopupUI::ImagePopupUI()
	: PopupUIHolderBase()
{
	
}

ImagePopupUI::~ImagePopupUI()
{
	
}

void ImagePopupUI::Spawn(const VECTOR& base_pos,const std::string& image_name,const float& size)
{
	popup_ui_->Spawn(base_pos, ImageRepository::GetInstance().GetHandle(image_name), size);
}