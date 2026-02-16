#pragma once

class IInput
{
public:
	virtual ~IInput() = default;
	virtual void Update();
};