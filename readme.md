## 简介
---
用于实践一些技术以及用于测试一些shader和pipeline。

## 开发日志
tag -- skeleton 支持gpu蒙皮

![alt text](readme-res/skeleton.gif)

tag -- shadow 阴影

![alt text](image.png)

## Console
---
```python
# 显示engine bind的一些接口
print(dir(sw.g.engine))
# 显示world bind的一些接口
print(dir(sw.g.world))
```
更加详细具体的文档等待整理

## Build
---
使用cmake完成项目构建

```cmake
cmake -S . -B .\build\
```
初次构建由于需要clone和build cpython,因此需要一会时间。之后可以在.\build目录下可以看到staywalk.sln

解决方案中，需要先生成generated_code项目，自动生成ui和脚本绑定代码；然后启动engine项目即可。

启动之后，可以载入测试world.
![alt text](readme-res/image.png)

## 问题 
构建过程中，可能会出现找不到， 手动重新生成解决方案中ThridParty/cpython/pythoncode即可；因为自动构建的bat在powershell中启动存在一些问题；