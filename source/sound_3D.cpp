#include<string>
#include"DxLib.h"
#include"sound_3D.h"
#include<fstream>
#include<sstream>
#include"csv_file_assistant.h"

Sound3D::Sound3D(const std::string& file_path)
{
	LoadFile(file_path);
}

Sound3D::~Sound3D()
{

}

void Sound3D::Init()
{

}

void Sound3D::SetPos(const VECTOR& pos)
{
	pos_ = pos;
	// 
	Set3DPositionSoundMem(pos_, handle_);
}

void Sound3D::LoadFile(const std::string& file_path)
{
	std::ifstream file(file_path);
	std::string line;

	if (!file)
	{
		printfDx("csvファイル読み込み失敗\n");
		return;
	}

	// 最初の行を飛ばす
	std::getline(file, line);
	std::getline(file, line);

	std::string data_file_path;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string data;			// csvからの文字列をもらう

		name_				= CSVFileAssistant::GetStringOfCSVFile(ss, data);
		data_file_path	= CSVFileAssistant::GetStringOfCSVFile(ss, data);
		volume_			= CSVFileAssistant::GetIntOfCSVFile(ss, data);
		loop_					= CSVFileAssistant::GetBoolOfCSVFile(ss, data);
		pos_					= CSVFileAssistant::GetVectorOfCSVFile(ss, data);
		radius_				= CSVFileAssistant::GetFloatOfCSVFile(ss, data);	// 聞こえる範囲
	}

	handle_ = LoadSoundMem(data_file_path.c_str());
	if (handle_ == -1) { printfDx("3Dサウンド読み込み失敗\n"); }

	// ボリュームの設定
	ChangeVolumeSoundMem(volume_, handle_);
	// 範囲の指定
	Set3DRadiusSoundMem(radius_, handle_);
	// 初期座標の設定
	Set3DPositionSoundMem(pos_, handle_);
}
