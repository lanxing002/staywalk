#pragma once

#include "eventpp/callbacklist.h"

namespace staywalk {
	class Event {
	public:
		static eventpp::CallbackList<void(void)> World_AssetChanged;
	};
}