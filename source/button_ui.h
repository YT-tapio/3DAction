#pragma once
#include"config_name.h"

class ButtonUI
{
public:

	ButtonUI(const ConfigName& name,const VECTOR& pos, const float& default_size, std::function<void()> execute);

	~ButtonUI();

	void Init();

	void Update();

	void Draw();

private:

	virtual bool CheckMyButton();

private:

	VECTOR pos_;

	std::function<void()> execute_;
	ConfigName name_;

	float default_size_;
	float current_size_;
	float target_size_;

	bool is_execute_;
};