@echo off
title DAY CODE REIMAN PRIME LEN GITHUB CHO DAI CA TKIETN
color 0C
echo ==============================================================================
echo              HE THONG TU DONG DAY CODE LEN GITHUB CHO DAI CA
echo              Repository: https://github.com/tkietn24-creator/reiman-prime-ios.git
echo ==============================================================================
echo.
echo [+] Dang dong goi toan bo ma nguon va he thong Actions...
git branch -M main
git remote remove origin 2>nul
git remote add origin https://github.com/tkietn24-creator/reiman-prime-ios.git

echo.
echo [+] Dang day ma nguon len GitHub...
echo [!] Neu trinh duyet bat len hop thoai 'Sign in with your browser', Dai ca chi can bam dang nhap nhe!
echo.
git push -u origin main --force

echo.
echo ==============================================================================
echo [V] DA DAY THANH CONG TOAN BO REPO CHO DAI CA!
echo.
echo     Bay gio Dai ca chi can vao link nay de tai file .dylib ve may:
echo     >> https://github.com/tkietn24-creator/reiman-prime-ios/actions
echo ==============================================================================
echo.
pause
