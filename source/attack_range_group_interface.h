#pragma once

class IAttackRangeGroup
{
public:

	virtual ~IAttackRangeGroup() = default;

	virtual int CircleDrawRequest(const VECTOR& pos, const VECTOR& scale, const float& time, std::function<bool()>end_function);

	virtual int RectangleDrawRequest(const VECTOR& pos, const VECTOR& scale, const VECTOR& dir, const float& time, std::function<bool()> end_function);

	virtual void CircleSetPos(const int& id, const VECTOR& pos);

	virtual void RectangleSetPos(const int& id, const VECTOR& pos);

	virtual void RectangleSetDir(const int& id, const VECTOR& dir);
};