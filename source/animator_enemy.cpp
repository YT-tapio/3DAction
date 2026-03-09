#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"animator_enemy.h"

AnimatorEnemy::AnimatorEnemy(const char* data_file_path, int handle)
	:AnimatorBase("data/csv/animation/enemy_animation.csv",handle)
{

}

AnimatorEnemy::~AnimatorEnemy()
{

}

void AnimatorEnemy::Update()
{

}