#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	:m_llCurrCount{}, m_llPrevCount{}, m_llFrequency{}, m_dDT(0.), m_dAcc(0.), m_iCallCount(0), m_iFPS(0) // 유니온
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 실행 속도를 측정하고 싶을 때/ 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 타이머의 주기(1초당 진동 수)를 반환/ 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurrCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_llCurrCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; // QuadPart -> longlong 자료형

	// 이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurrCount;

	++m_iCallCount;
	m_dAcc += m_dDT; // DT 누적

	// 누적된 시간이 1초를 넘을 때
	if(m_dAcc > 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
