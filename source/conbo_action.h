#pragma once
#include"behavior_base.h"

class ObjectBase;
class Conbo;

class ConboAction : public BehaviorBase
{
public:

	ConboAction(std::weak_ptr<ObjectBase>owner,std::unordered_map<int,std::shared_ptr<Conbo>> conbos);

	~ConboAction() override;

	void Init() override;

	void Update() override;
	
	void Draw() override;
	
	void Debug() override;


private:

	std::unordered_map<int, std::shared_ptr<Conbo>> conbos_;

	int current_conbo_;
};