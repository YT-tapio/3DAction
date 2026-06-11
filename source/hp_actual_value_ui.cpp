#include<functional>
#include<string>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"string_ui.h"
#include"hp_actual_value_ui.h"
#include"csv_file_assistant.h"
#include"color.h"


HPActualValueUI::HPActualValueUI(const std::string& file_path,std::function<int()> get_current_hp)
	: StringUI(file_path)
	, get_current_hp_(get_current_hp)
{
	LoadFile(file_path);
}

HPActualValueUI::~HPActualValueUI()
{
	
}

void HPActualValueUI::Init()
{

}

const void HPActualValueUI::Draw() const
{
	DrawFormatStringToHandle(static_cast<int>(pos_.x), static_cast<int>(pos_.y), color_, font_handle_, "HPÅ@Å@%d", get_current_hp_());
}
