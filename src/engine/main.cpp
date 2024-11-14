
#include "World.h"
#include "Actor.h"
#include "Utility.h"
#include "Serialize.h"

using namespace staywalk;

void test() {
}

using namespace staywalk;
int main()
{
	auto w = World::load_marry_world();

	/*PActor a = std::make_shared<Actor>("avatar");
	PActor b = std::make_shared<Actor>("avatar1");
	PActor c = std::make_shared<Actor>("avatar2");

	a->location = (glm::vec3(100, 200, 400));
	a->rotation = (glm::quat(10.0, 20.0, 30.0, 1.0));
	a->scale = (glm::vec3(20.0, 30.0, 1.0));

	shared_ptr<StaticMeshComponent> sm = std::make_shared<StaticMeshComponent>();
	a->sm_comp = (sm);

	shared_ptr<World> w = World::create_empty_world("test-world");
	w->add_actor(a);
	w->add_actor(b);
	w->add_actor(c);
	w->dump();

	auto loaded_world = World::load("test-world");
	auto actors = loaded_world->get_all_actors();
	assert(Comparer::equal(w->get_all_actors(), loaded_world->get_all_actors()));*/
	return 0;
}