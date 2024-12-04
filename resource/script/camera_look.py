import staywalk as sw

world = sw.Engine.get_world()
cams = world.get_cameras()
print(cams[0])

actors = world.get_actors()
cams[0].look_actor(actors[0])

print('hello world')