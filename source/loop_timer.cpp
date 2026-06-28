#include"condition_timer.h"
#include"loop_timer.h"

LoopTimer::LoopTimer(const float& max_time)
	: ConditionTimer(max_time)
{

}

LoopTimer::~LoopTimer()
{

}

void LoopTimer::Init()
{

}

void LoopTimer::Update()
{
	// 1ƒ‹[ƒv‚¾‚¯‚Íis_end_‚ğtrue‚É‚µ‚Ä‚¨‚­
	if (is_end_) { time_ = 0.f; is_end_ = false; }
	ConditionTimer::Update();
}
