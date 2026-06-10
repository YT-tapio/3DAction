#pragma once

class HPFrame : public Object2D
{
public:
	HPFrame(const ImageData& data, const VECTOR& pos,float size_rate, float rot);

	~HPFrame() override;

	void Init() override;

	void Update() override;

	void Debug() override;

private:



};