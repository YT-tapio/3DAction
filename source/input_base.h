#pragma once

class IInput;

class InputBase
{
public:

	InputBase();

	virtual ~InputBase();

	virtual void Init();

	virtual void Update();


protected:

	std::vector<std::shared_ptr<IInput>> inputs_;


private:



};
