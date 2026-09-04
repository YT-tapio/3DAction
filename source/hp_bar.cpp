#include<string>
#include<vector>
#include<memory>
#include<sstream>
#include<fstream>
#include<functional>
#include"hp_bar.h"
#include"object_base.h"
#include"image_data.h"
#include"object_2D.h"
#include"hp_background.h"
#include"hp_frame.h"
#include"hp_body.h"
#include"vector_assistant.h"
#include"csv_file_assistant.h"
#include"animator_2d.h"

HPBar::HPBar(const std::string path, std::function<int()> get_base_hp, std::function<int()> get_current_hp)
{
	LoadFile(path,get_base_hp,get_current_hp);
}

HPBar::~HPBar()
{
	ui_.clear();
}

void HPBar::Init()
{
	for (auto& ui : ui_)
	{
		ui->Init();
	}
}

void HPBar::Update()
{
	for (auto& ui : ui_)
	{
		ui->Update();
	}
}

void HPBar::Draw()
{
	for (const auto& ui : ui_)
	{
		ui->Draw();
	}
}

void HPBar::LoadFile(const std::string path, std::function<int()> get_base_hp, std::function<int()> get_current_hp)
{
	std::ifstream file(path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		int id = -1;
		ImageData image_data = {};
		VECTOR pos		= VectorAssistant::VGetZero();
		float size_rate	= -1.f;
		float rot_z			= -1.f;
		
		id					= CSVFileAssistant::GetIntOfCSVFile(ss, data);
		image_data.path	= CSVFileAssistant::GetStringOfCSVFile(ss,data);
		image_data.width = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		image_data.height = CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		pos				= CSVFileAssistant::GetVector2DOfCSVFile(ss, data);
		size_rate		= CSVFileAssistant::GetFloatOfCSVFile(ss, data);
		rot_z				= CSVFileAssistant::GetFloatOfCSVFile(ss, data);

		switch (id)
		{
		case 0:
			ui_.emplace_back(std::make_shared<HPBackGround>(image_data, pos, size_rate, rot_z));
			break;

		case 1:
			ui_.emplace_back(std::make_shared<HPBody>(image_data, pos, size_rate, rot_z,get_base_hp,get_current_hp));
			break;

		case 2:
			ui_.emplace_back(std::make_shared<HPFrame>(image_data, pos, size_rate, rot_z));
			break;
		}
	}
}