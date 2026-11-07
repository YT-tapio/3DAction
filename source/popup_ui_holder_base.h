#pragma once

class PopupUI;

class PopupUIHolderBase
{
public:

	PopupUIHolderBase();

	virtual ~PopupUIHolderBase();

	virtual void Init();

	virtual void Update();

	virtual const void Draw() const;

	const int GetIsActive() const;

protected:

	std::shared_ptr<PopupUI> popup_ui_;

private:


};
