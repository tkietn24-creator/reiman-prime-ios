@echo off
title DAY CODE REIMAN PRIME LEN GITHUB CHO DAI CA
color 0C
echo ==============================================================================
echo              HE THONG DAY CODE LEN GITHUB CHO DAI CA TKIETN
echo ==============================================================================
echo.
set /p REPO_URL=">> Nhap link GitHub Repository cua Dai ca (vi du: https://github.com/user/reiman-ios.git): "

if "%REPO_URL%"=="" (
    echo [!] Dai ca chua nhap link! Vui long chay lai va nhap link repo.
    pause
    exit /b
)

echo.
echo [+] Dang khoi tao Git va dong goi ma nguon...
git init
git add .
git commit -m "REIMAN PRIME iOS - 675x545 Menu with Floating Pill Button"
git branch -M main

echo [+] Dang ket noi den Repository cua Dai ca...
git remote remove origin 2>nul
git remote add origin %REPO_URL%

echo [+] Dang day ma nguon len GitHub...
git push -u origin main --force

echo.
echo ==============================================================================
echo [V] DA DAY THANH CONG LEN GITHUB CHO DAI CA!
echo     Bay gio Dai ca chi can vao tab 'Actions' tren GitHub repo,
echo     cho 35 giay la tai file ReimanPrimeiOS.dylib ve chien luon!
echo ==============================================================================
echo.
pause
