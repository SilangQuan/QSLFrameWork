CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(QSLFrameWork)

INCLUDE_DIRECTORIES(
	${QSLFrameWork_SOURCE_DIR}/include
)

LINK_DIRECTORIES( 
	/usr/lib64/
)

SET(SRC_LIST main.cpp src/cgl.cpp src/shaderprogram.cpp src/util.cpp src/csdl2.cpp src/cassimpmodel.cpp src/ctexture.cpp)

ADD_EXECUTABLE(main ${SRC_LIST})

TARGET_LINK_LIBRARIES(main SDL2 GL GLU GLEW assimp SDL2_image)
