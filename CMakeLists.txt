# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(U4C4O12T_Interrupcoes C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(U4C4O12T_Interrupcoes src/main.c )

pico_set_program_name(U4C4O12T_Interrupcoes "Interrupcoes")
pico_set_program_version(U4C4O12T_Interrupcoes "0.1")

# Define o diretório de saída apenas para os arquivos de cabeçalho
set(PIO_HEADER_OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)

# Evita que headers gerados sejam duplicados em outros diretórios
set(PICO_NO_GENERATED_HEADERS_PATHS ON)

# Generate PIO header
# Gera o arquivo PIO na pasta especificada apenas para headers
pico_generate_pio_header(U4C4O12T_Interrupcoes 
    ${CMAKE_CURRENT_LIST_DIR}/InterfacePio.pio 
    OUTPUT_DIR ${PIO_HEADER_OUTPUT_DIR}
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(U4C4O12T_Interrupcoes 1)
pico_enable_stdio_usb(U4C4O12T_Interrupcoes 1)

# Add the standard library to the build
target_link_libraries(U4C4O12T_Interrupcoes
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(U4C4O12T_Interrupcoes PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Add any user requested libraries
target_link_libraries(U4C4O12T_Interrupcoes 
        hardware_pio
        matriz_5x5lib
)

# Add the external library
add_library(matriz_5x5lib STATIC
            src/funcoes.c
)

target_include_directories(matriz_5x5lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Add stdlib ao Matriz_cntrl.c
target_link_libraries(matriz_5x5lib
       pico_stdlib 
       hardware_pio    
)

pico_add_extra_outputs(U4C4O12T_Interrupcoes)

