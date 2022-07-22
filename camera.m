clear
close all
clc


% ==== 座標変換用プログラム =================================== %
% カメラの起動
cam = webcam(2);
preview(cam);

% 座標の取得
img = snapshot(cam);
image(img);

% 画角が何mmか
xl = 220;
yl = 285;

dx = xl / 480;
dy = yl / 640;