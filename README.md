### これはロボットアームを動かすためのコードです．
アームが直立するための各モータへの入力指令値です．

m1 = 102

m2 = 108

m3 = 83

m4 = 85

m5 = 85

この値で直立すると思う．(グリッパーを付けたとき)
モータに直接指令する場合のピンの位置は

m1 = 11

m2 = 10

m3 = 9

m4 = 6

m5 = 5

m6 = 3

です．またPIN12は起動時にHIGHになるように設定する．

MATLABのツール
computer vision toolbox
support package for usb webcams
の二つがあれば，コードを動かすことができると思います．
