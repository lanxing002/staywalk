import os
import sys

import math
from time import time
import numpy as np

# PyGLM
import glm

# PyOpenGL import
from OpenGL.GL import *
from OpenGL.GLUT import *

from OpenGL.GL.shaders import *

from subprocess import call
from shutil import which



glslVaidator = which('./spirv/glslangValidator.exe')
print(glslVaidator)