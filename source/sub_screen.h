#pragma once
#include"screen_size.h"

class SubScreen
{
public:

	SubScreen(int screen_width = kScreenWidth, int screen_height = kScreenHeight);

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
	const int GetWidth() const;

	/// <summary>
	/// たて
	/// </summary>
	/// <returns>screen_height_</returns>
	const int GetHeight() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns>handle_</returns>
	const int GetHandle() const;

	/// <summary>
	/// スクリーン内の中心座標
	/// </summary>
	/// <returns></returns>
	const VECTOR GetCenterPos() const;

private:

	int handle_;
	int width_;
	int height_;

};