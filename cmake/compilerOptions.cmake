# === Set the build type to release if not otherwise specified.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE release)
endif()

set(BUILD_SHARED_LIBS true)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -DQT_NO_DEBUG -DQT_NO_DEBUG_OUTPUT")

    add_definitions(-Wall -Wextra -pedantic -std=c++0x)
    add_definitions(-Wcast-align)
    add_definitions(-Wcast-qual)
    add_definitions(-Wdisabled-optimization)
    add_definitions(-Wstrict-aliasing)
    add_definitions(-Wunknown-pragmas)
    #add_definitions(-Wconversion)
    #add_definitions(-Wno-deprecated -Wno-unknown-pragmas)
    #add_definitions(-Wfloat-equal)

else()
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -xHost -ipo -no-prec-div -DNDEBUG -DQT_NO_DEBUG -DQT_NO_DEBUG_OUTPUT")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O2 -xHost -funroll-loops -ipo -no-prec-div -DNDEBUG -DQT_NO_DEBUG -DQT_NO_DEBUG_OUTPUT")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -DQT_NO_DEBUG -DQT_NO_DEBUG_OUTPUT")
    #add_definitions(-vec-report3)

    # Enable warning flags.
    # --------------------
    add_definitions(-Wall -Wcheck)
    #add_definitions(-Weffc++)

    # Suppress remarks and warnings.
    # -----------------------------
    add_definitions(-wd1418) # External function with no prior declaration.
    add_definitions(-wd1419) # External declaration in primary source file.
    add_definitions(-wd383)  # Value copied to temporary, reference to temporary used.
    add_definitions(-wd444)  # Destructor for base class not virtual.
    add_definitions(-wd981)  # Operands are evaluated in unspecified order.
    add_definitions(-wd177)  # Variable declared by never referenced.

    # Promote remarks to warnings.
    # ----------------------------
    add_definitions(-ww111)
    add_definitions(-ww1572)

endif()

