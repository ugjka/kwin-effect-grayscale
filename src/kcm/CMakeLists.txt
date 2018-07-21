#######################################
# Effect

#######################################
# Config
find_package (Qt5 REQUIRED COMPONENTS
    Core
    DBus
)

find_package (KF5 REQUIRED COMPONENTS
    ConfigWidgets
    GlobalAccel
    I18n
    Service
    XmlGui
)

set(kwin_grayscale_config_SRCS grayscale_config.cpp)
qt5_add_dbus_interface(kwin_grayscale_config_SRCS dbus.xml kwineffects_interface)

add_library(kwin_grayscale_config MODULE ${kwin_grayscale_config_SRCS})

target_link_libraries(kwin_grayscale_config
    Qt5::Core
    Qt5::DBus
    KF5::ConfigWidgets
    KF5::GlobalAccel
    KF5::I18n
    KF5::Service
    KF5::XmlGui
)

kcoreaddons_desktop_to_json(kwin_grayscale_config grayscale_config.desktop SERVICE_TYPES kcmodule.desktop)

install(
    TARGETS
        kwin_grayscale_config
    DESTINATION
        ${PLUGIN_INSTALL_DIR}/kwin/effects/configs
)
