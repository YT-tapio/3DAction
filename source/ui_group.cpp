#include<vector>
#include<memory>
#include"DxLib.h"
#include"ui_group.h"
#include"ui_interface.h"

UIGroup::UIGroup()
{

}

UIGroup::~UIGroup()
{

}

void UIGroup::Awake()
{
	LoadFile();
}

void UIGroup::Init()
{
	if (ui_objects_.size() == 0) { return; }
	for (auto& ui_object : ui_objects_)
	{
		ui_object->Init();
	}
}

void UIGroup::Update()
{
	if (ui_objects_.size() == 0) { return; }
	for (auto& ui_object : ui_objects_)
	{
		ui_object->Update();
	}

}

const void UIGroup::Draw() const
{
	if (ui_objects_.size() == 0) { return; }
	for (const auto& ui_object : ui_objects_)
	{
		ui_object->Draw();
	}
}

void UIGroup::LoadFile()
{

}