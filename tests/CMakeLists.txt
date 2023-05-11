

set(TEST_SOURCES tests_vecteur.cpp ${PROJECT_SOURCE_DIR}/Vecteur.h)

add_executable(
        tests_vecteur
        ${TEST_SOURCES}
)

target_include_directories(tests_vecteur PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        tests_vecteur
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(tests_vecteur)