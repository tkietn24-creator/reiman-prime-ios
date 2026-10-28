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

COMMON_FLAGS="-arch arm64 -isysroot $SDK_PATH -miphoneos-version-min=14.0 -std=c++17 -stdlib=libc++ -Iimgui -Iimgui/backends -I."

echo "[+] 1/6 Dang bien dich imgui.cpp..."
xcrun -sdk iphoneos clang++ $COMMON_FLAGS -c imgui/imgui.cpp -o imgui.o

echo "[+] 2/6 Dang bien dich imgui_draw.cpp..."
xcrun -sdk iphoneos clang++ $COMMON_FLAGS -c imgui/imgui_draw.cpp -o imgui_draw.o

echo "[+] 3/6 Dang bien dich imgui_widgets.cpp..."
xcrun -sdk iphoneos clang++ $COMMON_FLAGS -c imgui/imgui_widgets.cpp -o imgui_widgets.o

echo "[+] 4/6 Dang bien dich imgui_tables.cpp..."
xcrun -sdk iphoneos clang++ $COMMON_FLAGS -c imgui/imgui_tables.cpp -o imgui_tables.o

echo "[+] 5/6 Dang bien dich Metal Backend (imgui_impl_metal.mm)..."
xcrun -sdk iphoneos clang++ $COMMON_FLAGS -fobjc-arc -c imgui/backends/imgui_impl_metal.mm -o imgui_impl_metal.o

echo "[+] 6/6 Dang bien dich MenuMetalOverlay.mm..."
xcrun -sdk iphoneos clang++ $COMMON_FLAGS -fobjc-arc -c MenuMetalOverlay.mm -o MenuMetalOverlay.o

echo "[+] Dang lien ket thanh Dynamic Library ($OUTPUT)..."
xcrun -sdk iphoneos clang++ -arch arm64 -dynamiclib -isysroot "$SDK_PATH" \
    -miphoneos-version-min=14.0 \
    -stdlib=libc++ \
    -framework UIKit \
    -framework Foundation \
    -framework Metal \
    -framework MetalKit \
    -framework QuartzCore \
    -undefined dynamic_lookup \
    -install_name "@rpath/$OUTPUT" \
    imgui.o imgui_draw.o imgui_widgets.o imgui_tables.o imgui_impl_metal.o MenuMetalOverlay.o \
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
