#include<string>
#include<memory>
#include"DxLib.h"
#include"image_popup_ui.h"
#include<unordered_map>
#include"image_repository.h"
#include"popup_ui.h"

ImagePopupUI::ImagePopupUI(const std::string& image_name)
	: PopupUIHolderBase()
	, image_name_(image_name)
{
	
}

ImagePopupUI::~ImagePopupUI()
{
	
}

void ImagePopupUI::Spawn(const VECTOR& base_pos, const int& size)
{
	popup_ui_->Spawn(base_pos, ImageRepository::GetInstance().GetHandle(image_name_), size);
}