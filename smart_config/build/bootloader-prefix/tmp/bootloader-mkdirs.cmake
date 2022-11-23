# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v4.4.2/components/bootloader/subproject"
  "C:/esp-project/smart_config/build/bootloader"
  "C:/esp-project/smart_config/build/bootloader-prefix"
  "C:/esp-project/smart_config/build/bootloader-prefix/tmp"
  "C:/esp-project/smart_config/build/bootloader-prefix/src/bootloader-stamp"
  "C:/esp-project/smart_config/build/bootloader-prefix/src"
  "C:/esp-project/smart_config/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/esp-project/smart_config/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()