#pragma once
#include<vector>
#include<memory>
#include"input_base.h"

class PC;
class Pad;

class PlayerInput : public InputBase
{
public:

	PlayerInput();

	~PlayerInput() override;

	void Init() override;

	void Update() override;

	bool IsDash() override;

	VECTOR GetMoveDir() override;

private:

	VECTOR MoveDirPC(std::shared_ptr<PC> pc);

	VECTOR MoveDirPad(std::shared_ptr<Pad> pad);
};