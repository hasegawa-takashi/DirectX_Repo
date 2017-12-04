#include "TunnelCreate.h"



CTunnelCreate::CTunnelCreate()
{
	m_CreateTime = 0;
	CObjMgr::Getintance().PushObj(new CTunnel, ID_TUNNEL);
}


CTunnelCreate::~CTunnelCreate()
{
}


void CTunnelCreate::Update()
{
	m_CreateTime++;

	if (m_CreateTime >  1200)
	{
		CObjMgr::Getintance().PushObj(new CTunnel, ID_TUNNEL);
		m_CreateTime = 0;
	}

}