import staywalk as sw

engine = sw.Engine.get_engine()
world = sw.Engine.get_world()
a = world.get_actors()[0]
print(a.get_aabb())
