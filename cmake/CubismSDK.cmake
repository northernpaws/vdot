set(CUBISM_SDK_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extern/cubism)
set(CUBISM_CORE_PATH ${CUBISM_SDK_ROOT_PATH}/Core)
set(CUBISM_FRAMEWORK_PATH ${CUBISM_SDK_ROOT_PATH}/Framework)
set(CUBISM_THIRD_PARTY_PATH ${CUBISM_SDK_ROOT_PATH}/Samples/OpenGL/thirdParty)
set(CUBISM_STB_PATH ${CUBISM_THIRD_PARTY_PATH}/stb)

if (WIN32)
    include(${CMAKE_CURRENT_LIST_DIR}/cubism/windows.cmake)
elseif(ANDROID)
    include(${CMAKE_CURRENT_LIST_DIR}/cubism/android.cmake)
elseif(IOS)
    include(${CMAKE_CURRENT_LIST_DIR}/cubism/ios.cmake)
elseif(UNIX AND APPLE)
    include(${CMAKE_CURRENT_LIST_DIR}/cubism/macos.cmake)
elseif(UNIX)
    include(${CMAKE_CURRENT_LIST_DIR}/cubism/unix.cmake)
endif()

include_directories(SYSTEM ${CUBISM_CORE_PATH}/include)

add_subdirectory(${CUBISM_FRAMEWORK_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Framework)

# There's an issue with Cubsim trying to force us to select a pre-existing renderer,
# defaulting to Cocos. Strip the Cocos files from the target so they don't try to build.
get_target_property(Framework_Sources Framework SOURCES)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismOffscreenSurface_Cocos2dx.cpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismOffscreenSurface_Cocos2dx.hpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismRenderer_Cocos2dx.cpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismRenderer_Cocos2dx.hpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismShader_Cocos2dx.cpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismShader_Cocos2dx.hpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismCommandBuffer_Cocos2dx.cpp)
list(REMOVE_ITEM Framework_Sources ${CUBISM_FRAMEWORK_PATH}/src/Rendering/Cocos2d/CubismCommandBuffer_Cocos2dx.hpp)
set_target_properties(Framework PROPERTIES
        SOURCES "${Framework_Sources}"
)

# Re-write the scope of the Framework includes to be system,
# otherwise we get warnings and errors from them.
get_target_property(Framework_Public_Include Framework INTERFACE_INCLUDE_DIRECTORIES)
set_target_properties(Framework PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${Framework_Public_Include}
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${Framework_Public_Include}
)

target_link_libraries(Framework Live2DCubismCore)
