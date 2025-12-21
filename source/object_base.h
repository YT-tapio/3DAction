#pragma once

class ObjectBase
{
public:

	ObjectBase(const VECTOR& pos, const VECTOR& rot);
	
	virtual ~ObjectBase();
	
	virtual void Init();

	virtual void Update();

	virtual void Draw();

protected:

	VECTOR pos_;
	VECTOR rot_;

private:

	

};