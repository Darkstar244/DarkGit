close all;
clear all;
clc;
for i=1:793%帧数
    path='D:/Matvideo/MOS/';%视频路径
     disp(i); 
     path=strcat(path,num2str(i));
    p=strcat(path,'.jpg');
    f=imread(p);
    G = fspecial('gaussian', [5 5], 2);%;高斯模糊
    f=imfilter(f,G,'same');
    f=rgb2gray(f);%二值化
    roberts=edge(f,'roberts');%roberts算子边缘检测
   [mn,handle]=imcontour(roberts);%求出轮廓点坐标
   mn=mn.';%矩阵转置
   m=mn(:,1);
   n=mn(:,2);
   x=find(n<=3|n>=1078);
    y=find(m<=3|m>=1918);
    a=[y;x];%寻找边框（分辨率不同的话上面数值也不同）
    m=(m-960)/1080;%*1988410;%缩放以符合音频输出要求
   n=-(n-540)/1920;%*1118481;
   mn=[m,n];
    mn(a,:)=[];%消除边框
    
    %b=int32(mn);%强制类型转换
    lujing=strcat('D:/Matvideo/jie/',num2str(i));%输出存放路径
    lujing=strcat(lujing,'.wav');%输出格式
    audiowrite(lujing,mn,19600);
  
      %dlmwrite('D:/Matvideo/zed.txt',mn);%输出坐标数据到记事本中
   
end