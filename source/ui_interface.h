#pragma once

class IUIObject
{
public:

	virtual ~IUIObject() = default;

	virtual void Init();

	virtual void Update();

	virtual const void Draw() const;
};