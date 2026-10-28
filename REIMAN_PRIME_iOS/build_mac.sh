#!/bin/bash
# ==============================================================================
# REIMAN PRIME iOS - ONE-CLICK MACOS / THEOS BUILD SCRIPT
# Build ra file ReimanPrimeiOS.dylib chuẩn Mach-O ARM64 cho iOS
# ==============================================================================

set -e

echo "[+] Bat dau build REIMAN PRIME iOS Dylib cho Dai ca..."

SDK_PATH=$(xcrun --sdk iphoneos --show-sdk-path)
OUTPUT="ReimanPrimeiOS.dylib"

xcrun -sdk iphoneos clang++ -arch arm64 -shared \
    -isysroot "$SDK_PATH" \
    -miphoneos-version-min=14.0 \
    -fobjc-arc \
    -std=c++17 \
    -stdlib=libc++ \
    -framework UIKit \
    -framework Foundation \
    -framework Metal \
    -framework MetalKit \
    -framework QuartzCore \
    -Iimgui \
    -Iimgui/backends \
    MenuMetalOverlay.mm \
    imgui/imgui.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_widgets.cpp \
    imgui/imgui_tables.cpp \
    imgui/backends/imgui_impl_metal.mm \
    -o "$OUTPUT"

echo "[+] Ky ma gia lap (Ad-hoc Code Sign voi ldid) de bypass iOS Security..."
if command -v ldid &> /dev/null; then
    ldid -S "$OUTPUT"
    echo "[+] Da ky ldid thanh cong!"
else
    codesign -f -s - "$OUTPUT"
    echo "[+] Da ky codesign ad-hoc thanh cong!"
fi

echo "[+] HOAN TAT! File dylib da san sang tai: $OUTPUT"
ls -lh "$OUTPUT"
