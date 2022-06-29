clear
close all
clc

p = 0;
% camera setting(Calibration)

% Get coordinates


s=serialport('COM4',9600);
pause(2);
% Serial Communication to Arduino
for i=1:9

    switch p
    case 0
        DD = "60;";
        p = 1;
    case 1
        DD = "80;";
        p = 2;
    case 2
        DD = "100;";
        p = 0;   
    end

    writeline(s,DD);
    pause(0.5);
    flush(s); %メモリリセット
end
clear s