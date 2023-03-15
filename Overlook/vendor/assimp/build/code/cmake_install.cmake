# Install script for directory: D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.5-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/lib/Debug/assimp-vc143-mtd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/lib/Release/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/lib/MinSizeRel/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/lib/RelWithDebInfo/assimp-vc143-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.5" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/bin/Debug/assimp-vc143-mtd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/bin/Release/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/bin/MinSizeRel/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/bin/RelWithDebInfo/assimp-vc143-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/anim.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/aabb.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ai_assert.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/camera.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/color4.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/color4.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/code/../include/assimp/config.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ColladaMetaData.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/commonMetaData.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/defs.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/cfileio.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/light.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/material.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/material.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/matrix3x3.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/matrix3x3.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/matrix4x4.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/matrix4x4.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/mesh.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ObjMaterial.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/pbrmaterial.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/GltfMaterial.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/postprocess.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/quaternion.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/quaternion.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/scene.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/metadata.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/texture.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/types.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/vector2.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/vector2.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/vector3.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/vector3.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/version.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/cimport.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/AssertHandler.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/importerdesc.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Importer.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/DefaultLogger.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ProgressHandler.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/IOStream.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/IOSystem.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Logger.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/LogStream.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/NullLogger.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/cexport.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Exporter.hpp"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/DefaultIOStream.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/DefaultIOSystem.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SceneCombiner.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/fast_atof.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/qnan.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/BaseImporter.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Hash.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ParsingUtils.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/StreamReader.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/StreamWriter.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/StringComparison.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/StringUtils.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SGSpatialSort.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/GenericProperty.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SpatialSort.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SmallVector.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SmoothingGroups.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/SmoothingGroups.inl"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/StandardShapes.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/RemoveComments.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Subdivision.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Vertex.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/LineSplitter.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/TinyFormatter.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Profiler.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/LogAux.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Bitmap.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/XMLTools.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/IOStreamBuffer.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/CreateAnimMesh.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/XmlParser.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/BlobIOSystem.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/MathFunctions.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Exceptional.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/ByteSwapper.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Compiler/poppack1.h"
    "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/code/Debug/assimp-vc143-mtd.pdb")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Study/VS2022/Overlook/Overlook/vendor/assimp/build/code/RelWithDebInfo/assimp-vc143-mt.pdb")
  endif()
endif()

