#pragma once
#include"popup_ui_holder_base.h"

class PopupUI;
class SubScreen;

/// <summary>
/// ”’l‚ğ•\¦‚·‚éUI
/// </summary>
class NumberPopupUI : public PopupUIHolderBase
{
public:

	NumberPopupUI(const int& color, const int& dedge_color);

	~NumberPopupUI() override;

	void Init() override;

	void Spawn(const VECTOR& base_pos,const int& damage,const bool& is_critical = FALSE);

private:

	void MakeHandle(const int& damage, const bool& is_critical);

private:

	std::shared_ptr<SubScreen> sub_screen_;
	std::shared_ptr<PopupUI> popup_ui_;

	int color_;
	int edge_color_;

};