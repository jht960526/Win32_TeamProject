#include "pch.h"
#include "Camera.h"

#include "CObject.h"

#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

Camera::Camera()
    : m_pTargetObj(nullptr)
{}

Camera::~Camera()
{}

void Camera::update()
{
    if (m_pTargetObj)
    {
            SetLookAt(m_pTargetObj->Getp_Pos());
    }

	if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		m_vLookAt.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		m_vLookAt.x += 200.f * CTimeMgr::GetInst()->GetfDT();

	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		m_vLookAt.y -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		m_vLookAt.y += 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	CalDiff();
}

void Camera::CalDiff()
{
    Vec2 vResolution = CCore::GetInst()->GetResolution();
    Vec2 vCenter = Vec2(vResolution.x / 2.f, vResolution.y / 2.f);

    m_vDiff = Vec2(m_vLookAt.x - vCenter.x, m_vLookAt.y - vCenter.y);
}


