#pragma once

// HPの実数値を描画するui
class HPActualValueUI : public StringUI
{
public:
	
	HPActualValueUI(const std::string& file_path,std::function<int()> get_current_hp);
	
	~HPActualValueUI() override;

	void Init() override;

	const void Draw() const override;

private:

	// 関数ポインタで値を受け取る
	std::function<int()> get_current_hp_;

};