# CMakeList.txt: CMakeProject1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
set(OP_FILES
	"CMakeProject1.cpp" 
	"CMakeProject1.h"
	"./imageProc/imageloc.cpp"
	"./imageProc/imageproc.cpp"
	"./core/helpfunc.cpp"
	"./core/opEnv.cpp"
	"op.cpp"
)

set(SRC_FILES
	"CMakeProject1.cpp" 
	"CMakeProject1.h"
)


ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_DEFINITIONS(-D WIN32)
ADD_DEFINITIONS(-D _WINDOWS)
ADD_DEFINITIONS(-D _USRDLL)
ADD_DEFINITIONS(-D _CRT_NON_CONFORMING_SWPRINTFS)
ADD_DEFINITIONS(-D _CRT_SECURE_NO_WARNINGS)
ADD_DEFINITIONS(-D _SILENCE_CXX17_ADAPTOR_TYPEDEFS_DEPRECATION_WARNING)
ADD_DEFINITIONS(-D _WINDLL)
ADD_DEFINITIONS(-D _UNICODE)
ADD_DEFINITIONS(-D UNICODE)
ADD_DEFINITIONS(-D OP_EXPORTS)
 

add_library(libop ${OP_FILES})

add_executable (CMakeProject1 ${SRC_FILES})

target_link_libraries(CMakeProject1 libop)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

INSTALL( TARGETS libop DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )

install(FILES op.h DESTINATION ${CMAKE_INSTALL_PREFIX})
