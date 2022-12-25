cmake_minimum_required(VERSION 3.0.0)
project(Wallet VERSION 0.1.0)

#
# Wallet Library of all logic
#
add_library( Wallet STATIC
    ${PROJECT_SOURCE_DIR}/source/keys/SeedPhraseGenerator.cpp
    ${PROJECT_SOURCE_DIR}/source/keys/Random.cpp 
)
target_include_directories(Wallet PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Wallet PRIVATE ${PROJECT_SOURCE_DIR}/source)

#
# Wallet executable runs as a web service
#
add_executable(WalletService 
    main.cpp    
    )
target_link_libraries(WalletService Wallet)
target_include_directories(WalletService PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(WalletService PRIVATE ${PROJECT_SOURCE_DIR}/source)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#
# Google test. Bases on : http://google.github.io/googletest/quickstart-cmake.html
# 
include(CTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(
  WalletTest
  test/SeedPhraseTest.cpp
)
target_link_libraries(WalletTest GTest::gtest_main Wallet)

target_include_directories(WalletTest PRIVATE ${PROJECT_SOURCE_DIR}/source)
include(GoogleTest)
gtest_discover_tests(WalletTest)