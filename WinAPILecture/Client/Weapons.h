#pragma once
class Bullet
{
	int type;
	Vec2 B_Pos;
	Vec2 B_Scale;
	Vec2 B_angle;
	bool B_isOn;

public:
	Bullet();

	int GetType() { return type; }
	Vec2 GetPos() { return B_Pos;}
	Vec2 GetScale() { return B_Scale; }
	Vec2 GetAngle() { return B_angle; }
	bool CheckBullet() { return B_isOn; }

	void SetType(int _type) { type = _type; }
	void SetPos(Vec2 _Pos) { B_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { B_Scale = _Scale; }
	void SetAngle(Vec2 _1st_Pos, Vec2 _2nd_Pos);
	void FireBullet(Vec2 _Scale, Vec2 _1st_Pos, Vec2 _2nd_Pos, int _type);
	void TurnOn() { B_isOn = true; }
	void TurnOff() { B_isOn = false; }

};

