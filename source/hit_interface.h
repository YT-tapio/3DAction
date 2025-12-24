#pragma once
#include<iostream>

class IHit : public std::enable_shared_from_this<IHit>
{
public:
	virtual ~IHit() = default;
	virtual void OnHit(std::shared_ptr<IHit> object) = 0;
	
};