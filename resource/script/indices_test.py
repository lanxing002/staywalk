import staywalk as sw

engine = sw.Engine.get_engine()
world = sw.Engine.get_world()
a = world.get_actors()[0]
sm = a.sm_comp.meshs[0][0]

ii = sm.indices
vv = sm.vertices
print(len(vv))
print(max(ii))
print(len(ii))



print
print(dir(sm.indices))