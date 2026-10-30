#pragma once
#include"string_ui.h"

class DashStringUI : public StringUI
{
public:

	DashStringUI();

	~DashStringUI() override;

	const void Draw() const override;

private:


};