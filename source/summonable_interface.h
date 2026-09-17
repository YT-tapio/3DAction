#pragma once

class ISummonable
{
public:

	virtual ~ISummonable() = default;

	virtual void Summon(const VECTOR& pos) = 0;
};