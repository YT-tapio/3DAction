#include"condition_timer.h"
#include"variable_timer.h"
 
VariableTimer::VariableTimer(float max_time)
	: ConditionTimer(max_time)
{

}

VariableTimer::~VariableTimer()
{

}

void VariableTimer::ChangeMaxTime(float max_time)
{
	//Ž~‚Ü‚Á‚Ä‚¢‚é‚Æ‚«‚É•Ï‚¦‚ê‚é
	if (!is_stop_) { return; }
	max_time_ = max_time;
}
