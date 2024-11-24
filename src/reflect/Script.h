#pragma once

#ifndef _IN_REFLECT
#include "reflect.h"

#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/embed.h"

#include "fmt/format.h"
#include "fmt/ranges.h"
namespace py = pybind11;
namespace staywalk {
	namespace reflect {
		void py_bind();
	}
}

#include "generated/SerializeAll.gen.h"

#endif // !_IN_REFLECT
