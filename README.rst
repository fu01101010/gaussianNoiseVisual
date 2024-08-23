##########################
gaussianNoiseVisualisation
##########################

0: about this project
=====================

launch this application and see the visualisation of the gaussian white noise. the goal of this project is to practice working with OpenGL and statistics as both are relevant skills nowadays.

1: project layout
=================

- :code:`root`: The :code:`CMakeLists.txt` and :code:`.command` files are located directly in the root folder.

  - :code:`/bin`: contains the :code:`game` executable file.

  - :code:`/build`: contains the :code:`cmake` generated build files.

  - :code:`/source`: contains the :code:`main.cpp` source file and other headers.

2: cmake
========

.. code-block::

	cmake_minimum_required(VERSION 3.28)
	project("gaussianNoiseVisual")

	find_package(OpenGL REQUIRED)

	include_directories(
		# library headers
		"./include/"
    	)

	set( GLFW_SHARED_LIB
    		"${PROJECT_SOURCE_DIR}/libs/glfw/lib-x86_64/libglfw.3.dylib"
	)

	set ( ALL_LIBS 
    		${OpenGL}
    		${GLFW_SHARED_LIB}
    		"-ldl"
	)

	add_executable(gaussN 
    		"source/glad.c"
    		"source/main.cpp"
    	)

	target_link_libraries(gaussN ${ALL_LIBS})
	install(TARGETS gaussN DESTINATION "${PROJECT_SOURCE_DIR}/bin/")

3: build
========

- :code:`gaussN.command` contains the following:

  - :code:`~/projectRoot rm -rf build/` and :code:`~/projectRoot mkdir build` basically clears the build directory.

  - :code:`cd build`: enters the directory.

  - :code:`cmake ..`: builds the :code:`CMakeLists.txt` located in the parent directory.

  - :code:`make install`: creates the :code:`gaussN` executable and puts it in the :code:`~/projectRoot/bin` directory.

  - :code:`cd ../bin`: enters the /bin directory.

  - :code:`./gaussN`: launches the executable.