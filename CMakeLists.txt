cmake_minimum_required(VERSION 3.8)

project( a8util )

file(GLOB a8util-obj2asm_src
     "a8util-obj2asm.c"
)

add_executable( a8util-obj2asm ${a8util-obj2asm_src} )


file(GLOB a8util-gimpraw2mic_src
     "a8util-gimpraw2mic.c"
)

add_executable( a8util-gimpraw2mic ${a8util-gimpraw2mic_src} )



