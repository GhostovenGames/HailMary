set(manager_SOURCES GameManager.cpp GameManager.hpp GraphicsManager.cpp GraphicsManager.hpp
        SaveManager.cpp SaveManager.hpp TimeManager.cpp TimeManager.hpp Level.cpp Level.hpp)
add_library(managers ${manager_SOURCES})