#pragma once
#include"popup_ui_holder_base.h"

class ImagePopupUI : public PopupUIHolderBase
{
public:

	ImagePopupUI(const std::string& image_name);

	~ImagePopupUI() override;
	
	void Spawn(const VECTOR& base_pos, const int& size);



private:

	std::string image_name_;


};