// Hello I'm keff ~ 2020/10/30/16:45
// The any Biological have 4 Attribute points  �C�ӥͪ����|��4���ݩ��I
// Strength     => Str.		�O�q	�C�@�I�W�[ Health ���I
// Dextenity    => Dex.		�ӱ�	�C�@�I�W�[ �j�� �w��
// Intelligence => Int.		���z	�C�@�I�W�[ 
// Lucky        => Luk.		���B

#ifndef BIOLOGICAL_H
#define BIOLOGICAL_H

#include <string>
using namespace std;

class Biological {
public:
	Biological(string id, string name, int strength, int dextenity, int intelligence, int lucky);
	int getHealth() const;
	int getMagic() const;
	int getAttackDamage() const;
	int getMagicAttackDamage() const;
	int getAttackSpeed() const;

private:
	string _id;
	string _name;// �ӥͪ����m�W
	int _strength, _dextenity, _intelligence, _lucky;// �ӥͪ����n�|���ݩ��I
	int _health;// �ӥͪ��ͩR��
	int _magic;// ���ͪ��]�k��
	int _attackDamage;// �ӥͪ��������O
	int _magicAttackDamage;// �ӥͪ����]�k�����O
	int _attackSpeed;// �ӥͪ��������t��
};
#endif
