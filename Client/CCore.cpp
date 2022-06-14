#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"

#include "playerOBJ.h"
#include "Weapons.h"


//CCore* CCore::g_pInst = nullptr;


CObject g_obj;
HINSTANCE g_hinst;

CCore::CCore()
	: m_hwnd(0), m_ptResolution{}, m_hDC(0), m_hBit(0), m_memDC(0)
{

}

playerOBJ g_player;
Bullet BulletOBJ[500];
static int Bulletcnt = 0;


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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top,0);

	// �������� DC�� �����, �������� �־���
	m_hDC = GetDC(m_hwnd);


	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);

	// ���� ������ �ִ� ����Ʈ �� ����
	DeleteObject(hOldBit);



	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();



	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100, 100));

	g_player.Setp_Pos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_player.Setp_Scale(Vec2(20, 20));

	return S_OK;
}

// �۾��� ���ư��� ����
void CCore::progress()
{
	//static int callcount = 0;
	//++callcount;

	//// 1�ʸ��� �ӵ� ī��Ʈ
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

	

	// �������� üũ�ϴ� �κ�(Ű�Է¿� ���� �̵�)
	update();

	// �׷����� �κ�
	render();

}



void CCore::update()
{

	Vec2 vPos = g_player.Getp_Pos();
	
	POINT cursor;
	static bool cooldown;
	GetCursorPos(&cursor);

	if (GetKeyState(MK_LBUTTON)) {
		if (!cooldown) {
			BulletOBJ[Bulletcnt].SetPos(vPos);
			BulletOBJ[Bulletcnt].FireBullet(Vec2(10, 10), g_player.Getp_Pos()
				, Vec2((float)cursor.x, (float)cursor.y), 1);
			Bulletcnt++;
			if (Bulletcnt == 500)Bulletcnt = 0;
			cooldown = true;
		}
		else {
			if (CTimeMgr::GetInst()->GetfAcc() > 0.999)
				cooldown = false;
		}
		
		
	}

	Vec2 BPos = {};
	for (int i = 0; i < 500; i++) {
		if (BulletOBJ[i].CheckBullet() == true) {
			BPos = BulletOBJ[i].GetPos();

			BPos.x += BulletOBJ[i].GetAngle().x * 500.f * CTimeMgr::GetInst()->GetfDT();
			BPos.y += BulletOBJ[i].GetAngle().y * 500.f * CTimeMgr::GetInst()->GetfDT();

			if (0 <= BPos.x <= m_ptResolution.x && 0 <= BPos.y <= m_ptResolution.y)
				BulletOBJ[i].SetPos(BPos);
			else BulletOBJ[i].TurnOff();
		}
	}

	//GetAsyncKeyState(VK_LEFT) & 0x8000
	

	if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
		if (vPos.x < g_player.Getp_Scale().x/2)vPos.x = g_player.Getp_Scale().x / 2;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
		if (vPos.x > m_ptResolution.x - (g_player.Getp_Scale().x / 2))
			vPos.x = m_ptResolution.x - (g_player.Getp_Scale().x / 2);

	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		vPos.y -= 200.f * CTimeMgr::GetInst()->GetfDT();
		if (vPos.y < g_player.Getp_Scale().y / 2)vPos.y = g_player.Getp_Scale().y / 2;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		vPos.y += 200.f * CTimeMgr::GetInst()->GetfDT();
		if (vPos.y > m_ptResolution.y - (g_player.Getp_Scale().y / 2))
			vPos.y = m_ptResolution.y - (g_player.Getp_Scale().y / 2);
	}

	g_player.Setp_Pos(vPos);
}

void CCore::render()
{
	
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// �׸���
	Vec2 vPos = g_player.Getp_Pos();
	Vec2 vScale = g_player.Getp_Scale();

	for (int i = 0; i < 500; i++) {
		if (BulletOBJ[i].CheckBullet() == true) {
			

			Ellipse(m_memDC
				, int(BulletOBJ[i].GetPos().x - BulletOBJ[i].GetScale().x / 2.f)
				, int(BulletOBJ[i].GetPos().y - BulletOBJ[i].GetScale().y / 2.f)
				, int(BulletOBJ[i].GetPos().x + BulletOBJ[i].GetScale().x / 2.f)
				, int(BulletOBJ[i].GetPos().y + BulletOBJ[i].GetScale().y / 2.f));

		}
	}


	Ellipse(m_memDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	// �޸� ����
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC
		, 0, 0, SRCCOPY);
}
