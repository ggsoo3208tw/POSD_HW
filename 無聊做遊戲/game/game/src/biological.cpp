// Hello I'm keff ~ 2020/10/30/16:45

#include "biological.h"

#include <string>
using namespace std;

Biological::Biological(string id, string name, int strength, int dexenity, int intelligence, int lucky) {
	if (strength >= 0 && dexenity >= 0 && intelligence >= 0 && lucky >= 0) {
		_id = id;
		_name = name;
		_strength = strength;
		_dextenity = dexenity;
		_intelligence = intelligence;
		_lucky = lucky;
	}
	throw string("Error : Create Biological failed!");
}