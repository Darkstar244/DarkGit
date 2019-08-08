clear;
clc;
se = strel('line',11,90);
path='D:/Matvideo/Cai Xukun Idol Producer Self-Intro.mp4';%视频存放路径
obj=VideoReader(path);
num=obj.NumberOfFrames;
for i=1:1477%帧数
    frame=read(obj,i);
    lujing=strcat('D:/Matvideo/lunkuo/',num2str(i));%输出路径
    lujing=strcat(lujing,'.jpg');
    imwrite(frame,lujing)
end