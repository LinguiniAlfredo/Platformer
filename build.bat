@echo off

mkdir .\build
pushd .\build
cl /EHsc ..\CPP_Engine\main.cpp ^
            ^
            ..\CPP_Engine\HUD.cpp ^
            ..\CPP_Engine\Scene.cpp ^
            ..\CPP_Engine\Entities\*.cpp ^
            ..\CPP_Engine\Components\*.cpp ^
            ..\CPP_Engine\Editor\*.cpp ^
            ..\CPP_Engine\Utils\*.cpp ^
            ^
            /I C:\vclib\SDL2-2.30.7\include ^
            /I C:\vclib\SDL2_image-2.8.2\include ^
            /I C:\vclib\SDL2_ttf-2.22.0\include ^
            /I ..\CPP_Engine ^
            /I ..\CPP_Engine\Entities ^
            /I ..\CPP_Engine\Components ^
            /I ..\CPP_Engine\Editor ^
            /I ..\CPP_Engine\Utils ^
            ^
            /link ^
                /LIBPATH:C:\vclib\SDL2-2.30.7\lib\x64 ^
                /LIBPATH:C:\vclib\SDL2_image-2.8.2\lib\x64 ^
                /LIBPATH:C:\vclib\SDL2_ttf-2.22.0\lib\x64\ ^
                    shell32.lib ^
                    SDL2.lib ^
                    SDL2main.lib ^
                    SDL2_image.lib ^
                    SDL2_ttf.lib ^
            /SUBSYSTEM:CONSOLE ^
            /out:..\CPP_Engine\main.exe
popd
