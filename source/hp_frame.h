#pragma once

class HPFrame : public Object2D
{
	HPFrame(const std::string path);

	~HPFrame() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

};