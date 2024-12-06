import staywalk as sw

engine = sw.Engine.get_engine()
world = sw.Engine.get_world()
terrain = sw.Terrain("terrain")
terrain.init_with_plane()
world.add_actor(terrain)


