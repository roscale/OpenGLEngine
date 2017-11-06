cmake_minimum_required(VERSION 3.9)
project(OpenGLEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        rendering/DisplayManager.cpp rendering/DisplayManager.hpp
        models/Model.cpp models/Model.hpp
        rendering/Loader.cpp rendering/Loader.hpp
        rendering/Renderer.cpp rendering/Renderer.hpp
        rendering/ShaderProgram.cpp rendering/ShaderProgram.hpp
        rendering/StaticShader.cpp rendering/StaticShader.hpp
        rendering/Texture.cpp rendering/Texture.hpp
        components/Camera.cpp components/Camera.hpp
        prefabs/GameObject.cpp prefabs/GameObject.hpp
        components/Component.cpp components/Component.hpp
        components/Transform.cpp components/Transform.hpp
        core/World.cpp core/World.hpp
        components/Mesh.cpp components/Mesh.hpp
        components/MeshRenderer.cpp components/MeshRenderer.hpp
        rendering/OBJLoader.cpp rendering/OBJLoader.hpp
        components/Light.cpp components/Light.hpp
        components/Terrain.cpp components/Terrain.hpp
        core/InputManager.cpp core/InputManager.hpp
        core/Script.hpp
        interfaces/IEvents.cpp interfaces/IEvents.hpp
        settings.cpp settings.hpp
        core/Time.cpp core/Time.hpp
        util/util.cpp util/util.hpp
        util/Bitmap.cpp util/Bitmap.hpp)

add_executable(OpenGLEngine ${SOURCE_FILES})

#find_library(BOOST_LIB boost)
#message(${BOOST_LIB})

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

find_library(GL_LIB GL)
message(${GL_LIB})
target_link_libraries(OpenGLEngine ${GL_LIB})

find_library(GLEW_LIB GLEW)
message(${GLEW_LIB})
target_link_libraries(OpenGLEngine ${GLEW_LIB})

find_library(GLFW_LIB glfw)
message(${GLFW_LIB})
target_link_libraries(OpenGLEngine ${GLFW_LIB})