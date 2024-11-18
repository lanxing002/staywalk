#pragma once

#ifndef _IN_REFLECT
//#include "Common.gen.h"
#include "reflect.h"
#include "imgui.h"

namespace staywalk{
	namespace reflect {
		class UIHelper {
		public:
			template<typename T>
			void construct(const T& data);

			template<>
			void construct(std::string& data);

		};
	}
}

#include "generated/UIBindAll.gen.h"

#endif // !_IN_REFLECT
