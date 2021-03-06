#pragma once
#include "EnemyBase.h"

class CEnemyCorpsBossRectangle : public CEnemyBase
{
public:
	float m_moveSpeed;
	float m_rotateSpeed;
	float m_moveDirection;
	CTimer m_timerAfterEffect;

	CEnemyBase* m_pShield[3];
public:
	CEnemyCorpsBossRectangle();
	~CEnemyCorpsBossRectangle();

	virtual bool Initialize() override;
	virtual void Terminate() override;
	virtual bool Pulse() override;
};