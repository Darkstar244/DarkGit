clear;
clc;
 
WriterObj=VideoWriter('D:/Matvideo/Matryoshaka.avi', 'Uncompressed AVI');%·��+����ļ���+��ʽ
open(WriterObj);
for i=1:730
  pic='D:/Matvideo/Complete/';%���֡ͼ��·��
  pic=strcat(pic,num2str(i));
  ppic=strcat(pic,'.jpg');
  frame=imread(ppic);% ��ȡͼ�񣬷��ڱ���frame��
  disp(ppic);
  writeVideo(WriterObj,frame);% ��frame�ŵ�����WriterObj��
end
close(WriterObj);
