close all;
clear all;
clc;
for i=1:793%֡��
    path='D:/Matvideo/MOS/';%��Ƶ·��
     disp(i); 
     path=strcat(path,num2str(i));
    p=strcat(path,'.jpg');
    f=imread(p);
    G = fspecial('gaussian', [5 5], 2);%;��˹ģ��
    f=imfilter(f,G,'same');
    f=rgb2gray(f);%��ֵ��
    roberts=edge(f,'roberts');%roberts���ӱ�Ե���
   [mn,handle]=imcontour(roberts);%�������������
   mn=mn.';%����ת��
   m=mn(:,1);
   n=mn(:,2);
   x=find(n<=3|n>=1078);
    y=find(m<=3|m>=1918);
    a=[y;x];%Ѱ�ұ߿򣨷ֱ��ʲ�ͬ�Ļ�������ֵҲ��ͬ��
    m=(m-960)/1080;%*1988410;%�����Է�����Ƶ���Ҫ��
   n=-(n-540)/1920;%*1118481;
   mn=[m,n];
    mn(a,:)=[];%�����߿�
    
    %b=int32(mn);%ǿ������ת��
    lujing=strcat('D:/Matvideo/jie/',num2str(i));%������·��
    lujing=strcat(lujing,'.wav');%�����ʽ
    audiowrite(lujing,mn,19600);
  
      %dlmwrite('D:/Matvideo/zed.txt',mn);%����������ݵ����±���
   
end