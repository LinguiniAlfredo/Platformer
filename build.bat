@echo off

mkdir .\build
pushd .\build

cl /EHsc /JMC /GS /W3 /ZI /Gd /sdl /MDd /FC /Od /fp:precise /WX- /Zc:wchar_t ^
    /Zc:forScope /RTC1 ^
            ..\Platformer\main.cpp ^
            ^
            ..\Platformer\HUD.cpp ^
            ..\Platformer\Scene.cpp ^
            ..\Platformer\Entities\*.cpp ^
            ..\Platformer\Components\*.cpp ^
            ..\Platformer\Editor\*.cpp ^
            ..\Platformer\Utils\*.cpp ^
            ^
            /I C:\vclib\SDL2-2.30.7\include ^
            /I C:\vclib\SDL2_image-2.8.2\include ^
            /I C:\vclib\SDL2_ttf-2.22.0\include ^
            /I ..\Platformer ^
            /I ..\Platformer\Entities ^
            /I ..\Platformer\Components ^
            /I ..\Platformer\Editor ^
            /I ..\Platformer\Utils ^
            ^
            /link ^
                /LIBPATH:C:\vclib\SDL2-2.30.7\lib\x64 ^
                /LIBPATH:C:\vclib\SDL2_image-2.8.2\lib\x64 ^
                /LIBPATH:C:\vclib\SDL2_ttf-2.22.0\lib\x64\ ^
                    SDL2.lib ^
                    SDL2main.lib ^
                    SDL2_image.lib ^
                    SDL2_ttf.lib ^
                    shell32.lib ^
                    kernel32.lib ^
                    user32.lib ^
                    gdi32.lib ^
                    winspool.lib ^
                    comdlg32.lib ^
                    advapi32.lib ^
                    ole32.lib ^
                    oleaut32.lib ^
                    uuid.lib ^
                    odbc32.lib ^
                    odbccp32.lib ^
            /DYNAMICBASE ^
            /SUBSYSTEM:CONSOLE ^
            /out:..\Platformer\main.exe
popd
