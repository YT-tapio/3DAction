#pragma once
#include"popup_ui_holder_base.h"

class ImagePopupUI : public PopupUIHolderBase
{
public:

	ImagePopupUI();

	~ImagePopupUI() override;
	
	void Spawn(const VECTOR& base_pos, const std::string& image_name, const float& size);

private:

};