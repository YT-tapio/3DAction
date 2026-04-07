#pragma once

class Player;
class BehaviorBase;

class SkillBase
{
public:

	SkillBase(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behavior);

	virtual ~SkillBase();

	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void Debug();

	void SetOwner(std::weak_ptr<Player>owner);

protected:

	std::weak_ptr<Player> owner_;
	std::shared_ptr<BehaviorBase> behavior_;

	bool is_active_;

	const bool CheckMyOwner() const;

private:



};