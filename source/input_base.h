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

	virtual const bool IsPunch() const;

	virtual const bool IsAvoid() const;

	virtual const VECTOR GetMoveDir() const;

	virtual const VECTOR GetCameraDir() const;

	virtual const VECTOR GetCameraVelocity() const;

protected:


private:



};
