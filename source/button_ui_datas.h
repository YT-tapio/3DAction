#pragma once

class ButtonUIDatas
{
public:

	~ButtonUIDatas() = default;

	static ButtonUIDatas& GetInstance()
	{
		static ButtonUIDatas instance;
		return instance;
	}

	void Awake();

	void End();

	const int GetHandle(const std::string& name) const;

private:

	ButtonUIDatas();

	void LoadFile();

private:

	std::unordered_map<std::string, int> button_ui_handles_;

};