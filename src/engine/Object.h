#pragma once
#include "Common.h"

namespace staywalk{
	class Object{
	public:
		Object();
		Object(long long load_id);

		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		//virtual Object clone() {}
		//virtual Object deep_clone() {}
		long long get_guid() { return guid_; }

		bool operator==(const Object& rhs) {
			return guid_ == rhs.guid_;
		}

		virtual void dump(ofstream& ofs);
		static shared_ptr<Object> load(ifstream& ifs);

	protected:
		static void placement_load(shared_ptr<Object> obj, ifstream& ifs);
		long long guid_;
	};
}

