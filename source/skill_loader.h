#pragma once
#include"skill_type.h"

class SkillBase;
class Player;

namespace SkillLoader
{
	std::shared_ptr<SkillBase> SkillLoad(const int skill_name, const std::string name, std::weak_ptr<Player> owner, SkillType type);
}