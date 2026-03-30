#pragma once

// この中に操作のボタンを割り当てる
// intで値を持って置き、カスタマイズしたい時に変えられるように
namespace KeyConfig
{
	static int move_front	= KEY_INPUT_W;
	static int move_back	= KEY_INPUT_S;
	static int move_right	= KEY_INPUT_D;
	static int move_left	= KEY_INPUT_A;
	static int dash			= KEY_INPUT_LSHIFT;		// ダッシュ
	static int punch		= 0;
	static int jump			= KEY_INPUT_SPACE;		// ジャンプ
	static int avoid		= 1;
}