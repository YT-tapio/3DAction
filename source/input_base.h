#pragma once

class IInput;

class InputBase
{
public:

	InputBase();

	virtual ~InputBase();

	virtual void Init();

	virtual void Update();

	void Stop();

	void Start();

	virtual const bool IsDash() const;

	virtual const bool IsPunch() const;

	virtual const bool IsAvoid() const;

	virtual const bool IsNormalSkill() const;

	virtual const bool IsStrongSkill() const;

	virtual const bool GoNextScene() const;

	virtual const bool GoResult() const;

	virtual const bool Retry() const;

	virtual const bool GameToTitle() const;

	virtual const VECTOR GetMoveDir() const;

	virtual const VECTOR GetCameraDir() const;

	virtual const VECTOR GetCameraVelocity() const;

protected:

	bool is_stop_;

private:



};
