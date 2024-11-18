from parse_class import ClassNode, NoClassField, FuncParam
import clang.cindex
import os
from mylog import *

# --------------dump code start-----------------
dump_code1 = '''
void {cur_type}::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {{'''

dump_code2 = '''
    {base_type}::dump(ofs, dumper);'''

dump_code3 = '''
    dumper.write(this->{dump_prop}, ofs);'''

dump_code4 = '''
}
'''

dump_declare = ''' '''
# --------------dump code end-----------------


# --------------load code start-----------------
load_code1 = '''
void {cur_type}::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {{'''

load_code2 = '''
    {base_type}::load(ifs, loader);'''

load_code3 = '''
    loader.read(this->{load_prop}, ifs);'''

load_code4 = '''
}
'''

load_declare = ''' '''
# --------------load code end-----------------


# ---------------operator == code start------------------
eop_code1 = '''
bool {cur_type}::operator==(const {cur_type}& rhs) const {{'''

eop_code2 = '''
    return 
'''

eop_code3 = '''{base_type}::operator==(rhs) '''

eop_code4 = '''::staywalk::Comparer::equal(this->{load_prop}, rhs.{load_prop})'''

eop_code5 = '''
}
'''

eop_declare = ''' '''

# ---------------type object code start------------------
typeo_code1 = '''
::staywalk::reflect::MetaInfo {cur_type}::get_meta_info() const {{'''

typeo_code2 = '''
    return ::staywalk::reflect::MetaInfo{{"{cur_type_enum}"}};
'''

typeo_code3 = '''
}
'''

typeo_declare = ''' '''
# ---------------otype object  code end------------------


# ---------------create code start------------------
create_obj_code1 = '''
using namespace staywalk;
shared_ptr<Object> reflect::create_empty(reflect::MetaInfo minfo) {
    if (false) { return nullptr; }
'''

create_obj_code2 = '''
    else if (minfo.tname == "{cur_type_str}"){{return std::make_shared<{cur_type}>();}}
'''

create_obj_code3 = '''
    else {assert(false); return nullptr;}
'''

create_obj_code4 = '''
}
'''
# ---------------create code end------------------

class SerializeBind(object):
    def __init__(self, bind_node: ClassNode):
        self._node = bind_node.node
        self._base_names = None
        self.outer_classes = [x.spelling for x in bind_node.outer_classes]
        self._namespaces = [x.spelling for x in bind_node.namespaces]
        self._name = self._node.spelling
        self._full_name = '::' + '::'.join(self._namespaces) + '::' + '::'.join(
            self.outer_classes) + self._node.spelling
        self._props = []
        self._parse()

    @property
    def name(self):
        return self._name

    @property
    def fullname(self):
        return self._full_name

    @property
    def header(self):
        return str(self._node.extent.start.file.name)

    def _dump_code(self):
        code = ''
        code += dump_code1.format(cur_type=self._full_name)
        code += dump_code2.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            code += dump_code3.format(dump_prop=p)
        code += dump_code4
        declare = dump_declare.format(cur_type=self._full_name)
        return declare, code

    def _load_code(self):
        code = ''
        code += load_code1.format(cur_type=self._full_name)
        code += load_code2.format(base_type=self._base_names) if self._base_names else ''
        for p in self._props:
            code += load_code3.format(load_prop=p)
        code += load_code4
        declare = load_declare.format(cur_type=self._full_name)
        return declare, code

    def _eop_code(self):
        code = ''
        code += eop_code1.format(cur_type=self._full_name)
        code += eop_code2
        code += eop_code3.format(base_type=self
                                 ._base_names) if self._base_names else 'true'
        for p in self._props:
            code += ' && ' + eop_code4.format(load_prop=p)
        code += ';'
        code += eop_code5
        declare = eop_declare.format(cur_type=self._full_name)
        return declare, code

    def _typeo_code(self):
        code = ''
        code += typeo_code1.format(cur_type=self._full_name[2:])
        code += typeo_code2.format(cur_type_enum=self._full_name[2:])
        code += typeo_code3
        return typeo_declare, code

    def generate_code(self):
        ns_code = '{func_code}'
        for ns in self._namespaces[::-1]:
            ns_code = 'namespace ' + ns + '{{' + ns_code + '}}'
        declare1, impl1 = self._dump_code()
        declare2, impl2 = self._load_code()
        declare3, impl3 = self._eop_code()
        declare4, impl4 = self._typeo_code()
        return (declare1 + declare2 + declare3 + declare4,
                impl1 + '\n' + impl2 + '\n' + impl3 + '\n' + impl4)

    def _parse(self):
        find_base = [base.spelling for base in self._node.get_children() if
                     base.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER]
        self._base_names = find_base[0] if len(find_base) > 0 else None

        for member in self._node.get_children():
            if member.kind != clang.cindex.CursorKind.FIELD_DECL:
                continue

            is_label = filter(lambda x: x.kind == clang.cindex.CursorKind.ANNOTATE_ATTR and
                                        str(x.spelling).startswith('__sw'), member.get_children())
            is_label = len(list(is_label)) > 0
            if not is_label:
                continue

            self._props.append(member.spelling)


def generate(nodes: list[ClassNode], reflect_dir):
    generate_dir = os.path.join(reflect_dir, 'generated')
    declare_target_file = os.path.join(generate_dir, 'SerializeAll.gen.h')
    impl_target_file = os.path.join(generate_dir, 'SerializeAll.gen.cpp')
    common_target_file = os.path.join(generate_dir, 'Common.gen.h')
    common_imp_target_file = os.path.join(generate_dir, 'Common.gen.cpp')
    logging.log(logging.INFO, f'generate serialize code to {declare_target_file}, {impl_target_file} ...')

    include_code = '#include "{}"'

    with open(declare_target_file, 'w') as decl:
        with open(impl_target_file, 'w') as impl:
            with open(common_target_file, 'w') as common:
                common.write('namespace staywalk{ namespace reflect{\n\tenum class ObjectType : unsigned int{\n')
                for node in nodes:
                    if not node.labeled():
                        continue
                    common.write('\t\t' + node.name + ', \n')
                common.write('}; }}')

            impl.write(include_code.format(os.path.join(reflect_dir, 'Serialize.h')))
            impl.write('\n')

            all_include_code = ''
            create_code = ''
            for node in nodes:
                if not node.labeled():
                    continue
                snode = SerializeBind(node)
                logging.log(logging.INFO, f'start generate {node._node.spelling}')
                decl_code, impl_code = snode.generate_code()
                impl.write(include_code.format(snode.header) + '\n')
                impl.write(impl_code + '\n')
                # decl.write(decl_code + '\n')

                # generate create_empty function code
                all_include_code += include_code.format(snode.header) + '\n'
                create_code += create_obj_code2.format(cur_type_str=snode.fullname[2:], cur_type=snode.fullname)

            with open(common_imp_target_file, 'w') as common:
                common.write(all_include_code + '\n\n\n')
                common.write(include_code.format(os.path.join(reflect_dir, 'reflect.h')))
                common.write(create_obj_code1)
                common.write(create_code)
                common.write(create_obj_code3)
                common.write(create_obj_code4)

