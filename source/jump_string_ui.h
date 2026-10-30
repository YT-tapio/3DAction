#pragma once
#include"string_ui.h"

class JumpStringUI : public StringUI
{
public:

	JumpStringUI();

	~JumpStringUI() override;

	const void Draw() const override;

private:


};