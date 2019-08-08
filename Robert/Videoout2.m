clear;
clc;
 
WriterObj=VideoWriter('cxk.avi', 'Uncompressed AVI');%路径+输出文件名+格式
open(WriterObj);
for i=1:1477
  pic='D:/Matvideo/robert/';%存放帧图的路径
  pic=strcat(pic,num2str(i));
  ppic=strcat(pic,'.jpg');
  frame=imread(ppic);% 读取图像，放在变量frame中
  disp(ppic);
  writeVideo(WriterObj,frame);% 将frame放到变量WriterObj中
end
close(WriterObj);
