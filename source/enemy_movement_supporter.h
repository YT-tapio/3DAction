#pragma once

class EnemyBase;

/// <summary>
/// 敵の移動をサポート
/// </summary>
class EnemyMovementSupporter
{
public:

	EnemyMovementSupporter();

	~EnemyMovementSupporter();

	/// <summary>
	/// 登録
	/// </summary>
	/// <param name="enemy"></param>
	void AddResource(EnemyBase* enemy);


	/// <summary>
	/// 変換
	/// </summary>
	/// <param name="move_dir">実際に動こうとしている方向</param>
	/// <returns>動く方向を変換したもの</returns>
	VECTOR SupportMovement(EnemyBase* support_enemy, const VECTOR& target_pos);

private:

	std::vector<EnemyBase*> enemies_;

};