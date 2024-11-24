#include <memory>


namespace staywalk{
	class Object;
	class Actor;

	class Engine{
	public:
		// engine functions
		static shared_ptr<Engine> get_engine();
		static shared_ptr<World> get_world() { return Engine::get_engine()->world_; }
		static Ref<Console> get_console();

		~Engine();
		//end of engine functions

		void load_world(const string& name);

	public:
		//editor function
		void select(Ref<GameObject> target) { selelcted_ = target; }
		Ref<GameObject> get_selected() { return selelcted_; }

		// end of editor function

	private:
		Engine();

	private:
		shared_ptr<World> world_;
		//friend class std::shared_ptr<Engine>;

		// memeber for editor
		Ref<GameObject> selelcted_;

		Ref<Console> console_;

		// end member for editor
	};
}