#pragma once

class ObjectBase
{
public:

	ObjectBase();
	
	virtual ~ObjectBase();
	
	virtual void Init();

	virtual void Update();

	virtual void LateUpdate();

	virtual void Draw();

	virtual void  Debug();

	const bool GetIsActive() const;

	const VECTOR GetPosition() const;

protected:

	VECTOR pos_;
	VECTOR rot_;

	bool is_active_;

private:

	

};