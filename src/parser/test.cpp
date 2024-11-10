#define INTERESTING __attribute__((annotate("get;set")))

namespace staywalk{
	struct Vertex;
	class Material;

	// render object is a opengl object
	class INTERESTING RObject : public Object{
	public:
		RObject(const string& name = "0-RObj");

        INTERESTING void tttt();
		uint glid = kGlInvalidId;  // for opgnel id, -1 is invalid
		INTERESTING bool valid = false;
//		string path;

//		ObjectType get_type_value() const override { return ObjectType::RObject; }
//		bool operator==(const RObject& gameobj);
//	protected:
//		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
//		void load_impl(ifstream& ifs, Loader& loader) override;
	};
}