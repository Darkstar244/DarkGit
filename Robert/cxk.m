close all;
clear all;
clc;
for i=1:1477%帧数
    path='D:/Matvideo/lunkuo/';%视频路径
     disp(i); 
     path=strcat(path,num2str(i));
    p=strcat(path,'.jpg');
    f=imread(p);
    f=rgb2gray(f);
   roberts=edge(f,'roberts');%roberts算子
   [m,n]=find(roberts==1);
    %scatter(n,-m,'.');%去掉注释直接展示
    mh=scatter(n,-m,'.');%确定输出
    axis([0 1200 -750 0]);
    lujing=strcat('D:/Matvideo/robert/',num2str(i));%输出存放路径
    lujing=strcat(lujing,'.jpg');%输出格式
    saveas(mh,lujing);%保存(不想保存可以给14，16,17,18行加上注释并去掉13行注释)
    pause(0.05);
end