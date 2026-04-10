#pragma once

struct InputState
{
	int frame		= 0;
	int time			= 0;
	float pushing_time		= 0;	//“ü—Í‚ª‚³‚ê‘±‚¯‚Ä‚¢‚é
	float releasing_time	= 0;	//“ü—Í‚ª‚³‚ê‚Ä‚¢‚È‚¢ŽžŠÔ
	bool is_pressed = false;
};