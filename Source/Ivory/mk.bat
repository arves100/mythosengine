@echo off
echo �������� Ivory ���������������������������������������������������������
cd obj
nmake /nologo %1 %2 %3 %4 %5 %6 %7 %8 %9
cd ..
if ERRORLEVEL 1 goto error
echo �������� Ivory - Done ��������������������������������������������������
goto exit
:error
echo  E r r o r 
:exit
