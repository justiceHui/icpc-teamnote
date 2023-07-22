set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-DLOCAL -lm -g -Wl,--stack,268435456")
add_compile_options(-Wall -Wextra -Winvalid-pch -Wfloat-equal -Wno-sign-compare -Wno-misleading-indentation -Wno-parentheses)
# add_compile_options(-O3 -mavx -mavx2 -mfma)