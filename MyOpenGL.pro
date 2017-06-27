#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T09:56:08
#
#-------------------------------------------------

QT       += core gui opengl charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app


CONFIG       += plugin static
QT           += widgets

LIBS           = -L$$PWD/plugins/

macx-xcode {
    LIBS += -lSatelliteTrackingPlugin$($${QMAKE_XCODE_LIBRARY_SUFFIX_SETTING})
} else {
    LIBS += -lSatelliteTrackingPlugin
    if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
        mac:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)_debug
        win32:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)d
    }
}

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/plugins/release/ -lSatelliteTrackingPlugin_debug
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/plugins/debug/ -lSatelliteTrackingPlugin_debug
#else:unix: LIBS += -L$$PWD/plugins/ -lSatelliteTrackingPlugin_debug

#INCLUDEPATH += $$PWD/plugins
#DEPENDPATH += $$PWD/plugins

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/plugins/release/libSatelliteTrackingPlugin_debug.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/plugins/debug/libSatelliteTrackingPlugin_debug.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/plugins/release/SatelliteTrackingPlugin_debug.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/plugins/debug/SatelliteTrackingPlugin_debug.lib
#else:unix: PRE_TARGETDEPS += $$PWD/plugins/libSatelliteTrackingPlugin_debug.a


SOURCES += \
    Common/Camera3D.cpp \
    Common/Control.cpp \
    Common/Input.cpp \
    Common/Output.cpp \
    Common/Textures.cpp \
    Common/Transform3d.cpp \
    Cst/ComplexNumber.cpp \
    Cst/Cst.cpp \
    Cst/Pfd.cpp \
    Cst/TransferFunction.cpp \
    Kalman/FusionEKF.cpp \
    Kalman/OrbitDeterminationFilter.cpp \
    Nums/AbstractOdeSolver.cpp \
    Nums/AdaptiveRungeKuttaSolver.cpp \
    Nums/Restricted3BodySolver.cpp \
    Nums/RungeKuttaSolver.cpp \
    Nums/TwoBodySolver.cpp \
    Nums/EarthRotationSolver.cpp \
    Nums/GroundTrackingSolver.cpp \
    Nums/SatelliteSolver.cpp \
    Nums/FiniteDifferenceGrid.cpp \
    Nums/BoundaryValueProblem.cpp \
    Nums/DifferentialSystem.cpp \
    Objects/SimObject.cpp \
    Objects/Controllable.cpp \
    Window.cpp \
    MainViewWidget.cpp \
    Sims/Simulation.cpp \
    Sims/OrbitalSimulation.cpp \
    Orbital/Omt.cpp \
    main.cpp \
    Objects/Terrain.cpp \
    Objects/AdaptiveCar.cpp \
    Objects/Car.cpp \
    Objects/Mesh.cpp \
    Objects/Part.cpp \
    Objects/Road.cpp \
    Objects/Satellite.cpp \
    Kalman/CarFilterTools.cpp \
    Kalman/KalmanFilter.cpp \
    Kalman/UnscentedKalmanFilter.cpp

HEADERS  += \
    Common/Camera3D.hpp \
    Common/Control.hpp \
    Common/Input.hpp \
    Common/Output.hpp \
    Common/Textures.hpp \
    Common/Transform3d.hpp \
    Common/Vertex.hpp \
    Cst/Cst.hpp \
    Cst/Pfd.hpp \
    Cst/TransferFunction.hpp \
    Cst/ComplexNumber.hpp \
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
    Nums/AbstractOdeSolver.hpp \
    Nums/RungeKuttaSolver.hpp \
    Eigen/src/Cholesky/LDLT.h \
    Eigen/src/Cholesky/LLT.h \
    Eigen/src/Cholesky/LLT_MKL.h \
    Eigen/src/CholmodSupport/CholmodSupport.h \
    Eigen/src/Core/arch/AltiVec/Complex.h \
    Eigen/src/Core/arch/AltiVec/PacketMath.h \
    Eigen/src/Core/arch/Default/Settings.h \
    Eigen/src/Core/arch/NEON/Complex.h \
    Eigen/src/Core/arch/NEON/PacketMath.h \
    Eigen/src/Core/arch/SSE/Complex.h \
    Eigen/src/Core/arch/SSE/MathFunctions.h \
    Eigen/src/Core/arch/SSE/PacketMath.h \
    Eigen/src/Core/products/CoeffBasedProduct.h \
    Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    Eigen/src/Core/products/GeneralMatrixMatrix.h \
    Eigen/src/Core/products/GeneralMatrixMatrix_MKL.h \
    Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    Eigen/src/Core/products/GeneralMatrixMatrixTriangular_MKL.h \
    Eigen/src/Core/products/GeneralMatrixVector.h \
    Eigen/src/Core/products/GeneralMatrixVector_MKL.h \
    Eigen/src/Core/products/Parallelizer.h \
    Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    Eigen/src/Core/products/SelfadjointMatrixMatrix_MKL.h \
    Eigen/src/Core/products/SelfadjointMatrixVector.h \
    Eigen/src/Core/products/SelfadjointMatrixVector_MKL.h \
    Eigen/src/Core/products/SelfadjointProduct.h \
    Eigen/src/Core/products/SelfadjointRank2Update.h \
    Eigen/src/Core/products/TriangularMatrixMatrix.h \
    Eigen/src/Core/products/TriangularMatrixMatrix_MKL.h \
    Eigen/src/Core/products/TriangularMatrixVector.h \
    Eigen/src/Core/products/TriangularMatrixVector_MKL.h \
    Eigen/src/Core/products/TriangularSolverMatrix.h \
    Eigen/src/Core/products/TriangularSolverMatrix_MKL.h \
    Eigen/src/Core/products/TriangularSolverVector.h \
    Eigen/src/Core/util/BlasUtil.h \
    Eigen/src/Core/util/Constants.h \
    Eigen/src/Core/util/DisableStupidWarnings.h \
    Eigen/src/Core/util/ForwardDeclarations.h \
    Eigen/src/Core/util/Macros.h \
    Eigen/src/Core/util/Memory.h \
    Eigen/src/Core/util/Meta.h \
    Eigen/src/Core/util/MKL_support.h \
    Eigen/src/Core/util/NonMPL2.h \
    Eigen/src/Core/util/ReenableStupidWarnings.h \
    Eigen/src/Core/util/StaticAssert.h \
    Eigen/src/Core/util/XprHelper.h \
    Eigen/src/Core/Array.h \
    Eigen/src/Core/ArrayBase.h \
    Eigen/src/Core/ArrayWrapper.h \
    Eigen/src/Core/Assign.h \
    Eigen/src/Core/Assign_MKL.h \
    Eigen/src/Core/BandMatrix.h \
    Eigen/src/Core/Block.h \
    Eigen/src/Core/BooleanRedux.h \
    Eigen/src/Core/CommaInitializer.h \
    Eigen/src/Core/CoreIterators.h \
    Eigen/src/Core/CwiseBinaryOp.h \
    Eigen/src/Core/CwiseNullaryOp.h \
    Eigen/src/Core/CwiseUnaryOp.h \
    Eigen/src/Core/CwiseUnaryView.h \
    Eigen/src/Core/DenseBase.h \
    Eigen/src/Core/DenseCoeffsBase.h \
    Eigen/src/Core/DenseStorage.h \
    Eigen/src/Core/Diagonal.h \
    Eigen/src/Core/DiagonalMatrix.h \
    Eigen/src/Core/DiagonalProduct.h \
    Eigen/src/Core/Dot.h \
    Eigen/src/Core/EigenBase.h \
    Eigen/src/Core/Flagged.h \
    Eigen/src/Core/ForceAlignedAccess.h \
    Eigen/src/Core/Functors.h \
    Eigen/src/Core/Fuzzy.h \
    Eigen/src/Core/GeneralProduct.h \
    Eigen/src/Core/GenericPacketMath.h \
    Eigen/src/Core/GlobalFunctions.h \
    Eigen/src/Core/IO.h \
    Eigen/src/Core/Map.h \
    Eigen/src/Core/MapBase.h \
    Eigen/src/Core/MathFunctions.h \
    Eigen/src/Core/Matrix.h \
    Eigen/src/Core/MatrixBase.h \
    Eigen/src/Core/NestByValue.h \
    Eigen/src/Core/NoAlias.h \
    Eigen/src/Core/NumTraits.h \
    Eigen/src/Core/PermutationMatrix.h \
    Eigen/src/Core/PlainObjectBase.h \
    Eigen/src/Core/ProductBase.h \
    Eigen/src/Core/Random.h \
    Eigen/src/Core/Redux.h \
    Eigen/src/Core/Ref.h \
    Eigen/src/Core/Replicate.h \
    Eigen/src/Core/ReturnByValue.h \
    Eigen/src/Core/Reverse.h \
    Eigen/src/Core/Select.h \
    Eigen/src/Core/SelfAdjointView.h \
    Eigen/src/Core/SelfCwiseBinaryOp.h \
    Eigen/src/Core/SolveTriangular.h \
    Eigen/src/Core/StableNorm.h \
    Eigen/src/Core/Stride.h \
    Eigen/src/Core/Swap.h \
    Eigen/src/Core/Transpose.h \
    Eigen/src/Core/Transpositions.h \
    Eigen/src/Core/TriangularMatrix.h \
    Eigen/src/Core/VectorBlock.h \
    Eigen/src/Core/VectorwiseOp.h \
    Eigen/src/Core/Visitor.h \
    Eigen/src/Eigen2Support/Geometry/AlignedBox.h \
    Eigen/src/Eigen2Support/Geometry/All.h \
    Eigen/src/Eigen2Support/Geometry/AngleAxis.h \
    Eigen/src/Eigen2Support/Geometry/Hyperplane.h \
    Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h \
    Eigen/src/Eigen2Support/Geometry/Quaternion.h \
    Eigen/src/Eigen2Support/Geometry/Rotation2D.h \
    Eigen/src/Eigen2Support/Geometry/RotationBase.h \
    Eigen/src/Eigen2Support/Geometry/Scaling.h \
    Eigen/src/Eigen2Support/Geometry/Transform.h \
    Eigen/src/Eigen2Support/Geometry/Translation.h \
    Eigen/src/Eigen2Support/Block.h \
    Eigen/src/Eigen2Support/Cwise.h \
    Eigen/src/Eigen2Support/CwiseOperators.h \
    Eigen/src/Eigen2Support/Lazy.h \
    Eigen/src/Eigen2Support/LeastSquares.h \
    Eigen/src/Eigen2Support/LU.h \
    Eigen/src/Eigen2Support/Macros.h \
    Eigen/src/Eigen2Support/MathFunctions.h \
    Eigen/src/Eigen2Support/Memory.h \
    Eigen/src/Eigen2Support/Meta.h \
    Eigen/src/Eigen2Support/Minor.h \
    Eigen/src/Eigen2Support/QR.h \
    Eigen/src/Eigen2Support/SVD.h \
    Eigen/src/Eigen2Support/TriangularSolver.h \
    Eigen/src/Eigen2Support/VectorBlock.h \
    Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    Eigen/src/Eigenvalues/ComplexSchur.h \
    Eigen/src/Eigenvalues/ComplexSchur_MKL.h \
    Eigen/src/Eigenvalues/EigenSolver.h \
    Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    Eigen/src/Eigenvalues/RealQZ.h \
    Eigen/src/Eigenvalues/RealSchur.h \
    Eigen/src/Eigenvalues/RealSchur_MKL.h \
    Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    Eigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h \
    Eigen/src/Eigenvalues/Tridiagonalization.h \
    Eigen/src/Geometry/arch/Geometry_SSE.h \
    Eigen/src/Geometry/AlignedBox.h \
    Eigen/src/Geometry/AngleAxis.h \
    Eigen/src/Geometry/EulerAngles.h \
    Eigen/src/Geometry/Homogeneous.h \
    Eigen/src/Geometry/Hyperplane.h \
    Eigen/src/Geometry/OrthoMethods.h \
    Eigen/src/Geometry/ParametrizedLine.h \
    Eigen/src/Geometry/Quaternion.h \
    Eigen/src/Geometry/Rotation2D.h \
    Eigen/src/Geometry/RotationBase.h \
    Eigen/src/Geometry/Scaling.h \
    Eigen/src/Geometry/Transform.h \
    Eigen/src/Geometry/Translation.h \
    Eigen/src/Geometry/Umeyama.h \
    Eigen/src/Householder/BlockHouseholder.h \
    Eigen/src/Householder/Householder.h \
    Eigen/src/Householder/HouseholderSequence.h \
    Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    Eigen/src/Jacobi/Jacobi.h \
    Eigen/src/LU/arch/Inverse_SSE.h \
    Eigen/src/LU/Determinant.h \
    Eigen/src/LU/FullPivLU.h \
    Eigen/src/LU/Inverse.h \
    Eigen/src/LU/PartialPivLU.h \
    Eigen/src/LU/PartialPivLU_MKL.h \
    Eigen/src/MetisSupport/MetisSupport.h \
    Eigen/src/misc/blas.h \
    Eigen/src/misc/Image.h \
    Eigen/src/misc/Kernel.h \
    Eigen/src/misc/Solve.h \
    Eigen/src/misc/SparseSolve.h \
    Eigen/src/OrderingMethods/Amd.h \
    Eigen/src/OrderingMethods/Eigen_Colamd.h \
    Eigen/src/OrderingMethods/Ordering.h \
    Eigen/src/PardisoSupport/PardisoSupport.h \
    Eigen/src/PaStiXSupport/PaStiXSupport.h \
    Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    Eigen/src/plugins/BlockMethods.h \
    Eigen/src/plugins/CommonCwiseBinaryOps.h \
    Eigen/src/plugins/CommonCwiseUnaryOps.h \
    Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    Eigen/src/QR/ColPivHouseholderQR.h \
    Eigen/src/QR/ColPivHouseholderQR_MKL.h \
    Eigen/src/QR/FullPivHouseholderQR.h \
    Eigen/src/QR/HouseholderQR.h \
    Eigen/src/QR/HouseholderQR_MKL.h \
    Eigen/src/SparseCholesky/SimplicialCholesky.h \
    Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    Eigen/src/SparseCore/AmbiVector.h \
    Eigen/src/SparseCore/CompressedStorage.h \
    Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    Eigen/src/SparseCore/MappedSparseMatrix.h \
    Eigen/src/SparseCore/SparseBlock.h \
    Eigen/src/SparseCore/SparseColEtree.h \
    Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    Eigen/src/SparseCore/SparseDenseProduct.h \
    Eigen/src/SparseCore/SparseDiagonalProduct.h \
    Eigen/src/SparseCore/SparseDot.h \
    Eigen/src/SparseCore/SparseFuzzy.h \
    Eigen/src/SparseCore/SparseMatrix.h \
    Eigen/src/SparseCore/SparseMatrixBase.h \
    Eigen/src/SparseCore/SparsePermutation.h \
    Eigen/src/SparseCore/SparseProduct.h \
    Eigen/src/SparseCore/SparseRedux.h \
    Eigen/src/SparseCore/SparseSelfAdjointView.h \
    Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    Eigen/src/SparseCore/SparseTranspose.h \
    Eigen/src/SparseCore/SparseTriangularView.h \
    Eigen/src/SparseCore/SparseUtil.h \
    Eigen/src/SparseCore/SparseVector.h \
    Eigen/src/SparseCore/SparseView.h \
    Eigen/src/SparseCore/TriangularSolver.h \
    Eigen/src/SparseLU/SparseLU.h \
    Eigen/src/SparseLU/SparseLU_column_bmod.h \
    Eigen/src/SparseLU/SparseLU_column_dfs.h \
    Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    Eigen/src/SparseLU/SparseLU_Memory.h \
    Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    Eigen/src/SparseLU/SparseLU_pivotL.h \
    Eigen/src/SparseLU/SparseLU_pruneL.h \
    Eigen/src/SparseLU/SparseLU_relax_snode.h \
    Eigen/src/SparseLU/SparseLU_Structs.h \
    Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    Eigen/src/SparseLU/SparseLU_Utils.h \
    Eigen/src/SparseLU/SparseLUImpl.h \
    Eigen/src/SparseQR/SparseQR.h \
    Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    Eigen/src/StlSupport/details.h \
    Eigen/src/StlSupport/StdDeque.h \
    Eigen/src/StlSupport/StdList.h \
    Eigen/src/StlSupport/StdVector.h \
    Eigen/src/SuperLUSupport/SuperLUSupport.h \
    Eigen/src/SVD/JacobiSVD.h \
    Eigen/src/SVD/JacobiSVD_MKL.h \
    Eigen/src/SVD/UpperBidiagonalization.h \
    Eigen/src/UmfPackSupport/UmfPackSupport.h \
    Eigen/Array \
    Eigen/Cholesky \
    Eigen/CholmodSupport \
    Eigen/Core \
    Eigen/Dense \
    Eigen/Eigen \
    Eigen/Eigen2Support \
    Eigen/Eigenvalues \
    Eigen/Geometry \
    Eigen/Householder \
    Eigen/IterativeLinearSolvers \
    Eigen/Jacobi \
    Eigen/LeastSquares \
    Eigen/LU \
    Eigen/MetisSupport \
    Eigen/OrderingMethods \
    Eigen/PardisoSupport \
    Eigen/PaStiXSupport \
    Eigen/QR \
    Eigen/QtAlignedMalloc \
    Eigen/Sparse \
    Eigen/SparseCholesky \
    Eigen/SparseCore \
    Eigen/SparseLU \
    Eigen/SparseQR \
    Eigen/SPQRSupport \
    Eigen/StdDeque \
    Eigen/StdList \
    Eigen/StdVector \
    Eigen/SuperLUSupport \
    Eigen/SVD \
    Eigen/UmfPackSupport \
    Nums/BoundaryValueProblem.hpp \
    Nums/Node.hpp \
    Nums/DifferentialSystem.hpp \
    Nums/FiniteDifferenceGrid.hpp \
    SimulationInterface.hpp \
    Objects/SimObject.hpp \
    MainViewWidget.hpp \
    Window.hpp \
    Sims/Simulation.hpp \
    Sims/OrbitalSimulation.hpp \
    Orbital/Omt.hpp \
    Objects/Terrain.hpp \
    Objects/Adaptivecar.hpp \
    Objects/Car.hpp \
    Objects/Controllable.hpp \
    Objects/Mesh.hpp \
    Objects/Part.hpp \
    Objects/Road.hpp \
    Objects/Satellite.hpp \
    Kalman/CarFilterTools.hpp \
    Kalman/MeasurementPackage.hpp \
    Kalman/GroundTruthPackage.hpp \
    Kalman/FusionEKF.hpp \
    Kalman/KalmanFilter.hpp \
    Kalman/UnscentedKalmanFilter.hpp \
    Kalman/OrbitMeasurementPackage.hpp \
    Kalman/OrbitDeterminationFilter.hpp \
    Nums/AdaptiveRungeKuttaSolver.hpp \
    Nums/EarthRotationSolver.hpp \
    Nums/GroundTrackingSolver.hpp \
    Nums/Restricted3BodySolver.hpp \
    Nums/SatelliteSolver.hpp \
    Nums/TwoBodySolver.hpp

#FORMS    += \
#    Window.ui

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
    Data/Objects/cube.obj \
    Eigen/src/Cholesky/CMakeLists.txt \
    Eigen/src/CholmodSupport/CMakeLists.txt \
    Eigen/src/Core/arch/AltiVec/CMakeLists.txt \
    Eigen/src/Core/arch/Default/CMakeLists.txt \
    Eigen/src/Core/arch/NEON/CMakeLists.txt \
    Eigen/src/Core/arch/SSE/CMakeLists.txt \
    Eigen/src/Core/arch/CMakeLists.txt \
    Eigen/src/Core/products/CMakeLists.txt \
    Eigen/src/Core/util/CMakeLists.txt \
    Eigen/src/Core/CMakeLists.txt \
    Eigen/src/Eigen2Support/Geometry/CMakeLists.txt \
    Eigen/src/Eigen2Support/CMakeLists.txt \
    Eigen/src/Eigenvalues/CMakeLists.txt \
    Eigen/src/Geometry/arch/CMakeLists.txt \
    Eigen/src/Geometry/CMakeLists.txt \
    Eigen/src/Householder/CMakeLists.txt \
    Eigen/src/IterativeLinearSolvers/CMakeLists.txt \
    Eigen/src/Jacobi/CMakeLists.txt \
    Eigen/src/LU/arch/CMakeLists.txt \
    Eigen/src/LU/CMakeLists.txt \
    Eigen/src/MetisSupport/CMakeLists.txt \
    Eigen/src/misc/CMakeLists.txt \
    Eigen/src/OrderingMethods/CMakeLists.txt \
    Eigen/src/PardisoSupport/CMakeLists.txt \
    Eigen/src/PaStiXSupport/CMakeLists.txt \
    Eigen/src/plugins/CMakeLists.txt \
    Eigen/src/QR/CMakeLists.txt \
    Eigen/src/SparseCholesky/CMakeLists.txt \
    Eigen/src/SparseCore/CMakeLists.txt \
    Eigen/src/SparseLU/CMakeLists.txt \
    Eigen/src/SparseQR/CMakeLists.txt \
    Eigen/src/SPQRSupport/CMakeLists.txt \
    Eigen/src/StlSupport/CMakeLists.txt \
    Eigen/src/SuperLUSupport/CMakeLists.txt \
    Eigen/src/SVD/CMakeLists.txt \
    Eigen/src/UmfPackSupport/CMakeLists.txt \
    Eigen/src/CMakeLists.txt \
    Eigen/CMakeLists.txt

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


