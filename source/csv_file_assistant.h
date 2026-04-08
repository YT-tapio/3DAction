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
	/// std::stringを受け取る
	/// </summary>
	/// <param name="ss"></param>
	/// <param name="data"></param>
	/// <returns>文字列</returns>
	inline float GetIntOfCSVFile(std::stringstream& ss, std::string& data)
	{
		int value = 0;

		std::getline(ss, data, ',');
		value = stoi(data);

		return value;
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
	inline float GetBoolOfCSVFile(std::stringstream& ss, std::string& data)
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

}

