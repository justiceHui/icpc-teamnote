set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "-DLOCAL -lm -g -Wl,--stack,268435456")
add_compile_options(-DLOCAL -lm -g -Wl,--stack,268435456) # -O3 -mavx -mavx2 -mfma