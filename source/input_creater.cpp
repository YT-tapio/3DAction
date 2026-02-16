#include<vector>
#include<memory>
#include"DxLib.h"
#include"input_interface.h"
#include"pc.h"
#include"pad.h"
#include"input_creater.h"

void InputCreater::Awake()
{
	is_first_ = true;
	all_num_ = 0;
}

std::vector<std::shared_ptr<IInput>> InputCreater::Create()
{
	std::vector<std::shared_ptr<IInput>> inputs;
	all_num_++;
	// ˆê”ÔÅ‰
	if (all_num_ == 1)
	{
		inputs.push_back(std::make_shared<PC>());
		is_first_ = false;
	}
	int pad_num = 0;
	switch (all_num_)
	{
	case 1:
		pad_num = DX_INPUT_PAD1;
		break;

	case 2:
		pad_num = DX_INPUT_PAD2;
		break;

	default:
		printfDx("‚±‚êˆÈã‚Ì’Ç‰Á‚Í”F‚ß‚Ü‚¹‚ñ");
		break;
	}
	inputs.push_back(std::make_shared<Pad>(pad_num));

	return inputs;
}

InputCreater::InputCreater()
	: is_first_(true)
	, all_num_(0)
{
	Awake();
}

