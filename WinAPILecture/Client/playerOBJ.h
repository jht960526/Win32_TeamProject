#pragma once

class playerOBJ {
private:
	int HP;
	Vec2 p_Pos;
	Vec2 p_Scale;


public:
	playerOBJ();

	Vec2 Getp_Pos() { return p_Pos; }
	Vec2 Getp_Scale() { return p_Scale; }
	int Getp_HP() { return HP; }

	void Setp_Pos(Vec2 _vPos) { p_Pos = _vPos; }
	void Setp_Scale(Vec2 _vScale) { p_Scale = _vScale; }
	void Setp_HP(int _HP) { HP = _HP; }
};



