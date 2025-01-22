@echo on

if not defined HOST_TAG set HOST_TAG=windows-x86_64
if not defined ANDROID_HOME set ANDROID_HOME=D:/NVPACK/Sdk
if not defined NDKROOT set NDKROOT=%ANDROID_HOME%/ndk/21.1.6352462
if not defined NDK_MAKE set NDK_MAKE=%NDKROOT%/prebuilt/windows-x86_64/bin/make.exe
if not defined NDK_TOOLCHAIN set NDK_TOOLCHAIN=%NDKROOT%/build/cmake/android.toolchain.cmake
if not defined JAVA_HOME set JAVA_HOME=D:/NVPACK/jdk_11.0.21/corretto-11.0.21

if not defined VC set VC="D:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvars64.bat"
if not defined UEENGINE_DIR set UEENGINE_DIR="D:/Program Files/Epic Games/UE_4.27"

if not defined HAS_CALL_VC (
    call %VC%
    set HAS_CALL_VC=true
)

rmdir /S /Q build
mkdir build

cd build/

cmake ../ ^
-G "NMake Makefiles" ^
-DCMAKE_BUILD_TYPE="Release" ^
-Dprotobuf_BUILD_SHARED_LIBS=ON ^
-Dprotobuf_BUILD_TESTS=OFF ^
-Dprotobuf_BUILD_CONFORMANCE=OFF ^
-Dprotobuf_BUILD_EXAMPLES=OFF ^
-Dprotobuf_BUILD_PROTOC_BINARIES=ON ^
-Dprotobuf_MSVC_STATIC_RUNTIME=ON -DMSVC=ON

nmake -nologo install