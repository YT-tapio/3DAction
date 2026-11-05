#pragma once

class FontData
{
public:

	static FontData& GetInstance()
	{
		static FontData instance;
		return instance;
	}

	FontData(const FontData&) = delete;
	FontData& operator = (const FontData&) = delete;
	
	void Awake();

	// ƒŠƒ\[ƒX‚ğíœ
	void DeleteHandle();

	const int GetHandle(const std::string name) const;

private:

	FontData();

private:

	std::unordered_map<std::string, int> font_handles_;


};