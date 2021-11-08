cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17 -flto -fno-rtti -Wno-inline-new-delete -fno-exceptions -Wno-macro-redefined -Wno-return-type -nostartfiles  ") #-nostdlib ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-entry,--allow-undefined,--export=Ctor,--export=Dtor,--export=Method_0,--export=Method_1,--export=Method_2,--lto-O3") #",--strip-all")

add_executable(contract contract.cpp)
add_executable(app app.cpp)
target_link_libraries(contract PRIVATE Beam::shader-lib)

generate_sid(contract)
add_dependencies(app contract_header)
target_link_libraries(app 
	PRIVATE 
		Beam::shader-lib)

