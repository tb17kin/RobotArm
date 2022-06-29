clear
close all
clc

% camera setting(Calibration)

% Get coordinates


% Serial Communication to Arduino
% while (1)
%     try
%         device = serialport("COM4", 9600);
%         pause(2);
%         writeline(device, "be");
%         disp("書き込みました。");
%         pause(1);
%         clear device
%         disp("ポートを解放しました。");
%         % pause(0.5);
%     catch
%         disp("ポート接続できませんでした。");
%         disp("1秒間一時停止します。");
%         pause(1);
%     end
% end

s=serialport('COM4',9600);
pause(2);                 % <----------------重要
u=1;                      %読み込み回数の初期値
Input_max_count = 2;    %読み込む回数
x = 3;                    %適当な数字
case_number = int2str(x); %数字から文字変換
DD = "100;";
tic
while u < Input_max_count
    writeline(s,DD);
    outdum = readline(s);
         if isempty(outdum) == 0
        out(u)=str2num(outdum);
        u=u+1;
    end
end
toc
flush(s); %メモリリセット
figure(1);
plot(out);
xlabel('データNo.');
ylabel('出力値');