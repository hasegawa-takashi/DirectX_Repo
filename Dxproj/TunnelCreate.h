#pragma once
#include "includeheader.h"
#include"Tunnel.h"

class CTunnelCreate :public ObjBase
{
public:
	CTunnelCreate();
	~CTunnelCreate();

	void Update();

private:
	int m_CreateTime;

};

