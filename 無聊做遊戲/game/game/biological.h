// Hello I'm keff ~ 2020/10/30/16:45
// The any Biological have 4 Attribute points  每個生物都會有4個屬性點
// Strength     => Str.		力量	每一點增加 Health 兩點
// Dextenity    => Dex.		敏捷	每一點增加 迴避 趴數
// Intelligence => Int.		智慧	每一點增加 
// Lucky        => Luk.		幸運

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
	string _name;// 該生物的姓名
	int _strength, _dextenity, _intelligence, _lucky;// 該生物必要四個屬性點
	int _health;// 該生物生命值
	int _magic;// 乾生物魔法值
	int _attackDamage;// 該生物的攻擊力
	int _magicAttackDamage;// 該生物的魔法攻擊力
	int _attackSpeed;// 該生物的攻擊速度
};
#endif
