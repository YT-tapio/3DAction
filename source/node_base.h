#pragma once

enum class BehaviorStatus;

class NodeBase
{
public:

	NodeBase();

	virtual ~NodeBase();

	virtual void Init();

	virtual void Entry();

	virtual BehaviorStatus Update();

	virtual void Exit();

	virtual void Debug();

	const BehaviorStatus GetStatus() const;

protected:

	BehaviorStatus status_;

private:



};