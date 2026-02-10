#pragma once
#include"collider_base.h"

struct Contact;

class Mesh :public ColliderBase
{
public:

	Mesh(int handle);

	~Mesh() override;

	bool CheckCollision(const VECTOR& my_pos, const VECTOR& vel,const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll,Contact& contact) override;

	void FixPos(const VECTOR& my_pos, const VECTOR& vel, const VECTOR& other_pos, std::shared_ptr<ColliderBase> other_coll, Contact& contact) override;

	void Draw(const VECTOR& pos)override;

	const int GetHandle() const;

private:

	int handle_;

};
