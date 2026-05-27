#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include"animation_data.h"
#include<unordered_map>
#include"DxLib.h"
#include"animator_enemy.h"
#include"enemy_base.h"

AnimatorEnemy::AnimatorEnemy(int handle,  std::shared_ptr<EnemyBase> enemy,std::string data_name)
	:AnimatorBase("enemy/" + data_name,handle)
{
	enemy_ = enemy;
}

AnimatorEnemy::~AnimatorEnemy()
{

}

void AnimatorEnemy::ChangeAnimation()
{
	const std::string kOnDamage = "on_damage";
	const std::string kDoublePunch = "double_punch";
	const std::string kJumpingAttack = "jumping_attack";
	before_anim_name_ = now_anim_name_;
	
	PlayRequest("idle");
	std::map<int, std::string, std::greater<int>> request_name_priority_mp;
	if (!request_names_.empty())
	{
		//printfDx("--------------\n");
		for (auto& request_name : request_names_)
		{
			int priority = animation_datas_[request_name].priority;
			request_name_priority_mp[priority] = request_name;
			//printfDx("%s\n", request_name.c_str());
		}
	}

	// request‚Ì’†‚Å‚àpriority‚Ì‚½‚©‚¢‚à‚Ì‚ðŽæ‚éB
	if (!request_name_priority_mp.empty()) { now_anim_name_ = request_name_priority_mp.begin()->second; }
}