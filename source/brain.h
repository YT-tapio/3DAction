#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include<vector>
#include"virtual_camera_base.h"

class Player;
class Shake;
class PlayerGroup;

class Brain
{
public:

	static Brain& GetInstance()
	{
		static Brain instance;
		return instance;
	}

	Brain(const Brain&) = delete;
	Brain& operator = (const Brain&) = default;

	void Init();

	void CreatePlaySceneVirtualCamera(VECTOR* camera_pos, VECTOR* target_pos, std::function<VECTOR()> enemy_center_pos, 
		std::function<VECTOR()> enemy_dir, std::shared_ptr<PlayerGroup> player_group);

	void Update();

	void DeleteVirtualCamera();

	void ChangeCamera(const std::string& request_name);

	void ShakeCamera(const float& power, const float& time);

	void CollisionNotActive();

	void CollisionActive();

	const std::string GetCurrentCameraName() const;

	const VECTOR GetVelocity() const;

	const VECTOR GetTargetVelocity() const;

private:
	
	Brain();

private:

	const std::string kTracking = "tracking";
	const std::string kSphere = "sphere";

	std::vector<std::string> camera_names_;
	std::shared_ptr<Shake> shake_;
	std::string current_camera_;
	std::string before_camera_;

	std::unordered_map<std::string, std::shared_ptr<VirtualCameraBase>> virtual_cameras_;

	VECTOR vel_;
	VECTOR target_vel_;

	bool can_hit_;

};