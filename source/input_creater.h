#pragma once

class IInput;

class InputCreater
{
public:

	static InputCreater& GetInstance()
	{
		static InputCreater instance;
		return instance;
	}

	InputCreater(const InputCreater&) = delete;
	InputCreater& operator = (const InputCreater&) = delete;

	void Awake();

	std::vector<std::shared_ptr<IInput>> Create();

private:

	bool is_first_;
	int all_num_;

	InputCreater();

};