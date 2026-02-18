#pragma once

class IInput;

class InputBase
{
public:

	InputBase();

	virtual ~InputBase();

	virtual void Init();

	virtual void Update();

	virtual const bool IsDash() const;

	virtual const VECTOR GetMoveDir() const;

protected:


private:



};
