clear;
clc;
se = strel('line',11,90);
path='D:/Matvideo/Cai Xukun Idol Producer Self-Intro.mp4';%��Ƶ���·��
obj=VideoReader(path);
num=obj.NumberOfFrames;
for i=1:1477%֡��
    frame=read(obj,i);
    lujing=strcat('D:/Matvideo/lunkuo/',num2str(i));%���·��
    lujing=strcat(lujing,'.jpg');
    imwrite(frame,lujing)
end