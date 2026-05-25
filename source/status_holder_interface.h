#pragma once

class StatusContainer;

class IStatusHolder
{
public:
	virtual ~IStatusHolder();

	/// <summary>
	/// StatusContainer‚ð•Ô‚·
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<StatusContainer> GetStatusContainer();
};