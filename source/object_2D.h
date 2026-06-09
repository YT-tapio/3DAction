#pragma once

class Object2D : public ObjectBase
{
public:

	Object2D(const std::string path);

	~Object2D() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	int handle_;

private:


};