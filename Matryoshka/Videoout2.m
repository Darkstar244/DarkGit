clear;
clc;
 
WriterObj=VideoWriter('D:/Matvideo/Matryoshaka.avi', 'Uncompressed AVI');%路径+输出文件名+格式
open(WriterObj);
for i=1:730
  pic='D:/Matvideo/Complete/';%存放帧图的路径
  pic=strcat(pic,num2str(i));
  ppic=strcat(pic,'.jpg');
  frame=imread(ppic);% 读取图像，放在变量frame中
  disp(ppic);
  writeVideo(WriterObj,frame);% 将frame放到变量WriterObj中
end
close(WriterObj);
