cmake_minimum_required(VERSION 3.15)

project(
    geo_external_operator
    VERSION 1.1.0
    LANGUAGES C
)

file(
    GLOB GEO_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(
    geo_public
    SHARED
    ${GEO_SOURCES}
)

target_include_directories(
    geo_public
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(UNIX)
    target_link_libraries(
        geo_public
        PRIVATE
        m
    )
endif()

set_target_properties(
    geo_public
    PROPERTIES
    OUTPUT_NAME "geo_public"
)

install(
    TARGETS geo_public
    LIBRARY DESTINATION geo_external_operator
    RUNTIME DESTINATION geo_external_operator
)

install(
    FILES
        include/geo_public.h
        include/geo_engine.h
    DESTINATION
        geo_external_operator/include
)
