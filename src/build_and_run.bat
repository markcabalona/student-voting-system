@echo off
cls
echo Compiling...
g++ main.cpp models/*.cpp providers/*.cpp screens/*.cpp utils/*.cpp -o app.exe
echo PRESS CTRL + C to EXIT
timeout 5
:wait
if exist app.exe (echo App is booting. Please Wait && app) else (timeout 5 && goto wait)
del app.exe