clear
close all
clc

% camera setting(Calibration)

% Get coordinates

% Serial Communication to Arduino
% serialportでポート番号と速度を指定しポートを占有する
s = serialport('COM4',9600);
disp("ポートを開きました");
pause(2); % 占有のために2秒停止する

p = 0;
DD_before = "100";

% Arduino側からシリアルで何か送られてきた場合にフラグを立てる
global FlagSerial;
FlagSerial = 0;

% 制御用の値
r = [0; 0]; % 目標値
m = 5.5 * 10^(-3); % 質量(kg)

% 制御用のループ
while(1)
    % コールバック関数でシリアルが送られているか確認
    configureCallback(s, "terminator", @readSerialData);

    % シリアルが確認できたら制御を開始する
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

        % json形式で書き，文字列にする
        Str = jsonencode(struct('u1',DD,'u2',DD_before));
        writeline(s, Str); % シリアルに書き込む
        pause(0.05); % 書き込むためにコードを少し休止する
        DD_before = DD;
        flush(s); %メモリリセット
        FlagSerial = 0; % フラグをたたむ
    end
    pause(0.01);
end
clear s

% コールバック関数の中身
function readSerialData(src, evt)
    global FlagSerial
    FlagSerial = 1;
end

function u = PIDControl(m, r)
end