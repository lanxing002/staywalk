#define INTERESTING(...) __attribute__((annotate("__sw;" #__VA_ARGS__)))

namespace cc{
namespace cc2{
class Base{
    class Inner{};
};
}
}

template<typename T>
class Vector{
};

namespace dd{
class  Object : public cc::cc2::Base{
public:
    INTERESTING() Vector<int> vecc;
    INTERESTING(abd) Inner vecc2;
  private:
  int ____dsee;
};

}
     Vector<int> vecc2;


//
//namespace staywalk{
//	// render object is a opengl object
//	class INTERESTING RObject : public Object{
//	public:
//
//	    class JTR{
//	        int a;
//	    };
//
//		INTERESTING RObject(const string& name = "0-RObj");
//
//
//        INTERESTING virtual int tttt();
//        INTERESTING static int static_Dd();
//		uint glid = kGlInvalidId;  // for opgnel id, -1 is invalid
//		INTERESTING bool valid = false;
////		string path;
//
////		ObjectType get_type_value() const override { return ObjectType::RObject; }
////		bool operator==(const RObject& gameobj);
////	protected:
////		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
////		void load_impl(ifstream& ifs, Loader& loader) override;
//	};
//
//
//	struct Vertex;
//	class Material;
//
//    enum  class INTERESTING EMY : unsigned int{
//        NONE,
//    };
//
//	INTERESTING extern int a ;
//	INTERESTING int a ;
//	INTERESTING void tdsd();
//
//
//}