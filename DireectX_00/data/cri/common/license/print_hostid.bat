@echo off

rem ���C�Z���X�L�[�t�@�C���\���p�z�X�gID�̕\��

lmhostid | %SystemRoot%\system32\find "FLEXnet" >> %TMP%\temp_ipconfig.txt
%SystemRoot%\system32\notepad %TMP%\temp_ipconfig.txt
del %TMP%\temp_ipconfig.txt
