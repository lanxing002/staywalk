#pragma once
namespace staywalk{
	class Object{
	public:
		Object();

		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		//virtual Object clone() {}
		//virtual Object deep_clone() {}

		const long long guid;
	};
}

