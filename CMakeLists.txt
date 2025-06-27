cmake_minimum_required(VERSION 3.15)
project(main)

# Defina o diretório de fontes e includes
set(SRC_DIR src)
set(INC_DIR include)

# Pegue todos os .c em src/
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Adiciona o executável
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Inclui diretórios
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

# Copiar pasta resources para o diretório de build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# Configura Raylib conforme o sistema operacional
if(APPLE)
    message(STATUS "Compilando para macOS")
    # Supondo Raylib via Homebrew
    set(RAYLIB_PATH /opt/homebrew/opt/raylib)
    target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_PATH}/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_PATH}/lib)

   target_link_libraries(${PROJECT_NAME}
        raylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreAudio"
        "-framework CoreVideo"
    )
        # Copiar pasta resources para o diretório do executável
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )

elseif(WIN32)
    message(STATUS "Compilando para Windows")
    # Suponha que Raylib esteja instalado via MSYS2 em um path padrão
    # Ajuste conforme seu sistema
    set(RAYLIB_PATH "C:/raylib") # ou algo como C:/msys64/mingw64
    target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_PATH}/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_PATH}/lib)
    target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)

elseif(UNIX)
    message(STATUS "Compilando para Linux")

    # Esta configuração é mais genérica e assume que a Raylib foi instalada no sistema
    # (por exemplo, usando 'sudo make install' no diretório de código-fonte da Raylib).
    # O compilador encontrará os ficheiros de cabeçalho e a biblioteca nos caminhos padrão.

    # Apenas precisamos de dizer ao linker para usar a biblioteca 'raylib' e as suas dependências.
    target_link_libraries(${PROJECT_NAME}
        raylib
        m
        pthread
        dl
        GL
        X11
    )
endif()