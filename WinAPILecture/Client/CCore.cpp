#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"
#include "CScene.h"


//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	: m_hwnd(0), m_ptResolution{}, m_hDC(0), m_hBit(0), m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hwnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top,0);

	// 내부적인 DC가 생기고, 목적지를 넣어줌
	m_hDC = GetDC(m_hwnd);


	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);

	// 원래 가지고 있던 디폴트 값 삭제
	DeleteObject(hOldBit);



	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();



	/*g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));*/

	return S_OK;
}

// 작업이 돌아가는 공간
void CCore::progress()
{
	//static int callcount = 0;
	//++callcount;

	//// 1초마다 속도 카운트
	//static int iPrevCount = GetTickCount();
	//int iCurCount = GetTickCount();

	//if (iCurCount - iPrevCount > 1000)
	//{
	//	iPrevCount = iCurCount;
	//	callcount = 0;
	//}


	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();


	// ===========
	// Rendering
	// ===========
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	// 메모리 복사
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC
		, 0, 0, SRCCOPY);


}

