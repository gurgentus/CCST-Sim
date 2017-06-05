#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T09:56:08
#
#-------------------------------------------------

QT       += core gui opengl charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app

SOURCES += common/camera3D.cpp \
    common/control.cpp \
    common/input.cpp \
    common/main.cpp \
    common/output.cpp \
    common/textures.cpp \
    common/transform3d.cpp \
    #common/dynamiccontrol.cpp \
    cst/transferfunction.cpp \
    cst/cst.cpp \
    cst/complexnumber.cpp \
    cst/pfd.cpp \
    nums/AbstractOdeSolver.cpp \
    nums/AdaptiveRungeKuttaSolver.cpp \
    nums/Restricted3BodySolver.cpp \
    nums/RungeKuttaSolver.cpp \
    nums/TwoBodySolver.cpp \
    objects/adaptivecar.cpp \
    #objects/airplane.cpp \
    objects/car.cpp \
    objects/mesh.cpp \
    objects/part.cpp \
    objects/planet.cpp \
    objects/road.cpp \
    objects/sbody.cpp \
    objects/terrain.cpp \
    #objects/wing.cpp \
    sims/carsimulation.cpp \
    sims/orbitalsimulation.cpp \
    sims/restricted3bodysimulation.cpp \
    sims/simulation.cpp \
    sims/twobodysimulation.cpp \
    mainviewwidget.cpp \
    window.cpp

HEADERS  += common/camera3D.h \
    common/control.h \
    common/input.h \
    common/output.h \
    common/textures.h \
    common/transform3d.h \
    common/vertex.h \
    #common/dynamiccontrol.h \
    cst/complexnumber.h \
    cst/cst.h \
    cst/pfd.h \
    cst/transferfunction.h \
    GL/eglew.h \
    GL/glew.h \
    GL/glxew.h \
    GL/wglew.h \
    glm/detail/_features.hpp \
    glm/detail/_fixes.hpp \
    glm/detail/_noise.hpp \
    glm/detail/_swizzle.hpp \
    glm/detail/_swizzle_func.hpp \
    glm/detail/_vectorize.hpp \
    glm/detail/func_common.hpp \
    glm/detail/func_exponential.hpp \
    glm/detail/func_geometric.hpp \
    glm/detail/func_integer.hpp \
    glm/detail/func_matrix.hpp \
    glm/detail/func_packing.hpp \
    glm/detail/func_trigonometric.hpp \
    glm/detail/func_vector_relational.hpp \
    glm/detail/intrinsic_common.hpp \
    glm/detail/intrinsic_exponential.hpp \
    glm/detail/intrinsic_geometric.hpp \
    glm/detail/intrinsic_integer.hpp \
    glm/detail/intrinsic_matrix.hpp \
    glm/detail/intrinsic_trigonometric.hpp \
    glm/detail/intrinsic_vector_relational.hpp \
    glm/detail/precision.hpp \
    glm/detail/setup.hpp \
    glm/detail/type_float.hpp \
    glm/detail/type_gentype.hpp \
    glm/detail/type_half.hpp \
    glm/detail/type_int.hpp \
    glm/detail/type_mat.hpp \
    glm/detail/type_mat2x2.hpp \
    glm/detail/type_mat2x3.hpp \
    glm/detail/type_mat2x4.hpp \
    glm/detail/type_mat3x2.hpp \
    glm/detail/type_mat3x3.hpp \
    glm/detail/type_mat3x4.hpp \
    glm/detail/type_mat4x2.hpp \
    glm/detail/type_mat4x3.hpp \
    glm/detail/type_mat4x4.hpp \
    glm/detail/type_vec.hpp \
    glm/detail/type_vec1.hpp \
    glm/detail/type_vec2.hpp \
    glm/detail/type_vec3.hpp \
    glm/detail/type_vec4.hpp \
    glm/gtc/bitfield.hpp \
    glm/gtc/color_space.hpp \
    glm/gtc/constants.hpp \
    glm/gtc/epsilon.hpp \
    glm/gtc/integer.hpp \
    glm/gtc/matrix_access.hpp \
    glm/gtc/matrix_integer.hpp \
    glm/gtc/matrix_inverse.hpp \
    glm/gtc/matrix_transform.hpp \
    glm/gtc/noise.hpp \
    glm/gtc/packing.hpp \
    glm/gtc/quaternion.hpp \
    glm/gtc/random.hpp \
    glm/gtc/reciprocal.hpp \
    glm/gtc/round.hpp \
    glm/gtc/type_precision.hpp \
    glm/gtc/type_ptr.hpp \
    glm/gtc/ulp.hpp \
    glm/gtc/vec1.hpp \
    glm/gtx/associated_min_max.hpp \
    glm/gtx/bit.hpp \
    glm/gtx/closest_point.hpp \
    glm/gtx/color_space.hpp \
    glm/gtx/color_space_YCoCg.hpp \
    glm/gtx/common.hpp \
    glm/gtx/compatibility.hpp \
    glm/gtx/component_wise.hpp \
    glm/gtx/dual_quaternion.hpp \
    glm/gtx/euler_angles.hpp \
    glm/gtx/extend.hpp \
    glm/gtx/extented_min_max.hpp \
    glm/gtx/fast_exponential.hpp \
    glm/gtx/fast_square_root.hpp \
    glm/gtx/fast_trigonometry.hpp \
    glm/gtx/gradient_paint.hpp \
    glm/gtx/handed_coordinate_space.hpp \
    glm/gtx/hash.hpp \
    glm/gtx/integer.hpp \
    glm/gtx/intersect.hpp \
    glm/gtx/io.hpp \
    glm/gtx/log_base.hpp \
    glm/gtx/matrix_cross_product.hpp \
    glm/gtx/matrix_decompose.hpp \
    glm/gtx/matrix_interpolation.hpp \
    glm/gtx/matrix_major_storage.hpp \
    glm/gtx/matrix_operation.hpp \
    glm/gtx/matrix_query.hpp \
    glm/gtx/matrix_transform_2d.hpp \
    glm/gtx/mixed_product.hpp \
    glm/gtx/norm.hpp \
    glm/gtx/normal.hpp \
    glm/gtx/normalize_dot.hpp \
    glm/gtx/number_precision.hpp \
    glm/gtx/optimum_pow.hpp \
    glm/gtx/orthonormalize.hpp \
    glm/gtx/perpendicular.hpp \
    glm/gtx/polar_coordinates.hpp \
    glm/gtx/projection.hpp \
    glm/gtx/quaternion.hpp \
    glm/gtx/range.hpp \
    glm/gtx/raw_data.hpp \
    glm/gtx/rotate_normalized_axis.hpp \
    glm/gtx/rotate_vector.hpp \
    glm/gtx/scalar_multiplication.hpp \
    glm/gtx/scalar_relational.hpp \
    glm/gtx/simd_mat4.hpp \
    glm/gtx/simd_quat.hpp \
    glm/gtx/simd_vec4.hpp \
    glm/gtx/spline.hpp \
    glm/gtx/std_based_type.hpp \
    glm/gtx/string_cast.hpp \
    glm/gtx/transform.hpp \
    glm/gtx/transform2.hpp \
    glm/gtx/type_aligned.hpp \
    glm/gtx/vector_angle.hpp \
    glm/gtx/vector_query.hpp \
    glm/gtx/wrap.hpp \
    glm/common.hpp \
    glm/exponential.hpp \
    glm/ext.hpp \
    glm/fwd.hpp \
    glm/geometric.hpp \
    glm/glm.hpp \
    glm/integer.hpp \
    glm/mat2x2.hpp \
    glm/mat2x3.hpp \
    glm/mat2x4.hpp \
    glm/mat3x2.hpp \
    glm/mat3x3.hpp \
    glm/mat3x4.hpp \
    glm/mat4x2.hpp \
    glm/mat4x3.hpp \
    glm/mat4x4.hpp \
    glm/matrix.hpp \
    glm/packing.hpp \
    glm/trigonometric.hpp \
    glm/vec2.hpp \
    glm/vec3.hpp \
    glm/vec4.hpp \
    glm/vector_relational.hpp \
    nums/AbstractOdeSolver.hpp \
    nums/AdaptiveRungeKuttaSolver.h \
    nums/Restricted3BodySolver.h \
    nums/RungeKuttaSolver.hpp \
    nums/TwoBodySolver.h \
    objects/adaptivecar.h \
    #objects/airplane.h \
    objects/car.h \
    objects/mesh.h \
    objects/part.h \
    objects/planet.h \
    objects/road.h \
    objects/sbody.h \
    objects/terrain.h \
    #objects/wing.h \
    objects/controllablepart.h \
    sims/carsimulation.h \
    sims/orbitalsimulation.h \
    sims/restricted3bodysimulation.h \
    sims/simulation.h \
    sims/twobodysimulation.h \
    mainviewwidget.h \
    window.h

FORMS    += window.ui

DISTFILES += \
    SimpleFragmentShader.fragmentshader \
    SimpleVertexShader.vertexshader \
    shaders/simple.vert \
    shaders/simple.frag \
    shaders/texturediffuse.fsh \
    shaders/texturedDiffuse.frag \
    shaders/texturedDiffuse.vert \
    nums/hello-c-world \
    nums/hello-cpp-world \
    nums/data.txt \
    glm/CMakeLists.txt \
    nums/README.md \
    sample.py \
    Data/Terrain/terrain0-8bbp-257x257.raw \
    Data/Terrain/terrain0-16bbp-257x257.raw \
    Data/Textures/grass.jpg \
    Data/Textures/skydome4.jpg \
    Data/Textures/snow.jpg \
    Data/Textures/rock.png \
    Data/Objects/cube.obj

RESOURCES += \
    resources.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/release/ -lpython3.5m
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/debug/ -lpython3.5m
else:unix: LIBS += -L$$PWD/../../../../Applications/anaconda/lib/ -lpython3.5m

LIBS += -L$$PWD/../../../../Applications/anaconda/lib/ -lpython3.5m
INCLUDEPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m
DEPENDPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m

#INCLUDEPATH += /usr/local/Cellar/boost/1.60.0_2/include/
#LIBS += -L/usr/local/Cellar/boost/1.60.0_2/lib/ -lboost_filesystem -lboost_system

CONFIG += no_keywords

QMAKE_MAC_SDK = macosx10.12

#CONFIG += qwt
#INCLUDEPATH +="/usr/local/qwt-6.1.3/include"
#LIBS += -L/usr/local/qwt-6.1.3/lib -lqwt
