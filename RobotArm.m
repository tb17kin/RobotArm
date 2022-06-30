clear
close all
clc

% camera setting(Calibration)

% Get coordinates

% Serial Communication to Arduino
s=serialport('COM4',9600);
pause(10);
p = 0;
DD_before = "100;";
for i=1:10

    % DD = PIDControl(Ball, r);
    switch p
    case 0
        DD = "130;";
        p = 1;
    case 1
        DD = "90;";
        p = 2;
    case 2
        DD = "60;";
        p = 0;   
    end

    Str = "S;"+ DD + DD_before + "\n"
    writeline(s, Str);
    DD_before = DD;
    pause(0.05);
    flush(s); %メモリリセット
end
clear s

function u = PIDControl(m, r)
end