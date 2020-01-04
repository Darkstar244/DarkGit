clear;
clc;
se = strel('line',11,90);
path='D:/Matvideo/Doll.mp4';%视频存放路径
obj=VideoReader(path);
num=obj.NumberOfFrames;
for i=1:730%帧数
     disp(i); 
    f=read(obj,i);
    lujing=strcat('D:/Matvideo/Doll/',num2str(i));%输出路径
    lujing=strcat(lujing,'.jpg');
    imwrite(f,lujing)
end