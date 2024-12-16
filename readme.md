## example 
IMGUI_SIMPLE_EXAMPLE 用于开启imgui测试


## cpython 
cpython 项目巨大，本身没有cmakelists.txt；从头构�?.cmake文件比较困难，因此选择取巧的方式，直接在服用它本身所自带的项�?
build的时候，使用cpython/build.bat

由于build.bat需要使用python.exe，这个需要注意以�?

分两步构建，先构建python-core, 然后deploy到一个文件夹，之后再在项目中使用�?

删除了assimp的test文件，占用空间过�?  