#include <algorithm>
#include "stdafx.h"
#include "EnemyManager.h"
#include "GameSceneBase.h"

CEnemyManager::CEnemyManager()
{
	Initialize();
	m_sortTime.InitTimer(1000);
}

CEnemyManager::~CEnemyManager()
{
}

bool CEnemyManager::Initialize()
{
	return true;
}
void CEnemyManager::Terminate()
{

}
bool CEnemyManager::Pulse()
{
	if (m_sortTime.IsValidTimer())
		if (m_sortTime.IsElapseTimer()) {
			if (m_Enemy.size() > 0)
				std::sort(begin(m_Enemy), end(m_Enemy), [](CEnemyBase* p, CEnemyBase* q) { return p->m_Point.distance({}) > q->m_Point.distance({}); });
			m_sortTime.InitTimer(1000);
		}
	for (int i = 0; i < m_Enemy.size(); ++i)
	{
		if (m_Enemy[i] == nullptr)
		{
			m_Enemy.erase(m_Enemy.begin() + i);
			--i;
			continue;
		}
		m_Enemy[i]->Pulse();
		for (int j = 0; j < g_pGameScene->m_BulletManager->m_Bullet.size() && i < m_Enemy.size(); ++j)
			if (m_Enemy[i] == nullptr)
			{
				m_Enemy.erase(m_Enemy.begin() + i);
				--i;
				continue;
			}
			else if (m_Enemy[i]->hitBox(g_pGameScene->m_BulletManager->m_Bullet[j]->m_hitRect))
			{
				if (m_Enemy[i]->hitPolyton(g_pGameScene->m_BulletManager->m_Bullet[j], g_pGameScene->m_matWorld))
				{
					if (g_pGameScene->m_Player->m_gunType == 4);
					else if (--(g_pGameScene->m_BulletManager->m_Bullet[j]->m_hp) < 0)
					{
						delete g_pGameScene->m_BulletManager->m_Bullet[j];
						g_pGameScene->m_BulletManager->m_Bullet.erase(g_pGameScene->m_BulletManager->m_Bullet.begin() + j);
					}
					else
					{
						g_pGameScene->m_BulletManager->m_Bullet[j]->m_direction += 1 - 0.4 + 1.8 * (rand() % 200 / 200.0);
					}
					m_Enemy[i]->m_Hp -= g_pGameScene->m_BulletManager->m_Bullet[j]->m_damage;
					if (m_Enemy[i]->m_Hp <= 0)
					{
						delete m_Enemy[i];
						m_Enemy.erase(m_Enemy.begin() + i);
						--i;
					}
				}
			}
	}
	return true;
}
void CEnemyManager::Render(Matrix mat)
{
	for (auto& v : m_Enemy)
		if(v != nullptr)
			v->Render(mat);
}