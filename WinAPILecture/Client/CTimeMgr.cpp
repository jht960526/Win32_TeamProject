#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	:m_llCurrCount{}, m_llPrevCount{}, m_llFrequency{}, m_dDT(0.), m_dAcc(0.), m_iCallCount(0), m_iFPS(0) // ���Ͽ�
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ���� �ӵ��� �����ϰ� ���� ��/ ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// Ÿ�̸��� �ֱ�(1�ʴ� ���� ��)�� ��ȯ/ �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurrCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurrCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; // QuadPart -> longlong �ڷ���

	// ���� ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurrCount;

	++m_iCallCount;
	m_dAcc += m_dDT; // DT ����

	// ������ �ð��� 1�ʸ� ���� ��
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
