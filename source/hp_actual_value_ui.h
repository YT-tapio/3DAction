#pragma once

// HPの実数値を描画するui
class HPActualValueUI
{
public:
	
	HPActualValueUI(std::function<int()> get_current_hp,const VECTOR& pos);
	
	~HPActualValueUI();

	void Init();

	void Draw();

private:

	// 関数ポインタで値を受け取る
	std::function<int()> get_current_hp_;

};