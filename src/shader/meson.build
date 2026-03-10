shader_src = [
    'cas.frag.glsl',
    'deband.frag.glsl',
    'dls.frag.glsl',
    'dpx.frag.glsl',
    'film_noise.frag.glsl',
    'full_screen_triangle.vert.glsl',
    'fxaa.frag.glsl',
    'lift_gamma_gain.frag.glsl',
    'lut.frag.glsl',
    'linear_depth.frag.glsl',
    'screen_space_normal.frag.glsl',
    'sepia.frag.glsl',
    'smaa_blend.frag.glsl',
    'smaa_blend.vert.glsl',
    'smaa_edge.frag.glsl',
    'smaa_edge.vert.glsl',
    'smaa_neighbor.frag.glsl',
    'smaa_neighbor.vert.glsl',
    'vibrance.frag.glsl',
]

glsl_compiler = find_program('glslangValidator')
glsl_generator = generator(glsl_compiler,
    output    : [ '@BASENAME@.h' ],
    arguments : [ '-V', '-x', '@INPUT@', '-o', '@OUTPUT@' ])

shader_include = glsl_generator.process(shader_src)
