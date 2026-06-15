#pragma once


class HPBackGround : public Object2D
{
public:

	HPBackGround(const ImageData& data,const VECTOR& pos, float size_rate,float rot);

	~HPBackGround() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:


};