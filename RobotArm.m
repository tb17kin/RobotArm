clear
close all
clc

% カメラの起動
cam = webcam(2);
preview(cam);

% serialportでポート番号と速度を指定しポートを占有する
s = serialport('COM4',9600);
disp("ポートを開きました");
pause(2); % 占有のために2秒停止する

% Arduino側からシリアルで何か送られてきた場合にフラグを立てる
global FlagSerial;
FlagSerial = 0;

% 制御用の値
r = [140; 110]; % 目標値
dt = 0.04; % カメラのサンプリング周期(仮)

low_before = 0;
col_before = 0;

global SumI
SumI = 0;

% 1行1列が何mmか
dx = 0.458;
dy = 0.445;

% 制御用のループ
while(1)
    % コールバック関数でシリアルが送られているか確認
    configureCallback(s, "terminator", @readSerialData);

    
    % 座標の取得
    img = snapshot(cam);
    BW = imbinarize(img);
    
    [low, col] = find(BW(:,:,1)); % 白の場所を見つける


    % シリアルが確認できたら制御を開始する
    if(FlagSerial > 0)
        % xとy座標の取得
        x = mean(low);
        y = mean(col);
        x_before = mean(low_before);
        y_before = mean(col_before);

        % 1×1をmmに直す
        x = x * dx;
        y = y * dy;
        x_before = x_before * dx;
        y_before = y_before * dy;

        [xi, phi] = PIDControl(x, y, x_before, y_before, dt, r);

        % json形式で書き，文字列にする
        Str = jsonencode(struct('u1',xi,'u2',phi))
        writeline(s, Str); % シリアルに書き込む
        pause(0.02); % 書き込むためにコードを少し休止する
        flush(s); %メモリリセット
        FlagSerial = 0; % フラグをたたむ
    end
    low_before = low;
    col_before = col;
    pause(0.01);
end
clear s

% コールバック関数の中身
function readSerialData(src, evt)
    global FlagSerial
    FlagSerial = 1;
end

function [xi, phi] = PIDControl(x, y, x_before, y_before, dt, r)
    Kp = 0.03;
    Ki = 0.01;
    Kd = 0.01;
    e = r - [x; y];
    P = Kp * e;
    global SumI
    SumI = SumI + (r - [x; y]) * dt;
    I = Ki * SumI;
    D = Kd * (r - ([x; y] - [x_before;y_before]))/dt;
    u = P + I + D;
    xi = u(1,1);
    phi = u(2,1);
    if(xi > 140)
        xi = 140;
    elseif(xi < 30)
        xi = 30;
    end
    if(phi > 140)
        phi = 140;
    elseif(phi < 30)
        phi = 30;
    end
end