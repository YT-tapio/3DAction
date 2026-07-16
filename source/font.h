#pragma once

namespace Font
{

	/// <summary>
	/// 
	/// </summary>
	/// <param name="file_path"></param>
	/// <param name="font_name"></param>
	/// <param name="size"></param>
	/// <param name="edge"></param>
	/// <param name="font_type">>
	/// DX_FONTTYPE_NORMAL　　　　　　		: ノーマルフォント
	/// DX_FONTTYPE_EDGE　　　　　　　　	: エッジつきフォント
	/// DX_FONTTYPE_ANTIALIASING　　　　	: アンチエイリアスフォント
	/// DX_FONTTYPE_ANTIALIASING_4X4　　　	: アンチエイリアスフォント(4x4サンプリング)
	/// DX_FONTTYPE_ANTIALIASING_8X8　　	: アンチエイリアスフォント(8x8サンプリング)
	/// DX_FONTTYPE_ANTIALIASING_EDGE_4X4　 : アンチエイリアス＆エッジ付きフォント(4x4サンプリング)
	/// DX_FONTTYPE_ANTIALIASING_EDGE_8X8　 : アンチエイリアス＆エッジ付きフォント(8x8サンプリング) </param>
	/// <returns>フォントのデータ</returns>
	inline int CreatFontHandle(const std::string& file_path,const std::string& font_name,int size,int edge,int font_type)
	{
		int handle = -1;
		AddFontResourceExA(file_path.c_str(), FR_PRIVATE, nullptr);
		handle = CreateFontToHandle(font_name.c_str(), size, edge, font_type);
		return handle;
	}

	/// <summary>
	/// ファイルからフォントデータを作る
	/// </summary>
	/// <param name="file_path"></param>
	/// <returns></returns>
	inline int CreateHandleOfFile(const std::string& file_path)
	{
		int handle = -1;
		std::ifstream file(file_path);
		std::string line;

		if (!file)
		{
			printfDx("csvファイル読み込み失敗\n");
		}
		// 最初の行を飛ばす
		std::getline(file, line);

		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string data;			// csvからの文字列をもらう

			std::string font_file_path = CSVFileAssistant::GetStringOfCSVFile(ss, data);
			std::string font_name = CSVFileAssistant::GetStringOfCSVFile(ss, data);
			int size = CSVFileAssistant::GetIntOfCSVFile(ss, data);
			int edge = CSVFileAssistant::GetIntOfCSVFile(ss, data);
			int type = CSVFileAssistant::GetIntOfCSVFile(ss, data);
			handle = Font::CreatFontHandle(font_file_path.c_str(), font_name.c_str(), size, edge, type);
		}

		return handle;
	}

	/// <summary>
	/// 1文字の大きさ
	/// </summary>
	/// <param name="handle"></param>
	/// <returns></returns>
	inline int GetFontSize(int handle)
	{
		TCHAR* name;
		int size;
		int thick;
		GetFontStateToHandle(name, &size, &thick, handle);
		return size;
	}

	/// <summary>
	/// 外枠の大きさ
	/// </summary>
	/// <param name="handle"></param>
	/// <returns></returns>
	inline int GetFontThick(int handle)
	{
		TCHAR* name;
		int size;
		int thick;
		GetFontStateToHandle(name, &size, &thick, handle);
		return thick;
	}

}