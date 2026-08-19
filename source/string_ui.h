#pragma once

//•¶š—ñ‚ğ•`‰æ‚·‚éUI
class StringUI
{
public:

	StringUI(const std::string& data_file_path);

	virtual ~StringUI();

	virtual void Init();

	virtual void Update();

	void SetPos(const VECTOR& pos);

	virtual const void Draw() const;

protected:

	void LoadFile(const std::string& data_file_path);

protected:

	// ƒtƒHƒ“ƒg
	int font_handle_;

	unsigned int color_;
	unsigned int edge_color_;
	// •`‰æ‚³‚ê‚é•¶š—ñ
	std::string drawn_string;

	// •`‰æêŠ
	VECTOR pos_;

private:

	

};