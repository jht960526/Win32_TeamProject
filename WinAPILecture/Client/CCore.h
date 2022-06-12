#pragma once


// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능
//
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	// 정적 멤버함수
//	static CCore* GetInstance()
//	{
//		// 최초 호출된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//};
//


// 신경써서 메모리 해제를 생각안해도 괜찮음. -> 프로그램 중간에 메모리 해제가 어려움

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hwnd; // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC;  // 메인 윈도우에 Draw 할 DC

	HBITMAP m_hBit;
	HDC m_memDC;


public:

	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
	

private:
	void update();
	void render();

	CCore();
	~CCore();

public:
	HWND GetMainHwnd() { return m_hwnd; }

};
