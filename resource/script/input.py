import staywalk as sw

engine = sw.Engine.get_engine()
im = engine.get_input_mgr()
print(dir(im))

print(im.pos())