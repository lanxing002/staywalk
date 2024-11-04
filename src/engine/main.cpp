
#include "Common.h"
#include "Actor.h"

using namespace staywalk;
int main()
{
	shared_ptr<Actor> o1 = std::make_shared<Actor>("marry");
	shared_ptr<Actor> o2;
	{
		ofstream ostrm("test.swobj", std::ios::out | std::ios::binary);
		o1->dump(ostrm);
	}
	{
		ifstream istrm("test.swobj", std::ios::in | std::ios::binary);
		o2 = Actor::load(istrm);
	}

	assert(*o1 == *o2);
	return 0;
}
