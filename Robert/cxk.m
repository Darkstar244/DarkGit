close all;
clear all;
clc;
for i=1:1477%֡��
    path='D:/Matvideo/lunkuo/';%��Ƶ·��
     disp(i); 
     path=strcat(path,num2str(i));
    p=strcat(path,'.jpg');
    f=imread(p);
    f=rgb2gray(f);
   roberts=edge(f,'roberts');%roberts����
   [m,n]=find(roberts==1);
    %scatter(n,-m,'.');%ȥ��ע��ֱ��չʾ
    mh=scatter(n,-m,'.');%ȷ�����
    axis([0 1200 -750 0]);
    lujing=strcat('D:/Matvideo/robert/',num2str(i));%������·��
    lujing=strcat(lujing,'.jpg');%�����ʽ
    saveas(mh,lujing);%����(���뱣����Ը�14��16,17,18�м���ע�Ͳ�ȥ��13��ע��)
    pause(0.05);
end