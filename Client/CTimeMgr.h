#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);

private:

	// 횟수 카운트 할 때 많이 쓰는 자료형
	LARGE_INTEGER m_llCurrCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // 프레임 사이의 시간 값
	double m_dAcc; // m_dDT를 누적(1초 체크를 위한 누적 시간)
	UINT m_iCallCount; // 함수 호출 횟수 체크
	UINT m_iFPS; // 초당 호출 횟수

	// FPS
	// 1프레임당 시간 (Delta Time)

public:
	// 초기화
	void init();

	// 매 프레임마다 호출
	void update();

//private:
//	CTimeMgr();
//	~CTimeMgr();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
	float GetfAcc() { return (float)m_dAcc; }
};

