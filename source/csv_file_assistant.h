#pragma once
#include"vector_assistant.h"

namespace CSVFileAssistant
{

	/// <summary>
	/// std::stringを受け取る
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>文字列</returns>
	inline std::string GetStringOfCSVFile(std::stringstream& ss, std::string& data)
	{
		std::string string = "";

		std::getline(ss, data, ',');
		string = data;

		return string;
	}

	/// <summary>
	/// intのデータを受け取る
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>文字列</returns>
	inline int GetIntOfCSVFile(std::stringstream& ss, std::string& data)
	{
		int value = 0;

		std::getline(ss, data, ',');
		value = stoi(data);

		return value;
	}

	/// <summary>
	/// colorを受け取る(intを三連続受け取っているだけなので注意)
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	inline int GetColorOfCSVFile(std::stringstream& ss, std::string& data)
	{
		int color = -1;

		int red = GetIntOfCSVFile(ss, data);
		int green = GetIntOfCSVFile(ss, data);
		int blue = GetIntOfCSVFile(ss, data);
		color = GetColor(red, green, blue);

		return color;
	}

	/// <summary>
	/// std::stringを受け取る
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>文字列</returns>
	inline float GetFloatOfCSVFile(std::stringstream& ss, std::string& data)
	{
		float value = 0.f;

		std::getline(ss, data, ',');
		value = stof(data);

		return value;
	}

	/// <summary>
	/// std::stringを受け取る
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>文字列</returns>
	inline bool GetBoolOfCSVFile(std::stringstream& ss, std::string& data)
	{
		return GetIntOfCSVFile(ss, data) == 1;
	}

	/// <summary>
	/// csvからvectorを受け取る(三連続でデータを受けっているだけなのでそこに注意)
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>vector</returns>
	inline VECTOR GetVectorOfCSVFile(std::stringstream& ss, std::string& data)
	{
		VECTOR vec = VectorAssistant::VGetZero();

		vec.x = GetFloatOfCSVFile(ss, data);
		vec.y = GetFloatOfCSVFile(ss, data);
		vec.z = GetFloatOfCSVFile(ss, data);

		return vec;
	}

	/// <summary>
	/// csvからvectorを受け取る(二連続でデータを受けっているだけなのでそこに注意)
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>vector</returns>
	inline VECTOR GetVector2DOfCSVFile(std::stringstream& ss, std::string& data)
	{
		VECTOR vec = VectorAssistant::VGetZero();

		vec.x = GetFloatOfCSVFile(ss, data);
		vec.y = GetFloatOfCSVFile(ss, data);

		return vec;
	}

}

