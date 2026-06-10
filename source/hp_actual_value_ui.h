#pragma once

// HPの実数値を描画するui
class HPActualValueUI
{
public:
	
	HPActualValueUI(const std::string& file_path,std::function<int()> get_current_hp);
	
	~HPActualValueUI();

	void Init();

	const void Draw() const;

private:

	void LoadFile(const std::string& file_path, std::function<int()> get_current_hp);

private:

	// 関数ポインタで値を受け取る
	std::function<int()> get_current_hp_;
	VECTOR pos_;

	int font_handle_;

};