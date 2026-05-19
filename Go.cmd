if .%USERDOMAIN% == .DESKTOP-97PMNQT goto :savasPC

Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
mingw32-make.exe

:toliau

echo Vilnius Klaipeda >> duom.txt
echo Vilnius Kaunas 100 >> duom.txt
echo Vilnius Panevezys 130 >> duom.txt
echo Kaunas Klaipeda 200 >> duom.txt
echo Kaunas Siauliai 120 >> duom.txt
echo Panevezys Siauliai 80 >> duom.txt
echo Siauliai Klaipeda 150 >> duom.txt
echo Panevezys Utena 95 >> duom.txt
echo Utena Klaipeda 310 >> duom.txt

program.exe duom.txt > result1.txt

echo Vilnius Klaipeda >> graph.cfg
echo Vilnius Kaunas 100 >> graph.cfg
echo Kaunas Klaipeda 200 >> graph.cfg
echo Vilnius Panevezys 130 >> graph.cfg
echo Panevezys Siauliai 80 >> graph.cfg
echo Siauliai Klaipeda 150 >> graph.cfg
echo Kaunas Siauliai 120 >> graph.cfg

program.exe graph.cfg > result2.txt