#include "Object.h"
#include "Utility.h"
namespace staywalk{
	Object::Object() 
		:guid(Utility::GetRandomId()){
	}
}