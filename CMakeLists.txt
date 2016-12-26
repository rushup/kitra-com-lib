set(kitra_com_lib_VERSION 1)
set(kitra_com_lib_source_files
    kitra_input.c
    kitra_input.h
    kitra_output.c
    kitra_output.h
    kitra_packet_generator.c
    kitra_packet_generator.h
    kitra_small_utility.c
    kitra_small_utility.h
    )
add_library(kitra_com_lib ${kitra_com_lib_source_files})

target_link_libraries(kitra_com_lib)
