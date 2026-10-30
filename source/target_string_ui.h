#pragma once
#include"string_ui.h"

class TargetStringUI : public StringUI
{
public:

	TargetStringUI();
	
	~TargetStringUI() override;

	const void Draw() const override;

private:



};
