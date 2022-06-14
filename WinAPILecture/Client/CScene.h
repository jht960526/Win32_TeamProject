#pragma once


// ���漱��
// ������� ���ΰ� ���θ� �����ϴ� ���� ���� ���ؼ�
// ��ü���� ������ �� �� ���� ������ �����͸� ���

class CObject;

class CScene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];

	// Scene �̸�
	wstring m_strName;
	

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }

	const wstring& GetName() { return m_strName; }

	void update();

	void render(HDC _dc);

	// �ش� Scene�� ���� �� ȣ��
	virtual void Enter() = 0; // ���� �����Լ� : ������ ��ü ���� �Ұ�

	// �ش� Scene�� Ż�� �� ȣ��
	virtual void Exit() = 0;

protected:
	void AddObject(CObject* _pOb, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pOb); // Inline���� ȣ���ؼ� ���ÿ��� ó�� -> �Լ� ȣ����x
	}

public:

	CScene();
	virtual ~CScene();
};

