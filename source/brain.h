#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include<vector>
#include"virtual_camera_base.h"

class Player;
class Shake;
class Zoom;
class PlayerGroup;
class IEnemyController;

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

	void CreateTitleSceneVirtualCamera(VECTOR* camera_pos, VECTOR* target_pos);

	void CreatePlaySceneVirtualCamera(VECTOR* camera_pos, VECTOR* target_pos, std::shared_ptr<IEnemyController> enemy_controller,std::shared_ptr<PlayerGroup> player_group);

	void Update();

	void DeleteVirtualCamera();

	void ChangeCamera(const std::string& request_name);

	/// <summary>
	/// U“®
	/// </summary>
	/// <param name="power">‚Â‚æ‚³</param>
	/// <param name="time">‚¶‚©‚ñ</param>
	void ShakeCamera(const float& power, const float& time);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="target_fov">–Ú•W‚Ì‹–ìŠp</param>
	/// <param name="time">ŠÔ</param>
	void ZoomCamera(const float& target_fov, const float& time, const float& active_time);

	void CollisionNotActive();

	void CollisionActive();

	void SetCurrentFov(const float& current_fov);

	/// <summary>
	/// fov‚Ì•Ï‰»—Ê
	/// </summary>
	/// <returns></returns>
	const float GetZoomValue() const;

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
	std::shared_ptr<Zoom> zoom_;
	std::string current_camera_;
	std::string before_camera_;

	std::unordered_map<std::string, std::shared_ptr<VirtualCameraBase>> virtual_cameras_;

	VECTOR vel_;
	VECTOR target_vel_;

	bool can_hit_;

};