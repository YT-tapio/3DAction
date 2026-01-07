#pragma once
#include"DxLib.h"
#include"vector_assistant.h"
/// âüÇµñﬂÇµÇçsÇ§
/// velocityÇï‘Ç∑
namespace Resolve
{

	inline VECTOR SegmentPoly(const VECTOR& start_pos,const VECTOR& end_pos,const VECTOR& poly1,const VECTOR& poly2, const VECTOR poly3, const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();


		return offset_vel;
	}

	inline VECTOR SpherePoly(const VECTOR& pos, const VECTOR& velocity, const VECTOR& poly1, const VECTOR& poly2, const VECTOR poly3,const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();


		return offset_vel;
	}

	inline VECTOR CapsulePoly(const VECTOR& start_pos, const VECTOR& end_pos,const VECTOR& velocity, const VECTOR& poly1, const VECTOR& poly2, const VECTOR poly3, const VECTOR& norm)
	{
		VECTOR offset_vel = VectorAssistant::VGetZero();



		return offset_vel;
	}


}