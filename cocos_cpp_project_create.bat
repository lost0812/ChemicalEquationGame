<span style="font-size:18px;">@echo off  
set /p projectName=��������Ŀ���ƣ�  
if "%projectName%"=="" goto inputError  
set /p packageName=���������ʾ����  
if "%packageName%"=="" goto inputError  
set /p workspacePath=�����빤���ռ��ַ��  
if "%workspacePath=%"=="" goto inputError  
cocos new %projectName% -p %packageName% -l cpp -d %workspacePath=%
pause  
exit  
:inputError  
@echo ��Ŀ���ƻ��߰���ʾ�����߹����ռ��ַ����Ϊ�գ�  
pause</span>  