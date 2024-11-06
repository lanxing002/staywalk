#pragma once
#include "Object.h"
namespace staywalk{
	class GameComponent	: public Object{
	public:
		GameComponent(const string& name = "0-comp")
			:Object(name) {}

		bool operator==(const GameComponent& rhs) {
			return Object::operator==(rhs);
		}

		//void dump(ofstream& ofs, Dumper& dumper);
		static shared_ptr<GameComponent> load(ifstream& ifs, Loader& loader);
	protected:
		static void placement_load(shared_ptr<GameComponent> obj, ifstream& ifs);
	};
}

