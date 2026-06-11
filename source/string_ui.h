#pragma once

//•¶š—ñ‚ğ•`‰æ‚·‚éUI
class StringUI
{
public:

	StringUI(const std::string& data_file_path);

	virtual ~StringUI();

	virtual void Init();

	virtual void Update();

	virtual const void Draw() const;

protected:

	void LoadFile(const std::string& data_file_path);

protected:

	// ƒtƒHƒ“ƒg
	int font_handle_;

	// •`‰æêŠ
	VECTOR pos_;

private:

	

};