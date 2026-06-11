#include<string>
#include"DxLib.h"
#include"string_ui.h"
#include"character_name_ui.h"
#include<functional>
#include"draw_2D.h"

CharacterNameUI::CharacterNameUI(const std::string& file_path, const std::string& name)
	: StringUI(file_path)
	, name_(name)
{

}

CharacterNameUI::~CharacterNameUI()
{

}

void CharacterNameUI::Init()
{

}

void CharacterNameUI::Update()
{

}

const void CharacterNameUI::Draw() const
{
	Draw2D::StringToHandle(pos_, name_, GetColor(255, 255, 255), font_handle_);
}