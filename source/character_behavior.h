#pragma once

class BehaviorBase;
class CharacterBase;

class CharacterBehavior : public BehaviorBase
{
public:

	CharacterBehavior(std::weak_ptr<CharacterBase> owner);

	virtual ~CharacterBehavior() override;

	virtual void Init() override;

	virtual void Entry() override;

	virtual BehaviorStatus Update() override;

	virtual void Exit() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	std::weak_ptr<CharacterBase> my_owner_;

private:

	
};