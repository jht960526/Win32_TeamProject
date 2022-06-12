#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"



CSceneMgr::CSceneMgr()
	:m_arrScene{}
     ,m_pCurScene(nullptr)
{
	
}

CSceneMgr::~CSceneMgr()
{
	// Scene ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (m_arrScene[i] != nullptr)
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;

	// ���� Scene ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
}
