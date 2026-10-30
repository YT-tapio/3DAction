#pragma once
#include"string_ui.h"

class AvoidStringUI : public StringUI
{
public:

	AvoidStringUI();

	~AvoidStringUI() override;

	const void Draw() const override;

private:

};