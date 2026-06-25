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
	/// <param name="thickness"></param>
	inline void Circle(const VECTOR& pos, const float& radius, int color, bool alpha,int thickness = 1)
	{
		DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), radius, color, alpha,thickness);
	}

	/// <summary>
	/// 円形上に画像を切り抜く、画像は正方形
	/// </summary>
	/// <param name="pos">中心座標</param>
	/// <param name="percent">円の角度の割合(1～0)</param>
	/// <param name="handle">画像</param>
	/// <param name="start_percent">初期の円の角度,指定しなかったら0(1～0)</param>
	/// <param name="scale">大きさ</param>
	/// <param name="reverse_x">回転</param>
	/// <param name="reverse_y">回転</param>
	inline void CircleGauge(const VECTOR& center_pos, float percent,const int handle,float start_percent = 0.f,
		float scale = 1.f,int reverse_x = 0, int reverse_y = 0)
	{
		DrawCircleGauge(static_cast<int>(center_pos.x), static_cast<int>(center_pos.y), static_cast<double>(percent * 100),
			handle, static_cast<double>(start_percent * 100), static_cast<double>(scale), reverse_x, reverse_y);
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
	/// 文字列(数値なし)
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="string"></param>
	/// <param name="color"></param>
	/// <param name="handle"></param>
	/// <param name="edge_color"></param>
	inline void StringToHandle(const VECTOR& pos, std::string string, unsigned int color,int handle,int edge_color = -1)
	{
		if (edge_color != -1)
		{
			DrawStringToHandle(static_cast<int>(pos.x), static_cast<int>(pos.y), string.c_str(), color, handle,edge_color);
		}
		else
		{
			DrawStringToHandle(static_cast<int>(pos.x), static_cast<int>(pos.y), string.c_str(), color, handle);
		}
		
	}

	/// <summary>
	/// 文字列(数値も描画)
	/// </summary>
	/// <typeparam name="T">int,float,double</typeparam>
	/// <param name="pos"></param>
	/// <param name="string"></param>
	/// <param name="color"></param>
	/// <param name="handle"></param>
	/// <param name="t"></param>
	template <typename T>
	inline void FormatStringToHandle(const VECTOR& pos, std::string string, int color, int handle,const T& t)
	{
		DrawFormatStringToHandle(static_cast<int>(pos.x), static_cast<int>(pos.y), color, handle, string.c_str(), t);
	}

	/// <summary>
	/// 透過を行う
	/// </summary>
	/// <param name="draw">描画のポインタ関数</param>
	/// <param name="alpha_num"></param>
	inline void Blend(std::function<void()> draw,int alpha_num)
	{
		// 完全に透過だと早期リターン
		if (alpha_num == 0) { return; }
		if (alpha_num >= 255) 
		{
			draw();
			return;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_num);
		draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}