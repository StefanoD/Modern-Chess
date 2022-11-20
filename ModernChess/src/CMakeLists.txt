set(target ial-qt-can)

set(header_files
        )

set(source_files
        QtCAN.cpp
        ThreadedQCANBusDevice.cpp
        ThreadedQCANBusDevice.h
        )

find_package(Qt5 COMPONENTS
        Core
        SerialBus
        REQUIRED
        )

set(dependencies
        ial-interfaces
        Qt5::Core
        Qt5::SerialBus)

INSTALL_DEFAULT_LIB(IAL)