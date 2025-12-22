#pragma once

class ObjectBase
{
public:

	ObjectBase();
	
	virtual ~ObjectBase();
	
	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void  Debug();

protected:

	VECTOR pos_;
	VECTOR rot_;

private:

	

};