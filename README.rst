###################
gaussianNoiseVisual
###################

0: about this project
=====================

launch this application and see the visualisation of the gaussian white noise. the goal of this project is to practice working with OpenGL and statistics as both are relevant skills nowadays.

1.1: project layout
===================

- :code:`root`: The :code:`CMakeLists.txt` and :code:`.command` files are located directly in the root folder.

  - :code:`/bin`: contains the :code:`game` executable file.

  - :code:`/build`: contains the :code:`cmake` generated build files.

  - :code:`/source`: contains the :code:`main.cpp` source file and other headers.

  - :code:`/include`: contains :code:`glm`, :code:`glad` and :code:`glfw` libraries.

  - :code:`/libs`: contains the :code:`.dylib` file needed to run :code:`glfw`.

1.2: branches
=============

- this repo has two branches:

  - and major release versions to the :code:`master` branch.

  - we commitin' minor changes and non-release versions to the :code:`develop` branch.

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

	set (CMAKE_CXX_STANDARD 11)

	set (GLFW_SHARED_LIB
	  "${PROJECT_SOURCE_DIR}/libs/glfw/lib-x86_64/libglfw.3.dylib"
	)

	set (ALL_LIBS 
	  ${OpenGL}
	  ${GLFW_SHARED_LIB}
	  "-ldl"
	)

	add_executable(gaussN 
	  "source/glad.c"
	  "source/graphics/shader.cpp"
	  "source/graphics/light.cpp"
	  "source/graphics/material.cpp"
	  "source/graphics/vMesh.cpp"
	  "source/graphics/vModel.cpp"
	  "source/graphics/models/vCube.hpp"
	  "source/graphics/models/vLightSource.hpp"
	  "source/graphics/models/vTerrainGen.hpp"
	  "source/io/screen.cpp"
	  "source/io/camera.cpp"
	  "source/io/keyboard.cpp"
	  "source/io/mouse.cpp"
	  "source/math/gauss.cpp"
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