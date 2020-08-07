cmake_minimum_required(VERSION 3.5.1)

project(bicoloreTree VERSION 0.0.1 LANGUAGES C)

add_library(bicoloreTree SHARED bicoloreTree.c bicoloreTree.h )
add_library(bicoloreTreeStatic STATIC bicoloreTree.c bicoloreTree.h)
set_target_properties(bicoloreTree PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)
set_target_properties(bicoloreTreeStatic PROPERTIES
	OUTPUT_NAME bicoloreTree
)

install(
	TARGETS bicoloreTree bicoloreTreeStatic
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)

install(
	FILES bicoloreTree.h
	DESTINATION include
)

add_executable(test-bicolore bicoloreTree.c bicoloreTree.h)
add_dependencies(test-bicolore bicoloreTree)
target_link_libraries(test-bicolore bicoloreTree)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES "~$;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)

