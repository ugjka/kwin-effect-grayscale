#######################################
# Effect

#######################################
# Config
add_subdirectory( kcm )
find_package (Qt5 REQUIRED COMPONENTS
    Core
)

find_package (KF5 REQUIRED COMPONENTS
    Service
    WindowSystem
    GlobalAccel
    I18n
)

find_package (KWinEffects REQUIRED)

set(kwin_effect_grayscale_SRCS plugin.cpp GrayscaleEffect.cpp)
qt5_add_resources(kwin_effect_grayscale_SRCS shaders.qrc)
add_library(kwin_effect_grayscale SHARED ${kwin_effect_grayscale_SRCS})

target_link_libraries(kwin_effect_grayscale
PUBLIC
    Qt5::Core
    KF5::WindowSystem
    KF5::Service
    KF5::GlobalAccel
    KF5::I18n
    KWinEffects::KWinEffects
)

kcoreaddons_desktop_to_json(kwin_effect_grayscale grayscale.desktop SERVICE_TYPES kwineffect.desktop)

install(
    TARGETS
        kwin_effect_grayscale
    DESTINATION
        ${PLUGIN_INSTALL_DIR}/kwin/effects/plugins/
)
