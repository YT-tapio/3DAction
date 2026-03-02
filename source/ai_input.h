#pragma once
#include<vector>
#include<memory>
#include"input_base.h"

class AIInput : public InputBase
{
public:

	AIInput();

	~AIInput();

	void Init() override;

	void Update() override;

	const bool IsDash() const override;

	const VECTOR GetMoveDir() const override;

	const VECTOR GetCameraDir() const override;

private:



};