clear;
clc;
se = strel('line',11,90);
path='D:/Matvideo/Doll.mp4';%��Ƶ���·��
obj=VideoReader(path);
num=obj.NumberOfFrames;
for i=1:730%֡��
     disp(i); 
    f=read(obj,i);
    lujing=strcat('D:/Matvideo/Doll/',num2str(i));%���·��
    lujing=strcat(lujing,'.jpg');
    imwrite(f,lujing)
end