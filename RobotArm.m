clear
close all
clc

% camera setting(Calibration)

% Get coordinates

% Serial Communication to Arduino
s = serialport('COM4',9600);
disp("ポートを開きました");
pause(10);
disp("ループに入ります");
p = 0;
DD_before = "100";
global FlagSerial;
FlagSerial = 0;
for i=1:100
    
    configureCallback(s, "terminator", @readSerialData);

    if(FlagSerial > 0)

    % DD = PIDControl(Ball, r);
        switch p
        case 0
            DD = 130;
            p = 1;
        case 1
            DD = 90;
            p = 2;
        case 2
            DD = 60;
            p = 0;   
        end

        Str = jsonencode(struct('m3',DD,'m5',DD_before));
        writeline(s, Str);
        pause(0.5);
        DD_before = DD;
        flush(s); %メモリリセット
        FlagSerial = 0;
    end
    pause(0.01);
end
% clear s

function readSerialData(src, evt)
    global FlagSerial
    FlagSerial = 1;
end

function u = PIDControl(m, r)
end