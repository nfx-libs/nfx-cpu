#==============================================================================
# nfx-cpu - CMake Sources
#==============================================================================

#----------------------------------------------
# Conditional headers and sources
#----------------------------------------------

set(PUBLIC_HEADERS)

list(APPEND PUBLIC_HEADERS
	${NFX_CPU_INCLUDE_DIR}/nfx/cpu/CoreTopology.h
	${NFX_CPU_INCLUDE_DIR}/nfx/cpu/FeatureDetection.h
	${NFX_CPU_INCLUDE_DIR}/nfx/cpu/Identification.h

	${NFX_CPU_INCLUDE_DIR}/nfx/detail/cpu/CoreTopology.inl
	${NFX_CPU_INCLUDE_DIR}/nfx/detail/cpu/FeatureDetection.inl
	${NFX_CPU_INCLUDE_DIR}/nfx/detail/cpu/Identification.inl

	${NFX_CPU_INCLUDE_DIR}/nfx/CPU.h
)

#----------------------------------------------
# Library definition
#----------------------------------------------

# --- Create header-only interface library ---
add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

#----------------------------------------------
# Target properties
#----------------------------------------------

# --- Configure interface library ---
target_include_directories(${PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${NFX_CPU_INCLUDE_DIR}>
		$<INSTALL_INTERFACE:include>
)

# Set interface compile features for C++20
target_compile_features(${PROJECT_NAME}
	INTERFACE
		cxx_std_20
)
