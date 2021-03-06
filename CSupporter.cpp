#include "stdafx.h"
#include "CSupporter.h"
#include "GameSceneBase.h"

CSupporter::CSupporter()
{
	Initialize();
}

CSupporter::~CSupporter()
{
}

bool CSupporter::Initialize()
{
	m_eRenderType = eRenderType_Polygon;
	m_Color = RGB(0xff, 0xff, 0xff);

	m_Point = { 0, 0 };
	m_rotate = 0;
	m_scale = 1.0;

	old = GetTickCount();

	m_NumPolygon = 10;
	m_Polygon = new POINT[m_NumPolygon];
	{
		m_Polygon[0] = { -50, -50 };
		m_Polygon[1] = { -50,  50 };
		m_Polygon[2] = { 50,  50 };
		m_Polygon[3] = { 50, -50 };
		m_Polygon[4] = { -50, -50 };
		m_Polygon[5] = { -40, -40 };
		m_Polygon[6] = { 40, -40 };
		m_Polygon[7] = { 40,  40 };
		m_Polygon[8] = { -40,  40 };
		m_Polygon[9] = { -40, -40 };
	}
	return true;
}
void CSupporter::Terminate()
{

}
bool CSupporter::Pulse()
{
	CEnemyBase* bs = nullptr;
	Vector target;
	float distance = -1;
	m_rotate += 0.1;

	if (!g_pGameScene->m_EnemyManager->m_Enemy.size())
		return true;
	for (int i = 0; i < g_pGameScene->m_EnemyManager->m_Enemy.size(); ++i)
	{
		if (g_pGameScene->m_EnemyManager->m_Enemy[i])
			if (float dist = m_Point.distance(g_pGameScene->m_EnemyManager->m_Enemy[i]->m_Point); (dist < distance || distance < 0))
			{
				Vector vec{ cosf(m_rotate*PI), sinf(m_rotate*PI) };
				Vector vec2{ float(g_pGameScene->m_EnemyManager->m_Enemy[i]->m_Point.x - m_Point.x), float(g_pGameScene->m_EnemyManager->m_Enemy[i]->m_Point.y - m_Point.y) };
				distance = dist;
				target = g_pGameScene->m_EnemyManager->m_Enemy[i]->m_Point;
				bs = g_pGameScene->m_EnemyManager->m_Enemy[i];
			}
	}
	m_rotate = atan2(bs->m_Point.y - m_Point.y, bs->m_Point.x - m_Point.x) / PI;

	int m_gunType = g_pGameScene->m_Player->m_gunType;
	int m_gunLevel = g_pGameScene->m_Player->m_gunLevel;
	switch (m_gunType)
	{
	case 1:
		if (GetTickCount() - old > 100)
		{
			old = GetTickCount();
			g_pGameScene->m_BulletManager->m_Bullet.push_back(new CBulletStraight(m_rotate));
			g_pGameScene->m_BulletManager->m_Bullet.back()->m_Point = m_Point;
		}
		break;
	case 2:
		if (GetTickCount() - old > 125)
		{
			old = GetTickCount();
			g_pGameScene->m_BulletManager->m_Bullet.push_back(new CBulletReflection(m_rotate, 1));
			g_pGameScene->m_BulletManager->m_Bullet.back()->m_Point = m_Point;
		}
		break;
	case 3:
		if (GetTickCount() - old > 40)
		{
			old = GetTickCount();
			g_pGameScene->m_BulletManager->m_Bullet.push_back(new CBulletSprinkle(m_rotate));
			g_pGameScene->m_BulletManager->m_Bullet.back()->m_Point = m_Point;
		}
		break;
	case 4:
		if (GetTickCount() - old > 70)
		{
			old = GetTickCount();
			g_pGameScene->m_BulletManager->m_Bullet.push_back(new CBulletLaser(m_rotate, 50));
			g_pGameScene->m_BulletManager->m_Bullet.back()->m_Point = m_Point;
		}
		break;
	case 5:
		if (GetTickCount() - old > 200)
		{
			old = GetTickCount();
			g_pGameScene->m_BulletManager->m_Bullet.push_back(new CBulletBomb(m_rotate, 5));
			g_pGameScene->m_BulletManager->m_Bullet.back()->m_Point = m_Point;
		}
		break;
	case 6:
		if (GetTickCount() - old > 70 + (6 - m_gunLevel) * 30)
		{
			old = GetTickCount();
			g_pGameScene->m_BulletManager->m_Bullet.push_back(new CBulletGuided(m_rotate));
			g_pGameScene->m_BulletManager->m_Bullet.back()->m_Point = m_Point;
		}
		break;
	}
	return true;
}