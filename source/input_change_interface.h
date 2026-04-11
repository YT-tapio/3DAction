#pragma once
class InputBase;

class IInputChange
{
public:
	virtual ~IInputChange() = default;
	virtual void InputChange(std::shared_ptr<InputBase> input);
};