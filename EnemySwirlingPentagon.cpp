#include "stdafx.h"
#include "EnemySwirlingPentagon.h"
#include "WndSystem.h"
#include "GameSceneBase.h"
#include "AfterimageFX.h"
#include "EffectLineFX.h"

CEnemySwirlingPentagon::CEnemySwirlingPentagon()
{
	m_moveSpeed = 0.0f;
	m_rotateSpeed = 0.0f;
	m_moveDirection = 0.0f;
	Initialize();
}

CEnemySwirlingPentagon::~CEnemySwirlingPentagon()
{
	Terminate();
}

bool CEnemySwirlingPentagon::Initialize()
{
	m_eRenderType = eRenderType_Polygon;
	m_Color = RGB(0xff, 0xff, 0xff);

	m_NumPolygon = 5;
	m_Polygon = new POINT[m_NumPolygon];
	for (int i = 0; i < m_NumPolygon; ++i)
		m_Polygon[i] = { LONG(200 * cos(PI * 2 / m_NumPolygon * i)), LONG(200 * sin(PI * 2 / m_NumPolygon * i)) };

	m_rotate = 0.0f;
	m_scale = 1.0f;

	m_rotatingMoveSpeed = 1800;
	m_moveSpeed = 300;
	m_rotateSpeed = rand() % 2 ? 1.5f : -1.5f;
	m_moveDirection = atan2(-m_Point.y, -m_Point.x) / PI;

	m_Hp = 10;
	m_AddScore = 4;

	m_timerAfterEffect.InitTimer(50);

	return true;
}
void CEnemySwirlingPentagon::Terminate()
{
	g_pSoundManager->Pulse(m_pChannel, 7);
	g_pGameScene->SetShake(150, 15, m_rotate);
	g_pGameScene->m_EffectManager->m_VFX.push_back(new CTearFX(m_Point, 600, 9, m_Color));
	g_pGameScene->m_EffectManager->m_VFX.push_back(new CDestroyFX(m_Point, m_NumPolygon, 600, m_Color));
	g_pGameScene->m_EffectManager->m_VFX.push_back(new CEffectLineFX(m_Point, 300, m_Color));
}
bool CEnemySwirlingPentagon::Pulse()
{
	CEnemyBase::Pulse();

	if (m_timerAfterEffect.IsElapseTimer()) {
		if (!m_timerAfterEffect.IsValidTimer()) {
			g_pGameScene->m_EffectManager->m_VFX.push_back(new CAfterimageFX(this, m_Color, 300));
			m_timerAfterEffect.InitTimer(50);
		}
	}

	m_Point.x += g_pSystem->GetTimeStep() * m_moveSpeed * cos(m_moveDirection * PI);
	m_Point.x += g_pSystem->GetTimeStep() * m_rotatingMoveSpeed * cos((m_moveDirection + 0.5) * PI);

	m_Point.y += g_pSystem->GetTimeStep() * m_moveSpeed * sin(m_moveDirection * PI);
	m_Point.y += g_pSystem->GetTimeStep() * m_rotatingMoveSpeed * sin((m_moveDirection + 0.5) * PI);

	m_moveDirection = atan2(-m_Point.y, -m_Point.x) / PI;

	m_rotate += g_pSystem->GetTimeStep() * m_rotateSpeed;
	return false;
}