#pragma once

class IPlayerGroup
{
public:

	virtual VECTOR* GetCurrentPlayerHeadPos();

	virtual VECTOR* GetCurrentPlayerFrontDir();

	virtual VECTOR MostNearPlayerPos(const VECTOR& other_pos);

};