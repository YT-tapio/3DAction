#pragma once

#include<string>

class IPlayerGroup
{
public:

	virtual VECTOR* GetCurrentPlayerHeadPos();

	virtual VECTOR* GetCurrentPlayerFrontDir();

	virtual VECTOR GetPlayerPos(const std::string& name);
	
	virtual VECTOR MostNearPlayerPos(const VECTOR& other_pos);

	virtual std::string MostNearPlayerName(const VECTOR& other_pos);
};