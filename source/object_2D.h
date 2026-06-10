#pragma once

struct ImageData;

class Object2D : public ObjectBase
{
public:

	Object2D(const ImageData data,const VECTOR& pos, float size_rate, float rot);

	~Object2D() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	int handle_;

	ImageData data_;

	float size_rate_;

private:


};