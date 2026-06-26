#pragma once

class ShadowMap
{
public:

	ShadowMap();

	~ShadowMap();

	void Init();

	/// <summary>
	/// ‰e‚Ì•`‰æ‚ªs‚í‚ê‚éobject‚Í‚±‚ê‚ğ‹N“®‚·‚é
	/// </summary>
	void UpDrawShadowObject();

	/// <summary>
	/// ‰e‚Ì•`‰æ‚ªs‚í‚ê‚éobject‚ğ•`‰æ‚µI‚í‚Á‚½‚ç‚±‚ê‚ğŒÄ‚Ô
	/// </summary>
	void DownDrawShadowObject();

	/// <summary>
	/// ‰e‚ª•`‰æ‚³‚ê‚éobject‚½‚¿‚ğ•`‰æ‚·‚é
	/// </summary>
	void UpDrawnShadowObject();



	void DownDrawnShadowObject();

private:

	int handle_;



};