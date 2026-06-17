#pragma once

class IUIObject;

class UIGroup
{
public:


	UIGroup();

	~UIGroup();

	virtual void Awake();

	virtual void Init();

	virtual void Update();

	virtual const void Draw() const;

protected:

	virtual void LoadFile();

private:

	VECTOR pos_;		// ç¿ïW
	VECTOR scale_;		// ëÂÇ´Ç≥

	std::vector<std::shared_ptr<IUIObject>> ui_objects_;
};