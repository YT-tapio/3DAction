#pragma once

namespace Draw2D
{
	/// <summary>
	/// boxを描画
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="color"></param>
	/// <param name="alpha"></param>
	inline void Box(const VECTOR& pos, int width, int height, int color, const bool alpha)
	{
		DrawBox(static_cast<int>(pos.x - (float(width) * 0.5f)),
			static_cast<int>(pos.y - (float(height) * 0.5f)),
			static_cast<int>(pos.x + (float(width) * 0.5f)),
			static_cast<int>(pos.y + (float(height) * 0.5f)),
			color, alpha);
	}

	/// <summary>
	/// 丸を描画
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="radius"></param>
	/// <param name="color"></param>
	/// <param name="alpha"></param>
	inline void Circle(const VECTOR& pos, const float& radius, int color, bool alpha)
	{
		DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), radius, color, alpha);
	}

	/// <summary>
	/// エッジ付きの文字を描画
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="string"></param>
	/// <param name="handle"></param>
	/// <param name="font_color"></param>
	/// <param name="edge_color"></param>
	inline void EdgeStringToHandle(const VECTOR& pos, const char* string, const int& handle, const int& font_color, const int& edge_color)
	{
		DrawStringToHandle(static_cast<int>(pos.x), static_cast<int>(pos.y), string, font_color, handle, edge_color);
	}

	/// <summary>
	/// 画像のサイズを変えることができる
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="data"></param>
	/// <param name="alpha"></param>
	inline void ExtendGraph(const VECTOR& pos, int width, int height, const int& data, const bool alpha)
	{
		DrawExtendGraph(static_cast<int>(pos.x - (float(width) * 0.5f)),
			static_cast<int>(pos.y - (float(height) * 0.5f)),
			static_cast<int>(pos.x + (float(width) * 0.5f)),
			static_cast<int>(pos.y + (float(height) * 0.5f)),
			data, alpha);
	}

	/// <summary>
	/// 回転とサイズを指定できる
	/// </summary>
	/// <param name="pos">中心</param>
	/// <param name="size_rate"></param>
	/// <param name="rot_z">ラジアン角</param>
	/// <param name="data"></param>
	/// <param name="alpha"></param>
	inline void RotaGraph(const VECTOR& center_pos, float size_rate,float rot_z,const int& data, const bool alpha)
	{
		DrawRotaGraph(static_cast<int>(center_pos.x), static_cast<int>(center_pos.y),
			size_rate, rot_z, data, alpha);
	}

	/// <summary>
	/// 透過を行う
	/// </summary>
	/// <param name="draw">描画のポインタ関数</param>
	/// <param name="alpha_num"></param>
	inline void Blend(std::function<void()> draw,int alpha_num)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha_num));
		draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}