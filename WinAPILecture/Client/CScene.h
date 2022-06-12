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

public:

	CScene();
	virtual ~CScene();
};

