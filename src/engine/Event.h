#pragma once

#include "eventpp/callbacklist.h"
#include "SimpleType.h"

namespace staywalk {
	class Event {
	public:
		static eventpp::CallbackList<void(void)> World_AssetChanged;

		static eventpp::CallbackList<void(SWCodeRef)> Editor_EditCode;

		static eventpp::CallbackList<void(SWCodeRef)> Editor_EditCodeDone;
	};
}