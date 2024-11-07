#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"

namespace staywalk
{
	/**
	* @brief check drived class from Object has necessary functions
	*/
	//template<typename T, typename Base = Object>
	//class ObjectCheck {
	//public:
	//	static constexpr bool pass =
	//		!std::is_same<decltype(&T::dump_impl), decltype(&Base::dump_impl)>::value &&
	//		!std::is_same<decltype(&T::load_impl), decltype(&Base::load_impl)>::value &&
	//		!std::is_member_function_pointer<decltype(&T::operator==)>::value
	//		;
	//};

	//constexpr bool dd =  != (void*)(&Object::dump_impl);
	//constexpr bool c = std::is_same<decltype((void*)(std::declval<GameObject>().*(&Object::dump_impl))), decltype(&Object::dump_impl)>::value;
	//static_assert(ObjectCheck<GameObject>::pass);
}

