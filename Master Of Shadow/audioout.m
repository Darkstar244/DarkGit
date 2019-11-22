clear all;
cd = 'D:/Matvideo/jie/';
waveFiles = dir(fullfile(cd,'*.wav'));%读取所有的WAV
len = size(waveFiles,1);%总长度

%Z = [];%初始化Z
Z(2821021,2)=0;%预分配内存（如果数量多的话不这么做会非常卡）
for i =1:792%根据帧数而定
   fileName=strcat('D:/Matvideo/jie/',num2str(i));
   fileName=strcat(fileName,'.wav');
    disp(fileName);
    [X, fs] = audioread(fileName);
X=X( ( 1 : int32(fs*0.52) ), : );%截取每个音频的前0.52s(不然总输出会很大)
    
    Z = [Z; X];
    end
%for i = 1:792
   % fileName=strcat('D:/Matvideo/jie/',num2str(792-i+1));
   %fileName=strcat(fileName,'.wav');
   % disp(fileName);
   % [X, fs] = audioread(fileName);
   
 
   % Z = [Z; X];
%end
lujing=strcat('D:/Matvideo/','zed.wav');%存放路径
audiowrite(lujing,Z,2*fs);%输出