clear
close all
clc

% camera setting(Calibration)

% Get coordinates

% Serial Communication to Arduino
s=serialport('COM4',9600);
pause(2);
p = 0;
DD_before = "100;";
for i=1:10

    % DD = PIDControl(Ball, r);
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

    Str = "S;"+ DD + DD_before + "\n"
    % writeline(s, DD);
    writeline(s, Str);
    DD_before = DD;
    pause(2);
    flush(s); %メモリリセット
end
clear s

function u = PIDControl(m, r)
end