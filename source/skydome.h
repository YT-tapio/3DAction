#pragma once

class Object3D;

class SkyDome : public Object3D
{
public:

	SkyDome();

	~SkyDome();

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:




};