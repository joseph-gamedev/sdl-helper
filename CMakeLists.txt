cmake_minimum_required(VERSION 3.16)
project(sdl-helper)

# Add SDL submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sdl EXCLUDE_FROM_ALL)

# Add EnTT submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/external/entt)

# Add GLM submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm)

# Add SDL_ttf submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sdl_ttf)

# Add JSON library
add_subdirectory(${CMAKE_SOURCE_DIR}/external/json)  

# Add PhysFS library
add_subdirectory(${CMAKE_SOURCE_DIR}/external/physfs)

# Add Box2D submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/external/box2d)

# Add your project's source files
file(GLOB SOURCES "src/*.h" "src/*.cpp")

# Create a library target for your project
add_library(sdl_helper STATIC ${SOURCES})

# Link against SDL and EnTT libraries
target_link_libraries(sdl_helper PUBLIC SDL3::SDL3 SDL_ttf EnTT glm json physfs-static)

# Set include directories
target_include_directories(sdl_helper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/sdl/include  		# Include SDL headers
    ${CMAKE_SOURCE_DIR}/external/entt/src     		# Include EnTT headers
	${CMAKE_SOURCE_DIR}/external/glm          		# Include GLM headers
	${CMAKE_SOURCE_DIR}/external/sdl_ttf/include    # Include SDL_ttf headers
	${CMAKE_SOURCE_DIR}/external/json/include    	# Include JSON headers
    ${CMAKE_SOURCE_DIR}/external/physfs/src     	# Include PhysFS headers
	${CMAKE_SOURCE_DIR}/external/box2d/include    	# Include Box2D headers
)
