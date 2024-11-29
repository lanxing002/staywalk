import staywalk as sw

camera = sw.Camera('camera')
world = sw.Engine.get_world()
world.add_camera(camera)

print('hello world')