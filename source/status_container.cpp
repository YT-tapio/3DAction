#include<fstream>
#include<sstream>
#include<string>
#include"status.h"
#include"status_container.h"
#include"csv_file_assistant.h"

StatusContainer::StatusContainer(const std::string owner_name)
{
	LoadFile(owner_name);
	Init();
}

StatusContainer::~StatusContainer()
{

}

void StatusContainer::Init()
{
	current_status_ = base_status_;
}

void StatusContainer::Update()
{

}

void StatusContainer::Debug()
{
	
}

const Status StatusContainer::GetCurrentStatus() const
{
	return current_status_;
}

void StatusContainer::LoadFile(const std::string owner_name)
{
	// ƒf[ƒ^“Ç‚İæ‚è


}

