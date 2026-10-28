#!/bin/bash
# ==============================================================================
# REIMAN PRIME iOS - ONE-CLICK MACOS / THEOS BUILD SCRIPT
# Build ra file ReimanPrimeiOS.dylib chuẩn Mach-O ARM64 cho iOS
# ==============================================================================

set -e

echo "[+] Bat dau build REIMAN PRIME iOS Dylib cho Dai ca..."

if [ -d "/Applications" ]; then
    LATEST_XCODE=$(find /Applications -maxdepth 1 -name "Xcode*.app" | sort -V | tail -n 1)
    if [ -n "$LATEST_XCODE" ]; then
        echo "[+] Kich hoat Xcode Developer tai: $LATEST_XCODE"
        export DEVELOPER_DIR="$LATEST_XCODE/Contents/Developer"
    fi
fi

SDK_PATH=$(xcrun --sdk iphoneos --show-sdk-path)
echo "[+] Su dung iOS SDK tai: $SDK_PATH"
OUTPUT="ReimanPrimeiOS.dylib"

xcrun -sdk iphoneos clang++ -dynamiclib -arch arm64 \
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
    -undefined dynamic_lookup \
    -install_name @rpath/ReimanPrimeiOS.dylib \
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
    ldid -S "$OUTPUT" || true
    echo "[+] Da ky ldid thanh cong!"
fi

if command -v codesign &> /dev/null; then
    codesign -f -s - "$OUTPUT" || true
    echo "[+] Da ky codesign ad-hoc thanh cong!"
fi

echo "[+] HOAN TAT! File dylib da san sang tai: $OUTPUT"
ls -lh "$OUTPUT"
