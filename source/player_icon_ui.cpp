#include<memory>
#include<string>
#include<fstream>
#include<sstream>
#include<functional>
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"player_icon_ui.h"
#include"csv_file_assistant.h"
#include<unordered_map>
#include<list>
#include"animator_2d.h"
#include"draw_2D.h"

PlayerIconUI::PlayerIconUI(const std::string& name,std::function<int()> get_current_hp)
	: get_current_hp_(get_current_hp)
	, dark_percent_(0.f)
{
	LoadFile(name);
	animation_ = std::make_shared<Animator2D>("data/csv/test/test_animation.csv");
	animation_->PlayRequest("test");
	effect_pos_ = icon_->GetPosition();
}

PlayerIconUI::~PlayerIconUI()
{

}

void PlayerIconUI::Update()
{
	animation_->Update();
	if (get_current_hp_() > 0)
	{
		dark_percent_ = 0.f;
	}
	else
	{
		dark_percent_ = kDefaultDarkPercent;
	}
}

const void PlayerIconUI::Draw() const
{
	if (get_current_hp_ != nullptr)
	{
		if (get_current_hp_() > 0)
		{
			Draw2D::RotaGraph(VAdd(effect_pos_, VGet(0.f, -10.f, 0.f)), 5.f, 0.f, animation_->GetNowHandle(), TRUE);	
		}
	}
	auto draw = [this]() -> void
		{
			icon_->Draw();
		};
	Draw2D::Dark(draw, dark_percent_);
	
}

void PlayerIconUI::LoadFile(const std::string& name)
{
	std::string data_file_path = "data/csv/ui/player/" + name + "/" + name + "_icon.csv";

	std::ifstream file(data_file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の2行を飛ばす
	std::getline(file, line);
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		ImageData image_data = {};
		image_data.path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
		image_data.width = CSVFileAssistant::GetIntOfCSVFile(ss, data);
		image_data.height = CSVFileAssistant::GetIntOfCSVFile(ss, data);

		VECTOR pos = CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		float size_rate = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		float rot_z = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		icon_ = std::make_shared<Object2D>(image_data, pos, size_rate, rot_z);
	}

}

