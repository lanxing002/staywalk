import staywalk as sw

engine = sw.Engine.get_engine()
world = sw.Engine.get_world()

actor = sw.Actor("triangle")
sm = sw.StaticMeshComponent("simple-triangle")
mesh = sw.Mesh.create_simple_mesh()
# sm.meshs.append(mesh)
# program = sw.RProgram("nn")
sm.add_mesh(mesh)
# sm.meshs.append((program, mesh))
print(sm.meshs)
actor.sm_comp = sm
world.add_actor(actor)
