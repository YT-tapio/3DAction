#pragma once

class PopupUI;
class SubScreen;

/// <summary>
/// ”’l‚ğ•\¦‚·‚éUI
/// </summary>
class NumberPopupUI
{
public:

	NumberPopupUI(const int& color, const int& dedge_color);

	~NumberPopupUI();

	void Init();

	void Update();

	void Draw();

	void Spawn(const VECTOR& base_pos,const int& damage);

private:

	void MakeHandle(const int& damage);

private:

	std::shared_ptr<SubScreen> sub_screen_;
	std::shared_ptr<PopupUI> popup_ui_;

	int color_;
	int edge_color_;

};