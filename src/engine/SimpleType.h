#pragma once
#include "Common.h"
/**
* @those type have gui and josn code, 
*/

namespace staywalk{
	enum class CodeType : int{
		Shader = 0,
		Script = 1
	};

	namespace SWCode {
		struct __SWCode {

		private:
			__SWCode() {}

		public:
			string code;
			CodeType code_type = CodeType::Shader;

			bool operator==(const __SWCode& rhs) const {
				return code == rhs.code && code_type == rhs.code_type;
			}

			void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const;
			void load(rapidjson::Value&, staywalk::reflect::Loader&);

			friend Ref<__SWCode> create_code();
		};

		static Ref<__SWCode> create_code() { return std::shared_ptr<__SWCode>(new __SWCode()); }
	}
	using SWCodeRef = Ref<SWCode::__SWCode>;
}



