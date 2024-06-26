# Copyright © 2022 Collabora Ltd

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

glsl_shaders = files(
	'gear.frag',
	'gear.vert',
)

sources = files('vkgears.c', 'wsi/wsi.c')

args = []
wsi_deps = []

if dep_wayland.found()
  args += ['-DWAYLAND_SUPPORT']
  sources += files('wsi/wayland.c')
  wsi_deps += [dep_wayland, dep_epoll, dep_libdecor]
endif

if dep_xcb.found()
  args += ['-DXCB_SUPPORT']
  sources += files('wsi/xcb.c')
  wsi_deps += dep_xcb
endif

if (dep_wayland.found() or dep_xcb.found()) and prog_glslang.found()
  _gen = generator(
    prog_glslang,
    output : '@PLAINNAME@.spv.h',
    arguments : [ '@INPUT@', '-V', '-x', '-o', '@OUTPUT@' ]
  )

  spirv_shaders = _gen.process(glsl_shaders)

  executable(
    'vkgears', files('vkgears.c'), sources,
    spirv_shaders,
    dependencies: [dep_vulkan, idep_util, wsi_deps],
    c_args: args,
    install: true
  )
endif
