cmake_minimum_required(VERSION 2.8)

set(APP_NAME MyGame)
project (${APP_NAME})

include(cocos2d/build/BuildHelpers.CMakeLists.txt)


option(DEBUG_MODE "Debug or release?" ON)

if(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

if (MSVC)
	set(CMAKE_C_FLAGS_DEBUG "-DCOCOS2D_DEBUG=1")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")

elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")

    if(CLANG)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wc++1y-extensions -Wno-deprecated-declarations -Wno-reorder")
if(CLANG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

if( MACOSX )
set(GAME_SRC
  proj.ios_mac/mac/main.cpp
  Classes/AppDelegate.cpp
  Classes/MainScene.cpp
  Classes/Board.cpp
)
elseif( UNIX ) #assume linux
set(GAME_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
  Classes/MainScene.cpp
  Classes/Board.h
)
elseif ( WIN32 )
set(GAME_SRC
  proj.win32/main.cpp
  proj.win32/main.h
  proj.win32/resource.h
  Classes/AppDelegate.cpp
  Classes/MainScene.cpp
)
endif()

set(GAME_RESOURCES
  Resources/CloseNormal.png
  Resources/CloseSelected.png
  Resources/HelloWorld.png
)

set_source_files_properties(
    ${GAME_RESOURCES}
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
)

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)
if (WIN32)
include_directories(
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/cocos/audio/include
  ${COCOS2D_ROOT}/cocos/2d
  ${COCOS2D_ROOT}/cocos/2d/renderer
  ${COCOS2D_ROOT}/cocos/2d/platform
  ${COCOS2D_ROOT}/cocos/2d/platform/desktop
  ${COCOS2D_ROOT}/cocos/2d/platform/win32
  ${COCOS2D_ROOT}/cocos/base
  ${COCOS2D_ROOT}/cocos/deprecated
  ${COCOS2D_ROOT}/cocos/physics
  ${COCOS2D_ROOT}/cocos/editor-support
  ${COCOS2D_ROOT}/cocos/math
  ${COCOS2D_ROOT}/extensions
  ${COCOS2D_ROOT}/external
  ${COCOS2D_ROOT}/external/edtaa3func
  ${COCOS2D_ROOT}/external/jpeg/include/win32
  ${COCOS2D_ROOT}/external/png/include/win32
  ${COCOS2D_ROOT}/external/tiff/include/win32
  ${COCOS2D_ROOT}/external/webp/include/win32
  ${COCOS2D_ROOT}/external/curl/include/win32
  ${COCOS2D_ROOT}/external/tinyxml2
  ${COCOS2D_ROOT}/external/unzip
  ${COCOS2D_ROOT}/external/sqlite3/include
  ${COCOS2D_ROOT}/external/chipmunk/include/chipmunk
  ${COCOS2D_ROOT}/external/freetype2/include/win32
  ${COCOS2D_ROOT}/external/websockets/include/win32
  ${COCOS2D_ROOT}/external/spidermonkey/include/win32
  ${COCOS2D_ROOT}/external/glfw3/include/win32
  ${COCOS2D_ROOT}/external/win32-specific/gles/include/OGLES
  ${COCOS2D_ROOT}/external/win32-specific/icon/include
  ${COCOS2D_ROOT}/external/win32-specific/zlib/include
  ${COCOS2D_ROOT}/external/xxhash
)
link_directories(
  /usr/local/lib
  ${COCOS2D_ROOT}/external/png/prebuilt/win32
  ${COCOS2D_ROOT}/external/jpeg/prebuilt/win32
  ${COCOS2D_ROOT}/external/tiff/prebuilt/win32
  ${COCOS2D_ROOT}/external/glfw3/prebuilt/win32
  ${COCOS2D_ROOT}/external/webp/prebuilt/win32
  ${COCOS2D_ROOT}/external/curl/prebuilt/win32
  ${COCOS2D_ROOT}/external/sqlite3/libraries/win32
  ${COCOS2D_ROOT}/external/freetype2/prebuilt/win32
  ${COCOS2D_ROOT}/external/websockets/prebuilt/win32
  ${COCOS2D_ROOT}/external/spidermonkey/prebuilt/win32
  ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt
  ${COCOS2D_ROOT}/external/win32-specific/icon/prebuilt
  ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt
)

elseif( MACOSX )
include_directories(
  #/usr/local/include/GLFW
  #/usr/include/GLFW
  ${COCOS2D_ROOT}/external/glfw3/include/mac
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/cocos
  #${COCOS2D_ROOT}/cocos/audio/include
  #${COCOS2D_ROOT}/cocos/platform
  #${COCOS2D_ROOT}/cocos/platform/desktop
  #${COCOS2D_ROOT}/cocos/platform/linux
  #${COCOS2D_ROOT}/cocos/editor-support
  #${COCOS2D_ROOT}/extensions
  #${COCOS2D_ROOT}/external
  #${COCOS2D_ROOT}/external/edtaa3func
  #${COCOS2D_ROOT}/external/jpeg/include/mac
  #${COCOS2D_ROOT}/external/tiff/include/mac
  #${COCOS2D_ROOT}/external/webp/include/mac
  #${COCOS2D_ROOT}/external/tinyxml2
  #${COCOS2D_ROOT}/external/unzip
  #${COCOS2D_ROOT}/external/freetype2/include/mac
  #${COCOS2D_ROOT}/external/websockets/include/mac
  #${COCOS2D_ROOT}/external/spidermonkey/include/mac
  #${COCOS2D_ROOT}/external/linux-specific/fmod/include/${ARCH_DIR}
  #${COCOS2D_ROOT}/external/xxhash
)

link_directories(
  #/usr/local/lib
  ${COCOS2D_ROOT}/external/jpeg/prebuilt/mac
  ${COCOS2D_ROOT}/external/tiff/prebuilt/mac
  ${COCOS2D_ROOT}/external/webp/prebuilt/mac
  ${COCOS2D_ROOT}/external/freetype2/prebuilt/mac
  ${COCOS2D_ROOT}/external/chipmunk/prebuilt/mac
  ${COCOS2D_ROOT}/external/png/prebuilt/mac
  ${COCOS2D_ROOT}/external/glfw3/prebuilt/mac
  ${COCOS2D_ROOT}/external/websockets/prebuilt/mac
  #${COCOS2D_ROOT}/external/spidermonkey/prebuilt/mac
  #${COCOS2D_ROOT}/external/linux-specific/fmod/prebuilt/${ARCH_DIR}
)

ADD_DEFINITIONS(-DCC_TARGET_OS_MAC)

elseif(UNIX) #assumed linux
include_directories(
  /usr/local/include/GLFW
  /usr/include/GLFW
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/cocos/audio/include
  ${COCOS2D_ROOT}/cocos/platform
  ${COCOS2D_ROOT}/cocos/platform/desktop
  ${COCOS2D_ROOT}/cocos/platform/linux
  ${COCOS2D_ROOT}/cocos/editor-support
  ${COCOS2D_ROOT}/extensions
  ${COCOS2D_ROOT}/external
  ${COCOS2D_ROOT}/external/edtaa3func
  ${COCOS2D_ROOT}/external/jpeg/include/linux
  ${COCOS2D_ROOT}/external/tiff/include/linux
  ${COCOS2D_ROOT}/external/webp/include/linux
  ${COCOS2D_ROOT}/external/tinyxml2
  ${COCOS2D_ROOT}/external/unzip
  ${COCOS2D_ROOT}/external/freetype2/include/linux
  ${COCOS2D_ROOT}/external/websockets/include/linux
  ${COCOS2D_ROOT}/external/spidermonkey/include/linux
  ${COCOS2D_ROOT}/external/linux-specific/fmod/include/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/xxhash
)

ADD_DEFINITIONS(-DLINUX)

link_directories(
  /usr/local/lib
  ${COCOS2D_ROOT}/external/jpeg/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/tiff/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/webp/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/freetype2/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/websockets/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/spidermonkey/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/linux-specific/fmod/prebuilt/${ARCH_DIR}
)
endif()

# libcocos2d
#add_subdirectory(${COCOS2D_ROOT}/cocos)
add_subdirectory(${COCOS2D_ROOT})

add_executable(${APP_NAME} ${GAME_SRC} ${GAME_RESOURCES})

target_link_libraries(${APP_NAME} cocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

SET_TARGET_PROPERTIES(${APP_NAME} PROPERTIES MACOSX_BUNDLE TRUE)

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	)
else()
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    )

endif()
