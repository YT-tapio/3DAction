#pragma once

class SubScreen
{
public:

	SubScreen(int screen_width, int screen_height);

	~SubScreen();


	void Init();

	/// <summary>
	/// スクリーンを起動
	/// </summary>
	void Up();

	/// <summary>
	/// スクリーンを閉じる(元のスクリーンに戻る)
	/// </summary>
	void Down();

	/// <summary>
	/// よこ
	/// </summary>
	/// <returns>screen_width_</returns>
	const int GetScreenWidth() const;

	/// <summary>
	/// たて
	/// </summary>
	/// <returns>screen_height_</returns>
	const int GetScreenHeight() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns>handle_</returns>
	const int GetHandle() const;

private:

	int handle_;
	int screen_width_;
	int screen_height_;



};